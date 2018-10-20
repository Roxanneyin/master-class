T = 1; K = 1; r = 0.02; delta = 0.3; N = 1000; M = 10^5;
s_bar = K * exp(3 * delta * T^(0.5) / K^(0.5) + abs(r - delta^2 * 0.5 / K) * T);
dt = T / M; ds = s_bar / N; p = zeros(N+1, M+1);
ds^2 / (delta^2 * s_bar + r * ds^2)