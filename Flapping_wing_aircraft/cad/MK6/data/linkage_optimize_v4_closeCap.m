%% linkage_optimize_v6_pureHardConstraints.m
% 在 v5_hardRange 基礎上修改：
%   1. 把「角度中點變動範圍 avgRange (=max(avgList)-min(avgList))」也
%      改成【可調硬性範圍】：avgRange 必須 <= avgRange_max (硬性上限，
%      下限本來就是0，故只需設上限)。
%   2. 拿掉之前所有「懲罰/獎勵」評分機制：
%        - w_inv (中點變動範圍的平方懲罰)
%        - w_size (尺寸越小獎勵)
%        - w_close (擺角逼近上限的獎勵)
%        - 以及原本用 1e7*(超出量+1) 手刻的漸進式罰分
%      全部移除。現在死點餘裕、角度中點變動範圍、swing(b_min)、
%      swing(b_max) 四項，全部改用 fmincon 的【非線性不等式限制式
%      (nonlcon, c(x)<=0)】來硬性要求，不再有任何「越接近越好」的
%      連續評分。
%   3. 因為不再有任何評分/獎勵，目標函式改成常數 0（純可行性問題）：
%      只要找到「同時滿足全部硬性限制」的一組 (G, rG, B, rd, rk)
%      即為解，不再追求「越小」或「越逼近邊界越好」。
%      multistart 找到第一組可行解就停止（結果由 rng(1) 決定，具重現性）。
%
% 重要說明：
%   本版需要 Optimization Toolbox (fmincon)。
%
clear; clc; close all;
rng(1);

%% ---------- 1. 已知固定參數 ----------
a_min = -5;   a_max =  5;       % A_y 範圍 (已知)
b_min = -3.5; b_max = 3.5;      % A_x 範圍 (已知；你已改成對稱範圍)

%% ---------- 2. 未知數搜尋範圍 (共7個：Gx,Gy,rG,Bx,By,rd,rk) ----------
Gx_range = [5, 20];
Gy_range = [-1, 1];
rG_range = [6., 30];

Bx_range = [10, 20];
By_range = [-1, 1];

rd_range = [6., 30];
rk_range = [6., 30];

% --- fmincon 邊界向量 (lb/ub) ---
lb = [Gx_range(1), Gy_range(1), rG_range(1), Bx_range(1), By_range(1), rd_range(1), rk_range(1)];
ub = [Gx_range(2), Gy_range(2), rG_range(2), Bx_range(2), By_range(2), rd_range(2), rk_range(2)];

req_margin = 0.05;     % 死點安全餘裕 (硬性)
nTrials    = 2000;      % multistart 起始點數量上限（找到第一組可行解就停止）
nBSamples  = 5;        % 用幾個 b 代表點檢查「角度中點」與擺幅

% ======================= 硬性範圍設定 (全部可調) =======================
% *** 請依實際需求調整以下三組數字 ***
avgRange_max    = 0.5;           % 角度中點(兩端平均值)在整個 b 範圍內的
                                % 變動幅度上限 (deg)。下限恆為0，故只設上限。
swingBmin_range = [60, 80];    % b=b_min 時，擺角必須落在此範圍 (deg)
swingBmax_range = [180, 198];    % b=b_max 時，擺角必須落在此範圍 (deg)
% =======================================================================

if avgRange_max <= 0
    error('avgRange_max 必須為正值。');
end
if swingBmin_range(1) < 0 || swingBmax_range(1) < 0
    error('swingBmin_range / swingBmax_range 下限不可為負值。');
end

b_samples = linspace(b_min, b_max, nBSamples);   % b_samples(1)=b_min, b_samples(end)=b_max

fprintf('=========== 機構可行解搜尋開始（純硬性限制，無評分機制）===========\n');
fprintf('  死點餘裕 >= %.2f\n', req_margin);
fprintf('  中點變動範圍 <= %.2f deg\n', avgRange_max);
fprintf('  swing(b_min) in [%.1f, %.1f] deg\n', swingBmin_range(1), swingBmin_range(2));
fprintf('  swing(b_max) in [%.1f, %.1f] deg\n', swingBmax_range(1), swingBmax_range(2));

