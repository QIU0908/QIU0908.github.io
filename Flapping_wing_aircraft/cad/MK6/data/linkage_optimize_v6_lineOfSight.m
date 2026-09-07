%% linkage_optimize_v6_lineOfSight.m
% 新機構型式 (依上傳的 GeoGebra 構造圖)：
%   A = (b, a)                 輸入端 (b=A_x 滑桿 in [b_min,b_max]，a=A_y 滑桿 in [a_min,a_max])
%   G = (Gx, 0)                固定樞紐 (對應 GeoGebra 裡的 B 點)，限制在 x 軸上 (Gy=0)
%   圓 c : 圓心 G, 半徑 rG      (對應 GeoGebra 裡 Circle(B,5))
%   E = 從 A 通過 G 的射線 f，延伸到與圓 c 的遠端交點
%       (與之前版本 IfromA 公式完全相同：E = G + rG*(G-A)/|G-A|)
%   C = (Cx, 0)                固定樞紐 (對應 GeoGebra 裡的 C 點)，限制在 x 軸上 (Cy=0)
%   g : 射線 Ray(C, E)          <-- 這就是最終「撲翼桿」
%   輸出角度 theta = 射線 g 相對 C 的方位角 = atan2(Ey-Cy, Ex-Cx)
%
% 跟前一版 (需要 rd, rk 兩圓求交點得到 K) 的差別：
%   這版機構沒有 rd、rk，輸出桿直接是 C->E 的連線方向，
%   所以未知數只剩 3 個：Gx, rG, Cx (G、C 皆固定在 x 軸上)。
%
% 最佳化目標/限制邏輯與前一版相同：
%   - 擺角 swing(b=b_max) 越接近上限(maxSwingCap留swingSafetyMargin緩衝)，獎勵越強(距離平方)。
%   - 角度中點(兩端平均) 隨 b 變化的範圍越小，獎勵越強(平方懲罰)。
%   - 擺角必須 < maxSwingCap (硬性)。
%   - swing(b_max) 要比 swing(b_min) 大 minSwingIncreasePct~maxSwingIncreasePct (硬性)。
%   - swing(b_min) 不能小於 minSwingAtBmin (硬性，防漏洞)。
%   - Gx, rG, Cx 必須落在各自 range 內 (硬性, fmincon lb/ub)。
%   - 新的"奇異點"防呆 (取代原本的死點餘裕)：
%       (1) A 不能太靠近 G，否則方向向量 (G-A) 趨近零向量，E 的方向會不穩定
%           -> 要求 min(|A-G|) >= req_margin_AG
%       (2) E 不能太靠近 C，否則射線 g 的角度對 E 的微小變化會極度敏感(近似奇異)
%           -> 要求 min(|E-C|) >= req_margin_EC
%
% 最後追加：
%   - [Section 6b] 把最佳化出來的 3 個未知數 (Gx, rG, Cx) 四捨五入到小數點後1位，
%     重新驗證一次，並與原始(未取整)結果對照。
%   - 額外印出 b=0.000 時的中點平均角度 (原始 & 四捨五入後)。
%
% 重要說明：本版需要 Optimization Toolbox (fmincon)。
%
clear; clc; close all;
rng(1);

%% ---------- 1. 已知固定參數 ----------
a_min = -5;   a_max =  5;       % A_y 範圍
b_min = -3.5; b_max = 3.5;      % A_x 範圍

%% ---------- 2. 未知數搜尋範圍 (共3個：Gx, rG, Cx) ----------
Gx_range = [0, 20];
rG_range = [2, 20];
Cx_range = [0, 20];

lb = [Gx_range(1), rG_range(1), Cx_range(1)];
ub = [Gx_range(2), rG_range(2), Cx_range(2)];

req_margin_AG = 0.3;   % A 與 G 的最小距離 (避免方向向量趨近零向量)
req_margin_EC = 0.3;   % E 與 C 的最小距離 (避免射線角度對E的變化過度敏感)

nTrials    = 1000;     % multistart 起始點數量
nBSamples  = 5;        % 用幾個 b 代表點檢查「角度中點」與擺幅

w_inv      = 3.0;      % 中點不變懲罰權重 (乘上 rangeAvg^2)
w_size     = 0.3;      % 尺寸獎勵權重：sizeMetric = rG + |Cx-Gx| (機構整體跨距)，越小越好
w_close    = 5.0;      % 逼近上限獎勵權重

