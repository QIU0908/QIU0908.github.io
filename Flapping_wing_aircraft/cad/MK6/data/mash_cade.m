%% linkage_optimize_v11_pso_sqp_hybrid.m
% =========================================================================
% 機構最佳化【連續空間版】 particleswarm(全域,無梯度) + fmincon(SQP,局部精修)
% 混合式多起點最佳化
%
% [診斷：為什麼 v10 的 fmincon+MultiStart(2000起點) 找不到解]
%   (1) 目標函式在很大範圍內是「平坦懸崖」：
%       - 中點誤差超過門檻 (USE_HARD_MIDPOINT_CONSTRAINT=true) 時，
%         直接 val=1e9 return，沒有任何梯度方向可循。
%       - 整段 b 行程完全無法形成 K 交點 (all(isnan(swings))) 時，
%         同樣直接 val=1e9 return。
%       SQP 靠有限差分估計梯度，掉進這些「平坦值恆為1e9」的區域時，
%       所有鄰近試探點的目標值都一樣是1e9，梯度=0，fmincon會立刻判定
%       「找不到下降方向」而終止，幾乎每個起點都這樣陣亡。
%   (2) 每次目標函式求值要對 500 個 b 取樣點各呼叫一次 swingInfo
%       (內部再對 a 取 31 點)：約 15,500 次幾何運算/次評估。
%       SQP 有限差分梯度 7維*(至少8次評估)/迭代 * 最多600次迭代 * 2000起點，
%       總運算量在合理時間內幾乎不可能跑完。
%
% [對策]
%   (a) 搜尋階段改用較粗的 b_samples_opt (41點) 取代 b_samples(500點)，
%       單次評估成本降低超過10倍；完整500點高解析度只用在最終驗證/繪圖。
%   (b) 全域搜尋改用 particleswarm：族群式、不需要梯度，能夠「跳過」
%       1e9平坦懸崖去探索其他區域，直到族群某些粒子落入可行盆地。
%   (c) 用 particleswarm 內建 'HybridFcn' = {@fmincon, sqpOpts}：
%       PSO收斂後自動接力用 fmincon('sqp') 對同一個點做局部精修，
%       一次呼叫同時完成「全域找可行域」+「局部精修出精確解」。
%   (d) 外層重複跑多次獨立的 PSO+SQP 混合最佳化 (不同亂數種子/不同初始
%       族群)，模擬 multi-start 的穩健度，取全部裡面最好的一組。
%   (e) 找到最佳解後，再用完整 500 點解析度對它做一次 fmincon 局部精修，
%       確保最終報告數值是在高解析度下收斂的。
% =========================================================================
clear; clc; close all; rng(1);

%% ---------- 0. 若有已知可行解，可填在這裡當作額外起點 (可留空) ----------
v4SeedX = [];   % <-- 有已知可行解的話，把7個數字填在這裡 [Gx,Gy,rG,Bx,By,rd,rk]

%% ---------- 1. 已知固定參數 ----------
a_min = -5;   a_max =  5;       % A_y 行程範圍 (已知)
b_min = -3.5; b_max =  3.5;     % A_x 橫移範圍 (已知)

%% ---------- 2. 連續搜尋範圍 (7 個幾何參數, mm) ----------
Gx_range = [5.0, 25.0];
Gy_range = [0, 0];
rG_range = [6.0, 25.0];
Bx_range = [5.0, 25.0];
By_range = [0, 0];
rd_range = [6.0, 25.0];
rk_range = [6.0, 25.0];

lb = [Gx_range(1), Gy_range(1), rG_range(1), Bx_range(1), By_range(1), rd_range(1), rk_range(1)];
ub = [Gx_range(2), Gy_range(2), rG_range(2), Bx_range(2), By_range(2), rd_range(2), rk_range(2)];

step_3dp = 0.1;  % 僅用於最終參考四捨五入，不用於搜尋本身

% 運動學限制條件
req_margin             = 0.;
minTransAngleReq       = 0.0;
transAngleSafetyMargin = 0.0;
maxAllowedRangeAvg     = 0.5;      % 鋪翼中線 (midpoint) 誤差門檻 (deg)
maxSwingCap            = 210.0;
swingSafetyMargin      = 0;

swingBmax_lower = 180.0;
swingBmax_upper = 190.0;
swingBmin_lower = 50.0;
swingBmin_upper = 80.0;