%% ---------- 3. 目標函式與限制式 ----------
% 目標函式：常數0，代表本題是「純可行性(feasibility)問題」，
% 不對解做任何優劣評分，只要求同時滿足 nonlcon 的所有硬性限制。
objFun = @(x) 0;

nonlconFun = @(x) hardConstraints(x, a_min, a_max, b_min, b_max, b_samples, ...
                                   req_margin, avgRange_max, swingBmin_range, swingBmax_range, ...
                                   9, 7, 31);

nonlconFunFine = @(x) hardConstraints(x, a_min, a_max, b_min, b_max, b_samples, ...
                                       req_margin, avgRange_max, swingBmin_range, swingBmax_range, ...
                                       25, 17, 121);

%% ---------- 4. multistart：找到第一組可行解就停止 ----------
optsF = optimoptions('fmincon', ...
    'Display','off', ...
    'Algorithm','sqp', ...
    'MaxIterations',1000, ...
    'MaxFunctionEvaluations',2000, ...
    'StepTolerance',1e-3, ...
    'ConstraintTolerance',1e-4, ...
    'OptimalityTolerance',1e-2);

feasTol = 1e-4;   % 判定「c(x) <= 0」是否成立的容許誤差
bestX = [];
attemptLog = zeros(nTrials,1);   % 1=該次起點找到可行解, 0=沒有

for t = 1:nTrials
    x0 = [ Gx_range(1)+rand*diff(Gx_range), Gy_range(1)+rand*diff(Gy_range), ...
           rG_range(1)+rand*diff(rG_range), ...
           Bx_range(1)+rand*diff(Bx_range), By_range(1)+rand*diff(By_range), ...
           rd_range(1)+rand*diff(rd_range), rk_range(1)+rand*diff(rk_range) ];

    try
        [xOpt, ~, exitflag] = fmincon(objFun, x0, [],[],[],[], lb, ub, nonlconFun, optsF);
    catch
        continue;
    end

    if exitflag > 0
        c = nonlconFun(xOpt);
        if all(c <= feasTol)
            attemptLog(t) = 1;
            bestX = xOpt;
            fprintf('第 %d 次起始點即找到可行解，停止 multistart。\n', t);
            break;
        end
    end
end

if isempty(bestX)
    error(['%d 次 multistart 起點都沒找到同時滿足所有硬性限制的解，請放寬 ' ...
           'req_margin / avgRange_max / swingBmin_range / swingBmax_range，或擴大搜尋範圍再試一次。'], nTrials);
end

%% ---------- 5. 局部精修 (用更高解析度的限制式重新確認/微調) ----------
try
    [xOptFine, ~, exitflagFine] = fmincon(objFun, bestX, [],[],[],[], lb, ub, nonlconFunFine, optsF);
    if exitflagFine > 0
        cFine = nonlconFunFine(xOptFine);
        if all(cFine <= feasTol)
            bestX = xOptFine;
        end
    end
catch
    % 精修失敗就沿用 multistart 找到的 bestX
end

bestX = min(max(bestX, lb), ub);

Gx_opt=bestX(1); Gy_opt=bestX(2); rG_opt=bestX(3);
Bx_opt=bestX(4); By_opt=bestX(5); rd_opt=bestX(6); rk_opt=bestX(7);
G_opt = [Gx_opt, Gy_opt]; B_opt = [Bx_opt, By_opt];

%% ---------- 6. 最終高解析度驗證 ----------
minMarginFinal = minMarginOverRange(G_opt, rG_opt, B_opt, rd_opt, rk_opt, ...
    a_min, a_max, b_min, b_max, 61, 41);

infoFinal = swingInfo(G_opt, rG_opt, B_opt, rd_opt, rk_opt, b_max, a_min, a_max, 401);