maxSwingCap        = 195;  % 擺角上限
swingSafetyMargin  = 2;    % 安全緩衝(deg)

minSwingIncreasePct    = 0.50;
maxSwingIncreasePct    = 0.60;
minSwingAtBmin       = 20;

b_samples = linspace(b_min, b_max, nBSamples);

fprintf('=========== [視線式機構] 最佳化開始 (3未知數 Gx,rG,Cx + 中點穩定 + 逼近上限獎勵 + 擺角<%.0f + 擺幅差%.0f%%~%.0f%% + 底限%.0fdeg) ===========\n', ...
    maxSwingCap, minSwingIncreasePct*100, maxSwingIncreasePct*100, minSwingAtBmin);

%% ---------- 3. 目標函式 ----------
objFun = @(x) penalizedNegSwingLOS(x, a_min, a_max, b_min, b_max, b_samples, ...
                                    req_margin_AG, req_margin_EC, w_inv, w_size, ...
                                    maxSwingCap, swingSafetyMargin, ...
                                    minSwingIncreasePct, maxSwingIncreasePct, minSwingAtBmin, ...
                                    'w_close', w_close);

%% ---------- 4. multistart (fmincon + lb/ub) ----------
optsF = optimoptions('fmincon', ...
    'Display','off', ...
    'Algorithm','sqp', ...
    'MaxIterations',1000, ...
    'MaxFunctionEvaluations',2000, ...
    'StepTolerance',1e-3, ...
    'OptimalityTolerance',1e-2);

bestVal = inf; bestX = [];
trialLog = nan(nTrials,1);

for t = 1:nTrials
    x0 = [ Gx_range(1)+rand*diff(Gx_range), ...
           rG_range(1)+rand*diff(rG_range), ...
           Cx_range(1)+rand*diff(Cx_range) ];

    try
        [xOpt, fVal] = fmincon(objFun, x0, [],[],[],[], lb, ub, [], optsF);
    catch
        continue;
    end

    if fVal < 1e6
        trialLog(t) = -fVal;
    end
    if fVal < bestVal
        bestVal = fVal; bestX = xOpt;
    end
end

if isempty(bestX) || bestVal >= 1e6
    error(['所有 multistart 起點都沒找到可行解，請放寬搜尋範圍、' ...
           '降低 req_margin_AG/req_margin_EC/minSwingAtBmin，或降低 w_inv/w_close 再試一次。']);
end

fprintf('multistart 初步最佳解 obj=%.3f\n', bestVal);

%% ---------- 5. 局部精修 ----------
objFunFine = @(x) penalizedNegSwingLOS(x, a_min, a_max, b_min, b_max, b_samples, ...
                                        req_margin_AG, req_margin_EC, w_inv, w_size, ...
                                        maxSwingCap, swingSafetyMargin, ...
                                        minSwingIncreasePct, maxSwingIncreasePct, minSwingAtBmin, ...
                                        'na',25,'nb',17,'nSwing',121, 'w_close', w_close);
optsFine = optimoptions('fmincon', ...
    'Display','off', ...
    'Algorithm','sqp', ...
    'MaxIterations',1200, ...
    'MaxFunctionEvaluations',2400, ...
    'StepTolerance',1e-4, ...
    'OptimalityTolerance',1e-3);

try
    [xOptFine, fValFine] = fmincon(objFunFine, bestX, [],[],[],[], lb, ub, [], optsFine);
    if fValFine < bestVal && fValFine < 1e6
        bestX = xOptFine; bestVal = fValFine;
    end
catch
end

bestX = min(max(bestX, lb), ub);

Gx_opt = bestX(1); rG_opt = bestX(2); Cx_opt = bestX(3);
G_opt = [Gx_opt, 0]; C_opt = [Cx_opt, 0];

%% ---------- 6. 最終高解析度驗證 ----------
mm = minMarginLOS(G_opt, rG_opt, C_opt, a_min, a_max, b_min, b_max, 61, 41);
minMargin_AG_final = mm.mAG;
minMargin_EC_final = mm.mEC;

infoFinal = swingInfoLOS(G_opt, rG_opt, C_opt, b_max, a_min, a_max, 401);

