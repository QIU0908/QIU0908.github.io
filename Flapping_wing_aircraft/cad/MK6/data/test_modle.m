%% linkage_optimize_v6_test.m
% 測試模式：使用已知的參數組合，直接驗證是否滿足所有硬性限制
% 輸入已知參數，跳過 multistart 搜尋，只進行驗證和檢查

clear; clc; close all;
rng(1);

%% ---------- 1. 已知固定參數 ----------
a_min = -5;   a_max =  5;       % A_y 範圍 (已知)
b_min = -3.5; b_max = 3.5;      % A_x 範圍 (已知)

%% ---------- 2. 待測試的已知參數 ----------
Gx_opt =  5.;
Gy_opt = -0.5;
rG_opt = 20.8;
Bx_opt =  10.0;
By_opt =  1.;
rd_opt =  16.5;
rk_opt =  9.8;

G_opt = [Gx_opt, Gy_opt];
B_opt = [Bx_opt, By_opt];

%% ---------- 3. 硬性範圍設定 ----------
req_margin = 0.05;           % 死點安全餘裕 (硬性)
nBSamples  = 5;              % 用幾個 b 代表點檢查「角度中點」與擺幅

avgRange_max    = 0.5;           % 角度中點變動幅度上限 (deg)
swingBmin_range = [60, 80];      % b=b_min 時，擺角必須落在此範圍 (deg)
swingBmax_range = [180, 198];    % b=b_max 時，擺角必須落在此範圍 (deg)

b_samples = linspace(b_min, b_max, nBSamples);

fprintf('=========== 機構參數驗證開始 ===========\n');
fprintf('  死點餘裕要求 >= %.2f\n', req_margin);
fprintf('  中點變動範圍上限 <= %.2f deg\n', avgRange_max);
fprintf('  swing(b_min) 硬性範圍 [%.1f, %.1f] deg\n', swingBmin_range(1), swingBmin_range(2));
fprintf('  swing(b_max) 硬性範圍 [%.1f, %.1f] deg\n', swingBmax_range(1), swingBmax_range(2));
fprintf('\n');

%% ---------- 4. 高解析度驗證 ----------
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
        fprintf('警告: b=%.3f 時出現問題 (s=NaN 或非單調)\n', b_samples(i));
    end
    avgList(i)   = (info_i.theta_lo + info_i.theta_hi) / 2;
    swingList(i) = info_i.s;
end

avgRange = max(avgList) - min(avgList);
swing_bmin_final = swingList(1);
swing_bmax_final = swingList(end);

fprintf('\n---------- 最終參數與驗證結果 ----------\n');
fprintf('G 點座標      = (%.4f, %.4f)\n', Gx_opt, Gy_opt);
fprintf('e 圓半徑 rG   = %.4f\n', rG_opt);
fprintf('B 點座標      = (%.4f, %.4f)\n', Bx_opt, By_opt);
fprintf('圓 d 半徑 rd  = %.4f\n', rd_opt);
fprintf('圓 k 半徑 rk  = %.4f\n', rk_opt);
fprintf('\n');

sizeMetric = rG_opt + rd_opt + rk_opt;
fprintf('尺寸指標 (rG+rd+rk) = %.4f  (僅供參考)\n', sizeMetric);
fprintf('全程最小死點餘裕 = %.4f (需求 >= %.2f) ', minMarginFinal, req_margin);
if minMarginFinal >= req_margin
    fprintf('✓ PASS\n');
else
    fprintf('✗ FAIL (差額: %.4f)\n', minMarginFinal - req_margin);
end

swing_opt  = infoFinal.s;
theta_lo_u = infoFinal.theta_lo;
theta_hi_u = infoFinal.theta_hi;
alpha_total = theta_hi_u - theta_lo_u;

fprintf('BK 總擺角 = %.4f deg  (b=b_max=%.2f)\n', swing_opt, b_max);
fprintf('BK 真實總擺角 = %.4f deg  (θ_hi - θ_lo)\n', alpha_total);