avgList = nan(1, nBSamples);
swingList = nan(1, nBSamples);
allOkForSamples = true;
for i = 1:nBSamples
    info_i = swingInfo(G_opt, rG_opt, B_opt, rd_opt, rk_opt, b_samples(i), a_min, a_max, 201);
    if isnan(info_i.s) || ~info_i.monotonic
        allOkForSamples = false;
    end
    avgList(i)   = (info_i.theta_lo + info_i.theta_hi) / 2;
    swingList(i) = info_i.s;
end
avgRange = max(avgList) - min(avgList);

swing_bmin_final = swingList(1);
swing_bmax_final = swingList(end);

if minMarginFinal < req_margin || isnan(infoFinal.s) || ~infoFinal.monotonic || ~allOkForSamples
    error('最終高解析度驗證失敗，請重跑或調整搜尋範圍/req_margin。');
end
if avgRange > avgRange_max
    error('最終中點變動範圍 = %.4f deg 超出硬性上限 %.2f deg，請重跑或放寬 avgRange_max。', ...
        avgRange, avgRange_max);
end
if swing_bmin_final < swingBmin_range(1) || swing_bmin_final > swingBmin_range(2)
    error('最終 swing(b_min) = %.4f deg 超出硬性範圍 [%.1f, %.1f]，請重跑或調整搜尋範圍。', ...
        swing_bmin_final, swingBmin_range(1), swingBmin_range(2));
end
if swing_bmax_final < swingBmax_range(1) || swing_bmax_final > swingBmax_range(2)
    error('最終 swing(b_max) = %.4f deg 超出硬性範圍 [%.1f, %.1f]，請重跑或調整搜尋範圍。', ...
        swing_bmax_final, swingBmax_range(1), swingBmax_range(2));
end

xFinal = [Gx_opt, Gy_opt, rG_opt, Bx_opt, By_opt, rd_opt, rk_opt];
tolBound = 1e-6;
if any(xFinal < lb - tolBound) || any(xFinal > ub + tolBound)
    error('最終解超出指定邊界範圍，請檢查 fmincon 設定或邊界是否合理。');
end

swing_opt  = infoFinal.s;
theta_lo_u = infoFinal.theta_lo;
theta_hi_u = infoFinal.theta_hi;
theta_a0_u = infoFinal.theta_a0;
alpha_total = theta_hi_u - theta_lo_u;
sizeMetric = rG_opt + rd_opt + rk_opt;   % 僅供參考，不影響求解過程

fprintf('\n---------- 最終可行解 ----------\n');
fprintf('G 點座標      = (%.4f, %.4f)\n', Gx_opt, Gy_opt);
fprintf('e 圓半徑 rG   = %.4f\n', rG_opt);
fprintf('B 點座標      = (%.4f, %.4f)\n', Bx_opt, By_opt);
fprintf('圓 d 半徑 rd  = %.4f\n', rd_opt);
fprintf('圓 k 半徑 rk  = %.4f\n', rk_opt);
fprintf('尺寸指標 (rG+rd+rk) = %.4f  (僅供參考，未參與求解)\n', sizeMetric);
fprintf('全程最小死點餘裕 = %.4f (需求 >= %.2f)\n', minMarginFinal, req_margin);
fprintf('A 最右側(b=%.2f)時 BK 擺角 = %.4f deg\n', b_max, swing_opt);
fprintf('真實總擺角 = %.4f deg\n', alpha_total);

fprintf('\n【硬性限制檢查】\n');
fprintf('  中點變動範圍 = %.4f deg  (硬性上限 %.2f deg)\n', avgRange, avgRange_max);
fprintf('  swing(b_min=%.2f) = %.4f deg  (硬性範圍 [%.1f, %.1f])\n', ...
    b_min, swing_bmin_final, swingBmin_range(1), swingBmin_range(2));
fprintf('  swing(b_max=%.2f) = %.4f deg  (硬性範圍 [%.1f, %.1f])\n', ...
    b_max, swing_bmax_final, swingBmax_range(1), swingBmax_range(2));