avgList = nan(1, nBSamples);
swingList = nan(1, nBSamples);
allOkForSamples = true;
for i = 1:nBSamples
    info_i = swingInfoLOS(G_opt, rG_opt, C_opt, b_samples(i), a_min, a_max, 201);
    if isnan(info_i.s) || ~info_i.monotonic
        allOkForSamples = false;
    end
    avgList(i)   = (info_i.theta_lo + info_i.theta_hi) / 2;
    swingList(i) = info_i.s;
end
avgRange = max(avgList) - min(avgList);

swing_bmin_final = swingList(1);
swing_bmax_final = swingList(end);
increasePct_final = (swing_bmax_final - swing_bmin_final) / swing_bmin_final;

if minMargin_AG_final < req_margin_AG || minMargin_EC_final < req_margin_EC || ...
        isnan(infoFinal.s) || ~infoFinal.monotonic || ~allOkForSamples
    error('最終高解析度驗證失敗，請重跑或調整搜尋範圍/req_margin_AG/req_margin_EC/w_inv。');
end
if infoFinal.s >= maxSwingCap
    error('最終擺角 %.4f deg 未低於上限 %.1f deg，請重跑或加大 swingSafetyMargin。', ...
        infoFinal.s, maxSwingCap);
end
if swing_bmin_final < minSwingAtBmin
    error('最終 swing(b_min) = %.4f deg 低於底限 %.1f deg，請重跑或調整搜尋範圍。', ...
        swing_bmin_final, minSwingAtBmin);
end
if increasePct_final < minSwingIncreasePct || increasePct_final > maxSwingIncreasePct
    error(['最終 swing(b_max) 比 swing(b_min) 大 %.2f%%，超出需求範圍 %.0f%%~%.0f%%，' ...
           '請重跑或調整搜尋範圍/w_inv。'], increasePct_final*100, minSwingIncreasePct*100, maxSwingIncreasePct*100);
end

xFinal = [Gx_opt, rG_opt, Cx_opt];
tolBound = 1e-6;
if any(xFinal < lb - tolBound) || any(xFinal > ub + tolBound)
    error('最終解超出指定邊界範圍，請檢查 fmincon 設定或邊界是否合理。');
end

swing_opt  = infoFinal.s;
theta_lo_u = infoFinal.theta_lo;
theta_hi_u = infoFinal.theta_hi;
theta_a0_u = infoFinal.theta_a0;
alpha_total = theta_hi_u - theta_lo_u;

swingLimitReport = maxSwingCap - swingSafetyMargin;
distToCapReport  = swingLimitReport - swing_bmax_final;

sizeMetric_final = rG_opt + abs(Cx_opt - Gx_opt);

fprintf('\n---------- 最終最佳化結果 (視線式機構) ----------\n');
fprintf('G 點座標 (固定樞紐)   = (%.4f, 0)\n', Gx_opt);
fprintf('圓 c 半徑 rG          = %.4f\n', rG_opt);
fprintf('C 點座標 (輸出樞紐)   = (%.4f, 0)\n', Cx_opt);
fprintf('尺寸指標 (rG+|Cx-Gx|) = %.4f  (w_size=%.2f，越小代表機構越緊湊)\n', sizeMetric_final, w_size);
fprintf('全程最小 |A-G| 餘裕   = %.4f (需求 >= %.2f)\n', minMargin_AG_final, req_margin_AG);
fprintf('全程最小 |E-C| 餘裕   = %.4f (需求 >= %.2f)\n', minMargin_EC_final, req_margin_EC);
fprintf('A 最右側(b=%.2f)時 g 射線擺角 = %.4f deg  (上限 %.1f deg，安全上限 %.1f deg)\n', ...
    b_max, swing_opt, maxSwingCap, swingLimitReport);
fprintf('  與安全上限的距離 = %.4f deg  (w_close=%.2f，越小代表越逼近上限)\n', distToCapReport, w_close);
fprintf('  下端 theta(a=%.1f) = %.4f deg\n', a_min, theta_lo_u);
fprintf('  中點 theta(a=0)   = %.4f deg\n', theta_a0_u);
fprintf('  上端 theta(a=%.1f) = %.4f deg\n', a_max, theta_hi_u);
fprintf('真實總擺角 = %.4f deg\n', alpha_total);
fprintf('\n【角度中點(兩端平均) 穩定度檢查，共取 %d 個 b 樣本點】\n', nBSamples);
for i = 1:nBSamples
    fprintf('  b=%.3f  中點平均角度 = %.4f deg\n', b_samples(i), avgList(i));