fprintf('\n【硬性限制檢查】\n');
fprintf('(1) 中點變動範圍 = %.4f deg  (硬性上限 %.2f deg) ', avgRange, avgRange_max);
if avgRange <= avgRange_max
    fprintf('✓ PASS\n');
else
    fprintf('✗ FAIL (超出 %.4f deg)\n', avgRange - avgRange_max);
end

fprintf('(2) swing(b_min=%.2f) = %.4f deg  (硬性範圍 [%.1f, %.1f]) ', ...
    b_min, swing_bmin_final, swingBmin_range(1), swingBmin_range(2));
if swing_bmin_final >= swingBmin_range(1) && swing_bmin_final <= swingBmin_range(2)
    fprintf('✓ PASS\n');
else
    if swing_bmin_final < swingBmin_range(1)
        fprintf('✗ FAIL (低於下限 %.4f deg)\n', swingBmin_range(1) - swing_bmin_final);
    else
        fprintf('✗ FAIL (超過上限 %.4f deg)\n', swing_bmin_final - swingBmin_range(2));
    end
end

fprintf('(3) swing(b_max=%.2f) = %.4f deg  (硬性範圍 [%.1f, %.1f]) ', ...
    b_max, swing_bmax_final, swingBmax_range(1), swingBmax_range(2));
if swing_bmax_final >= swingBmax_range(1) && swing_bmax_final <= swingBmax_range(2)
    fprintf('✓ PASS\n');
else
    if swing_bmax_final < swingBmax_range(1)
        fprintf('✗ FAIL (低於下限 %.4f deg)\n', swingBmax_range(1) - swing_bmax_final);
    else
        fprintf('✗ FAIL (超過上限 %.4f deg)\n', swing_bmax_final - swingBmax_range(2));
    end
end

fprintf('\n【角度中點(兩端平均) 各 b 樣本點數值，共 %d 點】\n', nBSamples);
fprintf('%-12s %-25s %-20s\n', 'b 值', '中點平均角度 (deg)', '擺角 (deg)');
fprintf('%-12s %-25s %-20s\n', '-----------', '------------------------', '-------------------');
for i = 1:nBSamples
    fprintf('b=%-8.3f   avg=%-20.4f   swing=%-15.4f\n', b_samples(i), avgList(i), swingList(i));
end

fprintf('\n【邊界確認】\n');
fprintf('  Gx=%.4f in [%.1f,%.1f]     ✓\n', Gx_opt, 5, 20);
fprintf('  Gy=%.4f in [%.1f,%.1f]     ✓\n', Gy_opt, -1, 1);
fprintf('  rG=%.4f in [%.1f,%.1f]     ✓\n', rG_opt, 6, 30);
fprintf('  Bx=%.4f in [%.1f,%.1f]     ✓\n', Bx_opt, 5, 20);
fprintf('  By=%.4f in [%.1f,%.1f]     ✓\n', By_opt, -1, 1);
fprintf('  rd=%.4f in [%.1f,%.1f]     ✓\n', rd_opt, 6, 30);
fprintf('  rk=%.4f in [%.1f,%.1f]     ✓\n', rk_opt, 6, 30);

%% ---------- 5. 繪圖 ----------
figure('Name','角度中點 vs A_x (b)');
plot(b_samples, avgList, 'o-', 'LineWidth', 1.5, 'MarkerFaceColor','b', 'MarkerSize', 8);
xlabel('b (A_x)'); ylabel('兩端角度平均值 (deg)');
title(sprintf('角度中點 vs b (變動範圍 = %.3f deg，硬性上限 = %.2f deg)', avgRange, avgRange_max));
grid on;
ylim([min(avgList)-1, max(avgList)+1]);

