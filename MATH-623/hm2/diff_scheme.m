T = 1; K = 1; r = 0.02; delta = 0.3; N = 1000; M = 10^5;
s_bar = K * exp(3 * delta * T^(0.5) / K^(0.5) + abs(r - delta^2 * 0.5 / K) * T);
dt = T / M; ds = s_bar / N; p = zeros(N+1, M+1);
for i = 1 : (N + 1)
    p(i, M + 1) = max(ds * (i - 1) - K, 0);
end
for i = 1 : (M + 1)
    p(N + 1, i) = s_bar - exp(-r * (T - dt * (i - 1))) * K;
    p(1, i) = 0;
end
for i = (M + 1) : -1 : 2
    for j = 2 : N
        alpha1 = 1 - delta^2 * (j - 1) * dt / ds;
        alpha2 = delta^2 * (j - 1) * dt * 0.5 / ds + r * (j - 1) * dt * 0.5;
        alpha3 = delta^2 * (j - 1) * dt * 0.5 / ds - r * (j - 1) * dt * 0.5;
        p(j, i - 1) = alpha1 * p(j, i) + alpha2 * p(j + 1, i) + alpha3 * p(j - 1, i);
    end
end
s = 0 : ds : s_bar;
plot(s, p(:,1))