end
fprintf('  變動範圍 (max-min) = %.4f deg\n', avgRange);

% 明確印出 b=0 的中點平均角度 (獨立精算，不受 nBSamples 取樣影響)
info0 = swingInfoLOS(G_opt, rG_opt, C_opt, 0, a_min, a_max, 201);
avg0  = (info0.theta_lo + info0.theta_hi) / 2;
fprintf('\n【b=0.000 中點平均角度】(原始/未取整)\n');
fprintf('  b=0.000  中點平均角度 = %.4f deg\n', avg0);

fprintf('\n【擺幅差異檢查：swing(b_max) vs swing(b_min)】\n');
fprintf('  swing(b_min=%.2f) = %.4f deg  (需求底限 >= %.1f deg)\n', b_min, swing_bmin_final, minSwingAtBmin);
fprintf('  swing(b_max=%.2f) = %.4f deg\n', b_max, swing_bmax_final);
fprintf('  實際差異 = %.2f%%  (需求範圍 %.0f%%~%.0f%%)\n', increasePct_final*100, minSwingIncreasePct*100, maxSwingIncreasePct*100);

fprintf('\n【邊界確認】\n');
fprintf('  Gx=%.3f in [%.1f,%.1f] | rG=%.3f in [%.1f,%.1f] | Cx=%.3f in [%.1f,%.1f]\n', ...
    Gx_opt, Gx_range(1), Gx_range(2), rG_opt, rG_range(1), rG_range(2), Cx_opt, Cx_range(1), Cx_range(2));

%% ---------- 6b. 四捨五入到小數點後一位，重新計算驗證 ----------
xRounded = round(bestX * 10) / 10;
xRounded = min(max(xRounded, lb), ub);

Gx_r = xRounded(1); rG_r = xRounded(2); Cx_r = xRounded(3);
G_r = [Gx_r, 0]; C_r = [Cx_r, 0];

mm_r = minMarginLOS(G_r, rG_r, C_r, a_min, a_max, b_min, b_max, 61, 41);
infoFinal_r = swingInfoLOS(G_r, rG_r, C_r, b_max, a_min, a_max, 401);

avgList_r = nan(1, nBSamples);
swingList_r = nan(1, nBSamples);
allOkForSamples_r = true;
for i = 1:nBSamples
    info_i = swingInfoLOS(G_r, rG_r, C_r, b_samples(i), a_min, a_max, 201);
    if isnan(info_i.s) || ~info_i.monotonic
        allOkForSamples_r = false;
    end
    avgList_r(i)   = (info_i.theta_lo + info_i.theta_hi) / 2;
    swingList_r(i) = info_i.s;
end
avgRange_r = max(avgList_r) - min(avgList_r);

swing_bmin_r = swingList_r(1);
swing_bmax_r = swingList_r(end);
if swing_bmin_r ~= 0
    increasePct_r = (swing_bmax_r - swing_bmin_r) / swing_bmin_r;
else
    increasePct_r = NaN;
end

feasible_r = ~( isnan(infoFinal_r.s) || ~infoFinal_r.monotonic || ~allOkForSamples_r );

fprintf('\n\n=========== [驗證] 3個未知數四捨五入到小數點後1位，重新計算一次 ===========\n');
fprintf('四捨五入後參數：Gx=%.1f, rG=%.1f, Cx=%.1f\n', Gx_r, rG_r, Cx_r);

if ~feasible_r
    fprintf(2, ['\n[警告] 四捨五入後的參數在部分 b 值下算不出合法解 (可能奇異點/不連續)，' ...
                '以下數值僅供參考，機構可能無法照原設計正常運作！\n']);
else
    if mm_r.mAG < req_margin_AG
        fprintf(2, '[警告] 四捨五入後 |A-G| 餘裕 = %.4f，低於需求 %.2f！\n', mm_r.mAG, req_margin_AG);
    end
    if mm_r.mEC < req_margin_EC
        fprintf(2, '[警告] 四捨五入後 |E-C| 餘裕 = %.4f，低於需求 %.2f！\n', mm_r.mEC, req_margin_EC);
    end
    if infoFinal_r.s >= maxSwingCap
        fprintf(2, '[警告] 四捨五入後 擺角 = %.4f deg，超過上限 %.1f deg！\n', infoFinal_r.s, maxSwingCap);
    end