USE_HARD_SWING_CONSTRAINTS   = false;
USE_HARD_MIDPOINT_CONSTRAINT = true;

nBSamples = 500;                          % 最終驗證/繪圖用高解析度
b_samples = linspace(b_min, b_max, nBSamples);

nBSamples_opt = 41;                       % 搜尋(PSO+SQP)階段用粗解析度，加速評估
b_samples_opt = linspace(b_min, b_max, nBSamples_opt);

w_size  = 0.05;
w_close = 0.50;
w_inv   = 0.20;

fprintf('=========== 啟動【particleswarm(全域)+fmincon(SQP,局部精修)混合式】最佳化 ===========\n');
fprintf('swing(b_max) 目標範圍 = [%.1f, %.1f] deg (最大鋪翼)\n', swingBmax_lower, swingBmax_upper);
fprintf('swing(b_min) 目標範圍 = [%.1f, %.1f] deg (最小鋪翼，獨立指定)\n', swingBmin_lower, swingBmin_upper);
fprintf('鋪翼中線誤差門檻 = %.1f deg (%s)\n', maxAllowedRangeAvg, ...
    ternary(USE_HARD_MIDPOINT_CONSTRAINT, '硬約束', '軟懲罰(高權重)'));

%% ---------- 3. 目標函式 (搜尋用粗解析度 / 最終驗證用高解析度) ----------
minTransAngleEffective = minTransAngleReq + transAngleSafetyMargin;

objFun_search = @(x) smoothObjective(x, a_min, a_max, b_min, b_max, b_samples_opt, ...
    req_margin, minTransAngleEffective, w_inv, w_size, maxSwingCap, swingSafetyMargin, ...
    maxAllowedRangeAvg, w_close, ...
    swingBmax_lower, swingBmax_upper, swingBmin_lower, swingBmin_upper, ...
    USE_HARD_SWING_CONSTRAINTS, USE_HARD_MIDPOINT_CONSTRAINT);

objFun_full = @(x) smoothObjective(x, a_min, a_max, b_min, b_max, b_samples, ...
    req_margin, minTransAngleEffective, w_inv, w_size, maxSwingCap, swingSafetyMargin, ...
    maxAllowedRangeAvg, w_close, ...
    swingBmax_lower, swingBmax_upper, swingBmin_lower, swingBmin_upper, ...
    USE_HARD_SWING_CONSTRAINTS, USE_HARD_MIDPOINT_CONSTRAINT);