fprintf('\n【角度中點(兩端平均) 各 b 樣本點數值，共 %d 點】\n', nBSamples);
for i = 1:nBSamples
    fprintf('  b=%.3f  中點平均角度 = %.4f deg  |  擺角 = %.4f deg\n', b_samples(i), avgList(i), swingList(i));
end

fprintf('\n【邊界確認】\n');
fprintf('  Gx=%.3f in [%.1f,%.1f] | Gy=%.3f in [%.1f,%.1f] | rG=%.3f in [%.1f,%.1f]\n', ...
    Gx_opt, Gx_range(1), Gx_range(2), Gy_opt, Gy_range(1), Gy_range(2), rG_opt, rG_range(1), rG_range(2));
fprintf('  Bx=%.3f in [%.1f,%.1f] | By=%.3f in [%.1f,%.1f]\n', ...
    Bx_opt, Bx_range(1), Bx_range(2), By_opt, By_range(1), By_range(2));
fprintf('  rd=%.3f in [%.1f,%.1f] | rk=%.3f in [%.1f,%.1f]\n', ...
    rd_opt, rd_range(1), rd_range(2), rk_opt, rk_range(1), rk_range(2));

%% ---------- 7. 繪圖 ----------
figure('Name','角度中點 vs A_x (b)');
plot(b_samples, avgList, 'o-', 'LineWidth', 1.5, 'MarkerFaceColor','b');
xlabel('b (A_x)'); ylabel('兩端角度平均值 (deg)');
title(sprintf('角度中點 vs b (變動範圍 = %.3f deg，硬性上限 = %.2f deg)', avgRange, avgRange_max));
grid on;

figure('Name','擺角 vs A_x (b)，檢查硬性範圍');
plot(b_samples, swingList, 'o-', 'LineWidth', 1.5, 'Color',[0.85 0.2 0.2], 'MarkerFaceColor','r');
hold on;
yline(swingBmin_range(1), '--', 'b\_min 下限', 'Color',[0.2 0.2 0.85]);
yline(swingBmin_range(2), '--', 'b\_min 上限', 'Color',[0.2 0.2 0.85]);
yline(swingBmax_range(1), '--', 'b\_max 下限', 'Color',[0.2 0.6 0.2]);
yline(swingBmax_range(2), '--', 'b\_max 上限', 'Color',[0.2 0.6 0.2]);
xlabel('b (A_x)'); ylabel('擺角 (deg)');
title(sprintf('擺角 vs b (b_{min}=%.2f deg in [%.1f,%.1f], b_{max}=%.2f deg in [%.1f,%.1f])', ...
    swing_bmin_final, swingBmin_range(1), swingBmin_range(2), ...
    swing_bmax_final, swingBmax_range(1), swingBmax_range(2)));
grid on;

figure('Name','機構示意圖 (a = -5, 0, 5，b 在最右側)');
hold on; axis equal; grid on;
viscircles(G_opt, rG_opt, 'Color', [0.7 0.7 0.7], 'LineStyle', ':');
plot(G_opt(1), G_opt(2), 'ks', 'MarkerFaceColor','k'); text(G_opt(1), G_opt(2)-1, 'G');
plot(B_opt(1), B_opt(2), 'ks', 'MarkerFaceColor','k'); text(B_opt(1), B_opt(2)-1, 'B');
viscircles(B_opt, rd_opt, 'Color', [0.3 0.6 1], 'LineStyle', '--');

colors = {[0.85 0.2 0.2], [0.2 0.6 0.2], [0.2 0.2 0.85]};
labels = {sprintf('a=%.0f (下端)',a_min), 'a=0 (中點)', sprintf('a=%.0f (上端)',a_max)};
aVals = [a_min, 0, a_max];
for t = 1:3
    A_t = [b_max, aVals(t)];
    I_t = IfromA(A_t, G_opt, rG_opt);
    K_t = circleIntersect(I_t, rk_opt, B_opt, rd_opt);
    plot([A_t(1) G_opt(1)], [A_t(2) G_opt(2)], '-', 'Color', colors{t}*0.5+0.5);
    plot(A_t(1), A_t(2), 'o', 'Color', colors{t}, 'MarkerFaceColor', colors{t});
    plot(I_t(1), I_t(2), '^', 'Color', colors{t}, 'MarkerFaceColor', colors{t});
    plot([I_t(1) K_t(1)], [I_t(2) K_t(2)], '-', 'Color', colors{t}, 'LineWidth', 1.5);
    plot([B_opt(1) K_t(1)], [B_opt(2) K_t(2)], '-', 'Color', colors{t}, 'LineWidth', 2.5);
    plot(K_t(1), K_t(2), 'p', 'Color', colors{t}, 'MarkerFaceColor', colors{t}, 'MarkerSize', 10);