end

fprintf('\n全程最小 |A-G| 餘裕 = %.4f (需求 >= %.2f)\n', mm_r.mAG, req_margin_AG);
fprintf('全程最小 |E-C| 餘裕 = %.4f (需求 >= %.2f)\n', mm_r.mEC, req_margin_EC);
fprintf('A 最右側(b=%.2f)時 g 射線擺角 = %.4f deg  (上限 %.1f deg，安全上限 %.1f deg)\n', ...
    b_max, infoFinal_r.s, maxSwingCap, swingLimitReport);
fprintf('  下端 theta(a=%.1f) = %.4f deg\n', a_min, infoFinal_r.theta_lo);
fprintf('  中點 theta(a=0)   = %.4f deg\n', infoFinal_r.theta_a0);
fprintf('  上端 theta(a=%.1f) = %.4f deg\n', a_max, infoFinal_r.theta_hi);
fprintf('真實總擺角 = %.4f deg\n', infoFinal_r.theta_hi - infoFinal_r.theta_lo);

fprintf('\n【角度中點(兩端平均) 穩定度檢查，共取 %d 個 b 樣本點】(四捨五入後)\n', nBSamples);
for i = 1:nBSamples
    fprintf('  b=%.3f  中點平均角度 = %.4f deg\n', b_samples(i), avgList_r(i));
end
fprintf('  變動範圍 (max-min) = %.4f deg\n', avgRange_r);

% 明確印出四捨五入後 b=0 的中點平均角度
info0_r = swingInfoLOS(G_r, rG_r, C_r, 0, a_min, a_max, 201);
avg0_r  = (info0_r.theta_lo + info0_r.theta_hi) / 2;
fprintf('\n【b=0.000 中點平均角度】(四捨五入後)\n');
fprintf('  b=0.000  中點平均角度 = %.4f deg\n', avg0_r);

fprintf('\n【擺幅差異檢查：swing(b_max) vs swing(b_min)】(四捨五入後)\n');
fprintf('  swing(b_min=%.2f) = %.4f deg  (需求底限 >= %.1f deg)\n', b_min, swing_bmin_r, minSwingAtBmin);
fprintf('  swing(b_max=%.2f) = %.4f deg\n', b_max, swing_bmax_r);
fprintf('  實際差異 = %.2f%%  (需求範圍 %.0f%%~%.0f%%)\n', increasePct_r*100, minSwingIncreasePct*100, maxSwingIncreasePct*100);

fprintf('\n【原始(未取整) vs 四捨五入後(小數點後1位) 比較】\n');
fprintf('  擺角 swing(b_max) :  原始=%.4f deg   ->  取整後=%.4f deg   (差=%+.4f deg)\n', ...
    swing_bmax_final, swing_bmax_r, swing_bmax_r - swing_bmax_final);
fprintf('  擺幅增加百分比    :  原始=%.2f%%      ->  取整後=%.2f%%      (差=%+.2f%%)\n', ...
    increasePct_final*100, increasePct_r*100, (increasePct_r-increasePct_final)*100);
fprintf('  中點變動範圍      :  原始=%.4f deg   ->  取整後=%.4f deg   (差=%+.4f deg)\n', ...
    avgRange, avgRange_r, avgRange_r - avgRange);
fprintf('  b=0 中點平均角度  :  原始=%.4f deg   ->  取整後=%.4f deg   (差=%+.4f deg)\n', ...
    avg0, avg0_r, avg0_r - avg0);
fprintf('  |A-G| 最小餘裕    :  原始=%.4f       ->  取整後=%.4f       (差=%+.4f)\n', ...
    minMargin_AG_final, mm_r.mAG, mm_r.mAG - minMargin_AG_final);
fprintf('  |E-C| 最小餘裕    :  原始=%.4f       ->  取整後=%.4f       (差=%+.4f)\n', ...
    minMargin_EC_final, mm_r.mEC, mm_r.mEC - minMargin_EC_final);