%% ---------- 4. particleswarm(全域) + fmincon(SQP,HybridFcn局部精修) ----------
seedConfigs_x = [
    10.4,  0.0, 12.0, 11.0,  0.0, 11.4, 11.6;
     8.0,  1.0, 10.0,  9.6, -2.0, 10.0, 10.4;
    12.0, -1.0, 14.0, 13.0,  1.0, 13.0, 13.0;
     7.4,  0.0,  9.0,  8.6,  0.0,  9.0,  9.0;
    14.0,  2.0, 15.0, 15.0, -1.0, 14.0, 15.0
];
if ~isempty(v4SeedX)
    seedConfigs_x = [v4SeedX(:)'; seedConfigs_x];
end
seedConfigs_x = min(max(seedConfigs_x, lb), ub);
nSeed = size(seedConfigs_x, 1);

useParallel = false;
if license('test', 'Distrib_Computing_Toolbox')
    try
        if isempty(gcp('nocreate'))
            parpool;
        end
        useParallel = true;
    catch
        useParallel = false;
    end
end

fminconOpts = optimoptions('fmincon', ...
    'Algorithm', 'sqp', ...
    'Display', 'off', ...
    'MaxFunctionEvaluations', 3000, ...
    'MaxIterations', 400, ...
    'OptimalityTolerance', 1e-8, ...
    'StepTolerance', 1e-10, ...
    'SpecifyObjectiveGradient', false);

psoOpts = optimoptions('particleswarm', ...
    'SwarmSize', 300, ...
    'MaxIterations', 250, ...
    'MaxStallIterations', 60, ...
    'UseParallel', useParallel, ...
    'Display', 'iter', ...
    'HybridFcn', {@fmincon, fminconOpts});   % PSO收斂後自動接力fmincon(SQP)精修

nOuterRuns = 30;     % 外層獨立重跑次數，模擬 multi-start 穩健度
FEASIBLE_VAL_THRESHOLD = 1000;   % 遠低於任何懲罰量級(5e2~5e5)，視為已落在可行盆地

bestX   = [];
bestVal = inf;

for run_i = 1:nOuterRuns
    rng(run_i);

    nInit = min(psoOpts.SwarmSize, nSeed);
    initSwarm = nan(psoOpts.SwarmSize, 7);
    for s = 1:nInit
        span = (ub - lb);
        pert = (rand(1,7) - 0.5) .* span * 0.2;
        initSwarm(s, :) = min(max(seedConfigs_x(mod(s-1, nSeed) + 1, :) + pert, lb), ub);
    end
    remaining = psoOpts.SwarmSize - nInit;
    if remaining > 0
        if exist('lhsdesign', 'file') == 2
            Xlhs = lhsdesign(remaining, 7);
        else
            Xlhs = rand(remaining, 7);
        end
        initSwarm(nInit+1:end, :) = lb + Xlhs .* (ub - lb);
    end
    psoOptsRun = optimoptions(psoOpts, 'InitialSwarmMatrix', initSwarm);

    [xRun, fRun, exitflagRun, ~] = particleswarm(objFun_search, 7, lb, ub, psoOptsRun);

    fprintf('  [第 %2d/%2d 輪] fVal=%.6f  exitflag=%d\n', run_i, nOuterRuns, fRun, exitflagRun);

    if fRun < bestVal
        bestVal = fRun;
        bestX   = xRun;
    end

    if bestVal < FEASIBLE_VAL_THRESHOLD
        fprintf('  已找到可行解 (bestVal=%.4f < %d)，提前結束外層搜尋。\n', bestVal, FEASIBLE_VAL_THRESHOLD);
        break;
    end
end

fprintf('外層 PSO+SQP 混合搜尋完成：bestVal(粗解析度) = %.6f\n', bestVal);

if isempty(bestX) || bestVal >= 1e6
    error(['未能找到完全滿足所有約束的可行解。可能是需求本身在目前搜尋範圍內過緊' ...
        '(例如 swing(b_min)=%.0f~%.0f° 與 swing(b_max)=%.0f~%.0f° 差距很大、' ...
        '同時鋪翼中線誤差還要<=%.1f°)。建議：放寬 maxAllowedRangeAvg、放寬swing範圍、' ...
        '擴大幾何搜尋範圍(Gx/Gy/rG/Bx/By/rd/rk)，或增加 nOuterRuns/SwarmSize後重試。'], ...
        swingBmin_lower, swingBmin_upper, swingBmax_lower, swingBmax_upper, maxAllowedRangeAvg);
end

% 用完整解析度(500點)對最佳解再做一次 fmincon 局部精修，確保報告數值收斂
[bestX_refined, bestVal_refined] = fmincon(objFun_full, bestX, [], [], [], [], lb, ub, [], fminconOpts);
if bestVal_refined < bestVal
    bestX   = bestX_refined;
    bestVal = bestVal_refined;
end
fprintf('高解析度(500點)精修後：bestVal = %.6f\n', bestVal);

bestX = min(max(bestX, lb), ub);

Gx_opt = bestX(1); Gy_opt = bestX(2); rG_opt = bestX(3);
Bx_opt = bestX(4); By_opt = bestX(5); rd_opt = bestX(6); rk_opt = bestX(7);
G_opt  = [Gx_opt, Gy_opt];
B_opt  = [Bx_opt, By_opt];

%% ---------- 5. 高解析度運動學驗證與報告 ----------
[minMarginFinal, muMinEffFinal] = geometryChecks(G_opt, rG_opt, B_opt, rd_opt, rk_opt, a_min, a_max, b_min, b_max, 61, 41);

avgList        = nan(1, nBSamples);
swingList      = nan(1, nBSamples);
theta_lo_list  = nan(1, nBSamples);
theta_hi_list  = nan(1, nBSamples);
theta_a0_list  = nan(1, nBSamples);
monotonic_list = false(1, nBSamples);

for i = 1:nBSamples
    info_i = swingInfo(G_opt, rG_opt, B_opt, rd_opt, rk_opt, b_samples(i), a_min, a_max, 201);
    theta_lo_list(i)  = info_i.theta_lo;
    theta_hi_list(i)  = info_i.theta_hi;
    theta_a0_list(i)  = info_i.theta_a0;
    monotonic_list(i) = info_i.monotonic;
    avgList(i)        = (info_i.theta_lo + info_i.theta_hi) / 2;
    swingList(i)      = info_i.s;
end

valid_idx = ~isnan(avgList) & ~isnan(swingList);
if any(valid_idx)
    avgRange = max(avgList(valid_idx)) - min(avgList(valid_idx));
else
    avgRange = NaN;
end

if ~isnan(swingList(1))
    swing_bmin_final = swingList(1);
else
    idxFirst = find(~isnan(swingList),1,'first');
    swing_bmin_final = NaN;
    if ~isempty(idxFirst)
        swing_bmin_final = swingList(idxFirst);
        warning('b_min 位置的 swing 為 NaN，使用第一個有效樣本（idx=%d）代替。', idxFirst);
    end
end

if ~isnan(swingList(end))
    swing_bmax_final = swingList(end);
else
    idxLast = find(~isnan(swingList),1,'last');
    swing_bmax_final = NaN;
    if ~isempty(idxLast)
        swing_bmax_final = swingList(idxLast);
        warning('b_max 位置的 swing 為 NaN，使用最後一個有效樣本（idx=%d）代替。', idxLast);
    end
end

safeDenom = max([swing_bmin_final, 1e-3]);
increasePct_final = (swing_bmax_final - swing_bmin_final) / safeDenom;  % 僅供參考，非限制條件

fprintf('\n================== 連續空間最佳化尺寸 (particleswarm+fmincon混合) ==================\n');
fprintf('G 點座標 (Gx, Gy)  = (%.4f, %.4f) mm\n', Gx_opt, Gy_opt);
fprintf('延伸圓半徑 rG      = %.4f mm\n', rG_opt);
fprintf('B 點座標 (Bx, By)  = (%.4f, %.4f) mm\n', Bx_opt, By_opt);
fprintf('搖桿半徑 rd        = %.4f mm\n', rd_opt);
fprintf('耦桿半徑 rk        = %.4f mm\n', rk_opt);
fprintf('【全域運動學性能驗證】：\n');
fprintf('  - 全程最小死點安全餘裕 = %.4f mm (門檻: >= %.2f mm)\n', minMarginFinal, req_margin);
fprintf('  - 全程最小傳動角       = %.2f deg (門檻: >= %.1f deg)\n', muMinEffFinal, minTransAngleReq);
fprintf('  - 最大鋪翼 swing(b_max) = %.2f deg (目標: %.1f ~ %.1f deg)\n', swing_bmax_final, swingBmax_lower, swingBmax_upper);
fprintf('  - 最小鋪翼 swing(b_min) = %.2f deg (目標: %.1f ~ %.1f deg)\n', swing_bmin_final, swingBmin_lower, swingBmin_upper);
fprintf('  - 鋪翼中線誤差         = %.3f deg (門檻: <= %.1f deg)\n', avgRange, maxAllowedRangeAvg);
fprintf('  - (參考) 擺幅增加率    = %.2f%% (非限制條件，僅供參考)\n', increasePct_final*100);

fprintf('\n【最終可行性檢查】\n');
checks = { ...
    '死點餘裕',          minMarginFinal >= req_margin; ...
    '傳動角',            muMinEffFinal >= minTransAngleReq; ...
    'swing(bmax)範圍',   swing_bmax_final >= swingBmax_lower && swing_bmax_final <= swingBmax_upper; ...
    'swing(bmin)範圍',   swing_bmin_final >= swingBmin_lower && swing_bmin_final <= swingBmin_upper; ...
    '鋪翼中線誤差',      avgRange <= maxAllowedRangeAvg; ...
    '運動單調性(全樣本)', all(monotonic_list(valid_idx)) ...
};
allPass = true;
for i = 1:size(checks,1)
    status = checks{i,2};
    allPass = allPass && status;
    fprintf('  %-16s : %s\n', checks{i,1}, ternary(status,'PASS','FAIL'));
end
if allPass
    fprintf('\n>>> 所有限制皆滿足，此組連續空間解為可行解。\n');
else
    fprintf(2, ['\n[警告] 目前最佳解並未完全滿足所有限制(見上方FAIL項目)，' ...
                '請放寬相關限制、增加 nOuterRuns/SwarmSize，或檢查各項限制彼此是否矛盾後重跑。\n']);
end


%% ---------- 5b. 參考：四捨五入到 0.1mm 網格後的可行性覆核 ----------
bestX_rounded = round(bestX / step_3dp) * step_3dp;
bestX_rounded = min(max(bestX_rounded, lb), ub);
Gr = [bestX_rounded(1), bestX_rounded(2)];
Br = [bestX_rounded(4), bestX_rounded(5)];
rGr = bestX_rounded(3); rdr = bestX_rounded(6); rkr = bestX_rounded(7);

[minMarginR, muMinEffR] = geometryChecks(Gr, rGr, Br, rdr, rkr, a_min, a_max, b_min, b_max, 61, 41);
infoBmaxR = swingInfo(Gr, rGr, Br, rdr, rkr, b_max, a_min, a_max, 401);
infoBminR = swingInfo(Gr, rGr, Br, rdr, rkr, b_min, a_min, a_max, 401);
swingBmaxR = infoBmaxR.s; swingBminR = infoBminR.s;

fprintf('\n--- 參考：四捨五入到 %.1fmm 網格後 (供3D列印加工用) ---\n', step_3dp);
fprintf('G=(%.1f,%.1f) rG=%.1f B=(%.1f,%.1f) rd=%.1f rk=%.1f\n', ...
    Gr(1), Gr(2), rGr, Br(1), Br(2), rdr, rkr);
fprintf('  死點餘裕=%.4f (>=%.2f)  傳動角=%.2f (>=%.1f)  swing(bmax)=%.2f  swing(bmin)=%.2f\n', ...
    minMarginR, req_margin, muMinEffR, minTransAngleReq, swingBmaxR, swingBminR);
roundedPass = (minMarginR >= req_margin) && (muMinEffR >= minTransAngleReq) && ...
    (swingBmaxR >= swingBmax_lower) && (swingBmaxR <= swingBmax_upper) && ...
    (swingBminR >= swingBmin_lower) && (swingBminR <= swingBmin_upper);
fprintf('  四捨五入後仍滿足全部限制: %s\n', ternary(roundedPass, '是', '否 (建議以連續解為準，或重跑離散版微調)'));

T = table((1:nBSamples)', b_samples(:), theta_lo_list(:), theta_hi_list(:), theta_a0_list(:), avgList(:), swingList(:), monotonic_list(:), ...
    'VariableNames', {'idx','b_mm','theta_lo_deg','theta_hi_deg','theta_a0_deg','midpoint_deg','swing_deg','monotonic'});
writetable(T, 'midpoint_samples.csv');
fprintf('已輸出 midpoint_samples.csv\n');
% --- 在第 5 段、填完 theta_* 與 valid_idx 後加入以下判斷與輸出 ---
valid = valid_idx;   % 既有變數
if ~any(valid)
    warning('沒有有效樣本，無法計算中心角。');
else
    % 取有效樣本並做 unwrap（先轉弧度再 unwrap 再轉回度）
    midpts = avgList(valid);            % (theta_lo+theta_hi)/2 (deg)
    midpts_un = rad2deg(unwrap(deg2rad(midpts)));

    thetaA0 = theta_a0_list(valid);     % theta at a=0 (deg)
    thetaA0_un = rad2deg(unwrap(deg2rad(thetaA0)));

    % 統計值
    mean_mid = mean(midpts_un);
    median_mid = median(midpts_un);
    std_mid = std(midpts_un);

    mean_thetaA0 = mean(thetaA0_un);
    median_thetaA0 = median(thetaA0_un);

    % 代表性單點：b 的中間樣本（或最接近 b=0 的索引）
    midIndex = round(numel(b_samples)/2);
    % 找 nearest valid index to midIndex
    validIdxList = find(valid);
    [~, idxNearest] = min(abs(validIdxList - midIndex));
    repIdx = validIdxList(idxNearest);  % 全域索引
    rep_b = b_samples(repIdx);
    rep_mid_deg = rad2deg(unwrap(deg2rad((theta_lo_list(repIdx)+theta_hi_list(repIdx))/2)));
    rep_thetaA0_deg = theta_a0_list(repIdx);

    % 列印結果
    fprintf('\n--- 撲翼範圍中心角（相對 x 軸）統計 ---\n');
    fprintf('所有有效樣本中心角 mean = %.4f°  median = %.4f°  std = %.4f°\n', mean_mid, median_mid, std_mid);
    fprintf('a=0 處角 theta_a0 mean = %.4f°  median = %.4f°\n', mean_thetaA0, median_thetaA0);
    fprintf('代表樣本 (b ≈ %.4f mm, idx=%d): midpoint = %.4f°  theta_a0 = %.4f°\n', rep_b, repIdx, rep_mid_deg, rep_thetaA0_deg);
end

%% ---------- 6. 運動學診斷繪圖 ----------
figure('Name', '連桿運動學與幾何診斷 (PSO+SQP混合解)', 'Position', [100, 100, 1000, 700]);

subplot(2,2,1);
aa = linspace(a_min, a_max, 101);
th_max = nan(1,101); th_min = nan(1,101);
for i=1:101
    A_max = [b_max, aa(i)]; I_m = IfromA(A_max, G_opt, rG_opt); K_m = circleIntersect(I_m, rk_opt, B_opt, rd_opt);
    th_max(i) = atan2(K_m(2)-B_opt(2), K_m(1)-B_opt(1));
    A_min = [b_min, aa(i)]; I_mn = IfromA(A_min, G_opt, rG_opt); K_mn = circleIntersect(I_mn, rk_opt, B_opt, rd_opt);
    th_min(i) = atan2(K_mn(2)-B_opt(2), K_mn(1)-B_opt(1));
end
plot(aa, rad2deg(unwrap(th_max)), 'r-', 'LineWidth', 2); hold on;
plot(aa, rad2deg(unwrap(th_min)), 'b--', 'LineWidth', 1.5);
grid on; xlabel('行程 A_y (a)'); ylabel('撲翼角度 \theta (deg)');
legend('b=b_{max}', 'b=b_{min}', 'Location', 'best');
title(sprintf('擺角曲線 (b_{max}擺角=%.1f°)', swing_bmax_final));

subplot(2,2,2);
mu_curve = nan(1,101);
for i=1:101
    A_max = [b_max, aa(i)]; I_m = IfromA(A_max, G_opt, rG_opt); K_m = circleIntersect(I_m, rk_opt, B_opt, rd_opt);
    v1 = I_m - K_m; v2 = B_opt - K_m;
    cosMu = max(-1, min(1, dot(v1,v2)/(norm(v1)*norm(v2))));
    mu_curve(i) = rad2deg(acos(cosMu));
end
plot(aa, mu_curve, 'g-', 'LineWidth', 2); hold on;
yline(40, 'k--', '40° 建議下限'); yline(minTransAngleReq, 'r--', sprintf('%.0f° 硬門檻', minTransAngleReq));
grid on; xlabel('行程 A_y (a)'); ylabel('傳動角 \mu (deg)'); ylim([0 180]);
title(sprintf('傳動角分佈 (最小傳動角=%.1f°)', muMinEffFinal));

subplot(2,2,3);
plot(b_samples, avgList, 'o-m', 'LineWidth', 1.8, 'MarkerFaceColor', 'm');
grid on; xlabel('拉桿 A_x (b)'); ylabel('中點角度 (\theta_{lo}+\theta_{hi})/2 (deg)');
title(sprintf('中點角度穩定性 (變動範圍=%.2f° \\le %.1f°)', avgRange, maxAllowedRangeAvg));
hold on;
Nmark = max(1, floor(nBSamples/20));
valid_marks = find(valid_idx);
for k = valid_marks(1:Nmark:end)
    text(b_samples(k), avgList(k), sprintf(' %d:%.1f°', k, avgList(k)), 'FontSize',8);
end
hold off;

subplot(2,2,4);
hold on; axis equal; grid on;
viscircles(G_opt, rG_opt, 'Color', [0.7 0.7 0.7], 'LineStyle', ':');
viscircles(B_opt, rd_opt, 'Color', [0.3 0.6 1], 'LineStyle', '--');
plot(G_opt(1), G_opt(2), 'ks', 'MarkerFaceColor','k'); text(G_opt(1), G_opt(2)-1, 'G');
plot(B_opt(1), B_opt(2), 'ks', 'MarkerFaceColor','k'); text(B_opt(1), B_opt(2)-1, 'B');

colors = {[0.85 0.2 0.2], [0.2 0.6 0.2], [0.2 0.2 0.85]};
aVals = [a_min, 0, a_max];
for t = 1:3
    At = [b_max, aVals(t)]; It = IfromA(At, G_opt, rG_opt); Kt = circleIntersect(It, rk_opt, B_opt, rd_opt);
    plot([At(1) G_opt(1)], [At(2) G_opt(2)], '-', 'Color', colors{t}*0.5+0.5);
    plot([It(1) Kt(1)], [It(2) Kt(2)], '-', 'Color', colors{t}, 'LineWidth', 1.5);
    plot([B_opt(1) Kt(1)], [B_opt(2) Kt(2)], '-', 'Color', colors{t}, 'LineWidth', 2.5);
    plot(Kt(1), Kt(2), 'p', 'Color', colors{t}, 'MarkerFaceColor', colors{t}, 'MarkerSize', 8);
end
title(sprintf('PSO+SQP混合解機構姿態 (rd=%.2f, rk=%.2f, rG=%.2f)', rd_opt, rk_opt, rG_opt));
xlabel('x'); ylabel('y');

fprintf('\n=========== 程式執行完畢 ===========\n');

%% ======================= 區域輔助函式 (與 v10 相同) =======================
function val = smoothObjective(x, a_min, a_max, b_min, b_max, b_samples, ...
    req_margin, minTransAngleReq, w_inv, w_size, maxSwingCap, swingSafetyMargin, ...
    maxAllowedRangeAvg, w_close, ...
    swingBmax_lower, swingBmax_upper, swingBmin_lower, swingBmin_upper, ...
    USE_HARD_SWING_CONSTRAINTS, USE_HARD_MIDPOINT_CONSTRAINT)

    Gx=x(1); Gy=x(2); rG=x(3); Bx=x(4); By=x(5); rd=x(6); rk=x(7);
    G = [Gx,Gy]; B = [Bx,By];

    if rd<=0.2 || rk<=0.2 || rG<=0.2
        val = 1e9; return;
    end

    na = 17; nb = 9;
    minMargin = inf; muMinEff = inf;
    aa = linspace(a_min, a_max, na);
    bb = linspace(b_min, b_max, nb);
    for b = bb
        for a = aa
            A = [b, a];
            v = G - A;
            I = G + rG * v / max(1e-9, norm(v));
            d = B - I; D = norm(d);
            m = min((rk+rd)-D, D-abs(rk-rd));
            minMargin = min(minMargin, m);

            if D <= rk+rd && D >= abs(rk-rd) && D > 1e-9
                a_ = (rk^2 - rd^2 + D^2)/(2*D);
                h2 = rk^2 - a_^2;
                if h2 >= 0
                    h = sqrt(h2);
                    P2 = I + a_ * d / D;
                    perp = [-d(2), d(1)] / D * h;
                    K = P2 - perp;
                    v1 = I - K; v2 = B - K;
                    cosMu = max(-1, min(1, dot(v1,v2)/(norm(v1)*norm(v2))));
                    mu = rad2deg(acos(cosMu));
                    muMinEff = min(muMinEff, min(mu, 180-mu));
                else
                    muMinEff = 0;
                end
            else
                muMinEff = 0;
            end
        end
    end

    nBS = numel(b_samples);
    avgs = zeros(1, nBS); swings = zeros(1, nBS);
    allMonotonic = true;
    for i = 1:nBS
        info_i = swingInfo(G, rG, B, rd, rk, b_samples(i), a_min, a_max, 31);
        if isnan(info_i.s) || ~info_i.monotonic
            allMonotonic = false;
        end
        avgs(i) = (info_i.theta_lo + info_i.theta_hi)/2;
        swings(i) = info_i.s;
    end

    if all(isnan(swings))
        val = 1e9; return;
    end

    validSwingIdx = ~isnan(swings);
    swing_bmin = swings(find(validSwingIdx,1,'first'));
    swing_bmax = swings(find(validSwingIdx,1,'last'));
    rangeAvg = max(avgs(validSwingIdx)) - min(avgs(validSwingIdx));

    if USE_HARD_MIDPOINT_CONSTRAINT && (rangeAvg > maxAllowedRangeAvg)
        val = 1e9; return;
    end

    pen = 0;
    pen = pen + max(0, req_margin - minMargin) * 5000;
    pen = pen + max(0, minTransAngleReq - muMinEff) * 2000;
    pen = pen + max(0, swing_bmax - (maxSwingCap - swingSafetyMargin)) * 5000;
    if ~allMonotonic
        pen = pen + 30000;
    end

    if ~USE_HARD_MIDPOINT_CONSTRAINT
        pen = pen + max(0, rangeAvg - maxAllowedRangeAvg)^2 * 5e5;
    end

    W_bmax_low  = 5e5;
    W_bmax_high = 5e5;
    W_bmin_low  = 5e5;
    W_bmin_high = 5e5;

    viol_bmax_low  = max(0, swingBmax_lower - swing_bmax);
    viol_bmax_high = max(0, swing_bmax - swingBmax_upper);
    viol_bmin_low  = max(0, swingBmin_lower - swing_bmin);
    viol_bmin_high = max(0, swing_bmin - swingBmin_upper);

    if USE_HARD_SWING_CONSTRAINTS
        if (viol_bmax_low > 0) || (viol_bmax_high > 0) || (viol_bmin_low > 0) || (viol_bmin_high > 0)
            val = 1e9; return;
        end
    else
        pen = pen + W_bmax_low  * viol_bmax_low^2;
        pen = pen + W_bmax_high * viol_bmax_high^2;
        pen = pen + W_bmin_low  * viol_bmin_low^2;
        pen = pen + W_bmin_high * viol_bmin_high^2;
    end

    swingLimit = maxSwingCap - swingSafetyMargin;
    distToCap = max(0, swingLimit - swing_bmax);
    val = w_close * distToCap^2 + w_inv * rangeAvg^2 + w_size * (rG+rd+rk) + pen;
end

function I = IfromA(A, G, rG)
    v = G - A;
    I = G + rG * v / max(1e-9, norm(v));
end

function K = circleIntersect(I, rk, B, rd)
    d = B - I;
    D = norm(d);
    if D > rk+rd || D < abs(rk-rd) || D < 1e-9
        K = [NaN, NaN]; return;
    end
    a_ = (rk^2 - rd^2 + D^2) / (2*D);
    h2 = rk^2 - a_^2;
    if h2 < 0
        K = [NaN, NaN]; return;
    end
    h = sqrt(h2);
    P2 = I + a_ * d / D;
    perp = [-d(2), d(1)] / D * h;
    K = P2 - perp;
end

function [m, muMinEff] = geometryChecks(G, rG, B, rd, rk, a_min, a_max, b_min, b_max, na, nb)
    m = inf;
    muMinEff = inf;
    aa = linspace(a_min, a_max, na);
    bb = linspace(b_min, b_max, nb);
    for b = bb
        for a = aa
            A = [b, a];
            I = IfromA(A, G, rG);
            d = B - I; D = norm(d);
            m = min(m, min((rk+rd)-D, D-abs(rk-rd)));
            K = circleIntersect(I, rk, B, rd);
            if any(isnan(K))
                muMinEff = 0; continue;
            end
            v1 = I - K; v2 = B - K;
            nv1 = norm(v1); nv2 = norm(v2);
            if nv1 < 1e-9 || nv2 < 1e-9
                muMinEff = 0; continue;
            end
            cosMu = max(-1, min(1, dot(v1, v2) / (nv1 * nv2)));
            mu = rad2deg(acos(cosMu));
            muMinEff = min(muMinEff, min(mu, 180 - mu));
        end
    end
end

function res = swingInfo(G, rG, B, rd, rk, b, a_min, a_max, n)
    aa = linspace(a_min, a_max, n);
    th = nan(1, n);
    for i = 1:n
        A = [b, aa(i)];
        I = IfromA(A, G, rG);
        K = circleIntersect(I, rk, B, rd);
        if any(isnan(K))
            res.s = NaN; res.monotonic = false;
            res.theta_lo = NaN; res.theta_hi = NaN; res.theta_a0 = NaN;
            return;
        end
        th(i) = atan2(K(2)-B(2), K(1)-B(1));
    end
    th = unwrap(th);
    dth = diff(th);
    monotonic = (all(dth >= -1e-5) || all(dth <= 1e-5)) && (max(abs(dth)) > 1e-4);
    [~, idx0] = min(abs(aa - 0));
    res.s         = rad2deg(max(th) - min(th));
    res.monotonic = monotonic;
    res.theta_lo  = rad2deg(th(1));
    res.theta_hi  = rad2deg(th(end));
    res.theta_a0  = rad2deg(th(idx0));
end

function s = ternary(cond, a, b)
    if cond, s = a; else, s = b; end
end