end
legend(labels, 'Location', 'bestoutside');
title(sprintf('rd=%.3f, rk=%.3f, 總擺角=%.2f deg, 中點變動=%.2f deg', ...
    rd_opt, rk_opt, alpha_total, avgRange));
xlabel('x'); ylabel('y');

fprintf('\n=========== 完成 ===========\n');

%% ======================= 區域函式 =======================

function I = IfromA(A, G, rG)
    v = G - A;
    I = G + rG * v / norm(v);
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

function m = minMarginOverRange(G, rG, B, rd, rk, a_min, a_max, b_min, b_max, na, nb)
    m = inf;
    aa = linspace(a_min, a_max, na);
    bb = linspace(b_min, b_max, nb);
    for b = bb
        for a = aa
            A = [b, a];
            I = IfromA(A, G, rG);
            D = norm(B - I);
            m = min(m, min((rk+rd)-D, D-abs(rk-rd)));
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

function [c, ceq] = hardConstraints(x, a_min, a_max, b_min, b_max, b_samples, ...
                                     req_margin, avgRange_max, swingBmin_range, swingBmax_range, ...
                                     na, nb, nSwing)
    % 純硬性不等式限制式：c(x) <= 0 才算滿足。
    % 沒有任何評分/獎勵/漸進式罰分，只回報「超出量」供 fmincon 內部的
    % SQP 演算法拿去解限制式，不再用於引導最佳化方向的評分。
    ceq = [];
    Gx=x(1); Gy=x(2); rG=x(3); Bx=x(4); By=x(5); rd=x(6); rk=x(7);
    G = [Gx,Gy]; B = [Bx,By];

    BIG = 1e6;  % 幾何無解(死點/圓不相交)時，用大數表示「嚴重不可行」，
                % 純粹是為了讓 c(x) 有實數值可回傳給 fmincon，不是評分獎勵。

    if rd<=0.05 || rk<=0.05 || rG<=0.5
        c = BIG*ones(6,1);
        return;
    end

    m = minMarginOverRange(G, rG, B, rd, rk, a_min, a_max, b_min, b_max, na, nb);
    c1 = req_margin - m;   % 要求 <= 0，即 m >= req_margin

    avgs = nan(1, numel(b_samples));
    swings = nan(1, numel(b_samples));
    infeasible = false;
    for i = 1:numel(b_samples)
        info_i = swingInfo(G, rG, B, rd, rk, b_samples(i), a_min, a_max, nSwing);
        if isnan(info_i.s) || ~info_i.monotonic
            infeasible = true;
            break;
        end
        avgs(i)   = (info_i.theta_lo + info_i.theta_hi) / 2;
        swings(i) = info_i.s;
    end

    if infeasible
        c = [c1; BIG; BIG; BIG; BIG; BIG];
        return;
    end

    rangeAvg   = max(avgs) - min(avgs);
    swing_bmin = swings(1);
    swing_bmax = swings(end);

    c2 = rangeAvg - avgRange_max;                 % 要求 <= 0
    c3 = swingBmin_range(1) - swing_bmin;          % 要求 <= 0 (下限)
    c4 = swing_bmin - swingBmin_range(2);          % 要求 <= 0 (上限)
    c5 = swingBmax_range(1) - swing_bmax;          % 要求 <= 0 (下限)
    c6 = swing_bmax - swingBmax_range(2);          % 要求 <= 0 (上限)

    c = [c1; c2; c3; c4; c5; c6];
end