%% ---------- 7. 繪圖 ----------
figure('Name','multistart 收斂情形');
validTrials = ~isnan(trialLog);
stem(find(validTrials), trialLog(validTrials), 'filled');
xlabel('multistart 第幾次'); ylabel('-罰函數值');
title('各起始點收斂情形'); grid on;

figure('Name','角度中點 vs A_x (b)：原始 vs 四捨五入後');
plot(b_samples, avgList, 'o-', 'LineWidth', 1.5, 'MarkerFaceColor','b'); hold on;
plot(b_samples, avgList_r, 's--', 'LineWidth', 1.5, 'MarkerFaceColor','r');
xlabel('b (A_x)'); ylabel('兩端角度平均值 (deg)');
legend('原始(未取整)', '四捨五入後(0.1)', 'Location','best');
title(sprintf('角度中點 vs b (原始變動範圍=%.3f deg, 取整後=%.3f deg)', avgRange, avgRange_r));
grid on;

figure('Name','擺角 vs A_x (b)：原始 vs 四捨五入後');
plot(b_samples, swingList, 'o-', 'LineWidth', 1.5, 'Color',[0.85 0.2 0.2], 'MarkerFaceColor','r'); hold on;
plot(b_samples, swingList_r, 's--', 'LineWidth', 1.5, 'Color',[0.2 0.2 0.85], 'MarkerFaceColor','b');
xlabel('b (A_x)'); ylabel('擺角 (deg)');
legend('原始(未取整)', '四捨五入後(0.1)', 'Location','best');
title(sprintf('擺角 vs b (原始差異=%.1f%%, 取整後差異=%.1f%%)', ...
    increasePct_final*100, increasePct_r*100));
grid on;

figure('Name','機構示意圖 (a = -5, 0, 5，b 在最右側)');
hold on; axis equal; grid on;
viscircles(G_opt, rG_opt, 'Color', [0.7 0.7 0.7], 'LineStyle', ':');
plot(G_opt(1), G_opt(2), 'ks', 'MarkerFaceColor','k'); text(G_opt(1), G_opt(2)-1, 'G');
plot(C_opt(1), C_opt(2), 'ks', 'MarkerFaceColor','k'); text(C_opt(1), C_opt(2)-1, 'C');

colors = {[0.85 0.2 0.2], [0.2 0.6 0.2], [0.2 0.2 0.85]};
labels = {sprintf('a=%.0f (下端)',a_min), 'a=0 (中點)', sprintf('a=%.0f (上端)',a_max)};
aVals = [a_min, 0, a_max];
for t = 1:3
    A_t = [b_max, aVals(t)];
    E_t = EfromA(A_t, G_opt, rG_opt);
    plot([A_t(1) G_opt(1)], [A_t(2) G_opt(2)], '-', 'Color', colors{t}*0.5+0.5);
    plot(A_t(1), A_t(2), 'o', 'Color', colors{t}, 'MarkerFaceColor', colors{t});
    plot(E_t(1), E_t(2), '^', 'Color', colors{t}, 'MarkerFaceColor', colors{t});
    plot([C_opt(1) E_t(1)], [C_opt(2) E_t(2)], '-', 'Color', colors{t}, 'LineWidth', 2.5);
    plot(E_t(1), E_t(2), 'p', 'Color', colors{t}, 'MarkerFaceColor', colors{t}, 'MarkerSize', 10);
end
legend(labels, 'Location', 'bestoutside');
title(sprintf('rG=%.3f, |Cx-Gx|=%.3f, 總擺角=%.2f deg, 中點變動=%.2f deg', ...
    rG_opt, abs(Cx_opt-Gx_opt), alpha_total, avgRange));
xlabel('x'); ylabel('y');

fprintf('\n=========== 完成 ===========\n');

%% ======================= 區域函式 =======================

function E = EfromA(A, G, rG)
    v = G - A;
    nv = norm(v);
    if nv < 1e-9
        E = [NaN, NaN];
        return;
    end
    E = G + rG * v / nv;
end