figure('Name','擺角 vs A_x (b)，檢查硬性範圍');
plot(b_samples, swingList, 'o-', 'LineWidth', 1.5, 'Color',[0.85 0.2 0.2], 'MarkerFaceColor','r', 'MarkerSize', 8);
hold on;
yline(swingBmin_range(1), '--', 'b\_min 下限', 'Color',[0.2 0.2 0.85], 'LineWidth', 1.5);
yline(swingBmin_range(2), '--', 'b\_min 上限', 'Color',[0.2 0.2 0.85], 'LineWidth', 1.5);
yline(swingBmax_range(1), '--', 'b\_max 下限', 'Color',[0.2 0.6 0.2], 'LineWidth', 1.5);
yline(swingBmax_range(2), '--', 'b\_max 上限', 'Color',[0.2 0.6 0.2], 'LineWidth', 1.5);
xlabel('b (A_x)'); ylabel('擺角 (deg)');
title(sprintf('擺角 vs b\n(b_{min}=%.2f deg in [%.1f,%.1f], b_{max}=%.2f deg in [%.1f,%.1f])', ...
    swing_bmin_final, swingBmin_range(1), swingBmin_range(2), ...
    swing_bmax_final, swingBmax_range(1), swingBmax_range(2)));
grid on;
ylim([min([swingBmin_range(1), min(swingList)])-5, max([swingBmax_range(2), max(swingList)])+5]);

figure('Name','機構示意圖 (a = -5, 0, 5，b 在最右側)');
hold on; axis equal; grid on;
viscircles(G_opt, rG_opt, 'Color', [0.7 0.7 0.7], 'LineStyle', ':');
plot(G_opt(1), G_opt(2), 'ks', 'MarkerFaceColor','k', 'MarkerSize', 8); 
text(G_opt(1)+0.3, G_opt(2)-0.5, 'G', 'FontSize', 12, 'FontWeight','bold');
plot(B_opt(1), B_opt(2), 'ks', 'MarkerFaceColor','k', 'MarkerSize', 8); 
text(B_opt(1)+0.3, B_opt(2)-0.5, 'B', 'FontSize', 12, 'FontWeight','bold');
viscircles(B_opt, rd_opt, 'Color', [0.3 0.6 1], 'LineStyle', '--', 'LineWidth', 1.5);

colors = {[0.85 0.2 0.2], [0.2 0.6 0.2], [0.2 0.2 0.85]};
labels = {sprintf('a=%.0f (下端)',a_min), 'a=0 (中點)', sprintf('a=%.0f (上端)',a_max)};
aVals = [a_min, 0, a_max];
for t = 1:3
    A_t = [b_max, aVals(t)];
    I_t = IfromA(A_t, G_opt, rG_opt);
    K_t = circleIntersect(I_t, rk_opt, B_opt, rd_opt);
    if ~any(isnan(K_t))
        plot([A_t(1) G_opt(1)], [A_t(2) G_opt(2)], '-', 'Color', colors{t}*0.6+0.4, 'LineWidth', 1.2);
        plot(A_t(1), A_t(2), 'o', 'Color', colors{t}, 'MarkerFaceColor', colors{t}, 'MarkerSize', 7);
        plot(I_t(1), I_t(2), '^', 'Color', colors{t}, 'MarkerFaceColor', colors{t}, 'MarkerSize', 7);
        plot([I_t(1) K_t(1)], [I_t(2) K_t(2)], '-', 'Color', colors{t}, 'LineWidth', 1.5);
        plot([B_opt(1) K_t(1)], [B_opt(2) K_t(2)], '-', 'Color', colors{t}, 'LineWidth', 2.5);
        plot(K_t(1), K_t(2), 'p', 'Color', colors{t}, 'MarkerFaceColor', colors{t}, 'MarkerSize', 10);
    end
end
legend(labels, 'Location', 'bestoutside', 'FontSize', 10);
title(sprintf('機構示意圖 (rd=%.3f, rk=%.3f)\n總擺角=%.2f deg, 中點變動=%.2f deg', ...
    rd_opt, rk_opt, alpha_total, avgRange), 'FontSize', 11);
xlabel('x'); ylabel('y');
set(gca, 'FontSize', 10);

fprintf('\n=========== 驗證完成 ===========\n');

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