function res = swingInfoLOS(G, rG, C, b, a_min, a_max, n)
    aa = linspace(a_min, a_max, n);
    th = nan(1, n);
    for i = 1:n
        A = [b, aa(i)];
        E = EfromA(A, G, rG);
        if any(isnan(E))
            res.s = NaN; res.monotonic = false;
            res.theta_lo = NaN; res.theta_hi = NaN; res.theta_a0 = NaN;
            return;
        end
        th(i) = atan2(E(2)-C(2), E(1)-C(1));
    end
    th = unwrap(th);
    dth = diff(th);
    monotonic = all(sign(dth) >= 0) || all(sign(dth) <= 0);
    if max(abs(dth)) < 1e-6
        monotonic = false;
    end
    [~, idx0] = min(abs(aa - 0));

    res.s        = rad2deg(max(th) - min(th));
    res.monotonic = monotonic;
    res.theta_lo = rad2deg(th(1));
    res.theta_hi = rad2deg(th(end));
    res.theta_a0 = rad2deg(th(idx0));
end

function m = minMarginLOS(G, rG, C, a_min, a_max, b_min, b_max, na, nb)
    mEC = inf; mAG = inf;
    aa = linspace(a_min, a_max, na);
    bb = linspace(b_min, b_max, nb);
    for b = bb
        for a = aa
            A = [b, a];
            v = G - A;
            nv = norm(v);
            mAG = min(mAG, nv);
            if nv < 1e-9
                continue;   % 避免除以0；此點的 |A-G| 已經計入 mAG
            end
            E = G + rG * v / nv;
            mEC = min(mEC, norm(E - C));
        end
    end
    m.mEC = mEC;
    m.mAG = mAG;
end

function val = penalizedNegSwingLOS(x, a_min, a_max, b_min, b_max, b_samples, ...
                                     req_margin_AG, req_margin_EC, w_inv, w_size, ...
                                     maxSwingCap, swingSafetyMargin, ...
                                     minSwingIncreasePct, maxSwingIncreasePct, minSwingAtBmin, varargin)
    p = inputParser;
    addParameter(p,'na',13); addParameter(p,'nb',9); addParameter(p,'nSwing',31);
    addParameter(p,'w_close',1.0);
    parse(p, varargin{:});
    na = p.Results.na; nb = p.Results.nb; nSwing = p.Results.nSwing;
    w_close = p.Results.w_close;

    Gx=x(1); rG=x(2); Cx=x(3);

    if rG <= 0.5
        val = 1e7; return;
    end

    G = [Gx, 0]; C = [Cx, 0];

    mm = minMarginLOS(G, rG, C, a_min, a_max, b_min, b_max, na, nb);
    if mm.mAG < req_margin_AG
        val = 1e7 * (req_margin_AG - mm.mAG + 1);
        return;
    end
    if mm.mEC < req_margin_EC
        val = 1e7 * (req_margin_EC - mm.mEC + 1);
        return;
    end

    avgs = nan(1, numel(b_samples));
    swings = nan(1, numel(b_samples));
    for i = 1:numel(b_samples)
        info_i = swingInfoLOS(G, rG, C, b_samples(i), a_min, a_max, nSwing);
        if isnan(info_i.s) || ~info_i.monotonic
            val = 1e7; return;
        end
        avgs(i)   = (info_i.theta_lo + info_i.theta_hi) / 2;
        swings(i) = info_i.s;
    end
    rangeAvg = max(avgs) - min(avgs);

    swing_bmin = swings(1);
    swing_bmax = swings(end);

    swingLimit = maxSwingCap - swingSafetyMargin;
    if swing_bmax >= swingLimit
        val = 1e7 * (swing_bmax - swingLimit + 1);
        return;
    end

    if swing_bmin < minSwingAtBmin
        val = 1e7 * (minSwingAtBmin - swing_bmin + 1);
        return;
    end

    requiredMin = (1 + minSwingIncreasePct) * swing_bmin;
    requiredMax = (1 + maxSwingIncreasePct) * swing_bmin;
    if swing_bmax < requiredMin
        val = 1e7 * (requiredMin - swing_bmax + 1);
        return;
    end
    if swing_bmax > requiredMax
        val = 1e7 * (swing_bmax - requiredMax + 1);
        return;
    end

    sizeMetric = rG + abs(Cx - Gx);   % 尺寸指標：圓半徑 + G,C 間距，越小代表機構越緊湊

    distToCap   = swingLimit - swing_bmax;
    closeReward = w_close * distToCap^2;

    rangeReward = w_inv * rangeAvg^2;

    val = closeReward + rangeReward + w_size * sizeMetric;
end