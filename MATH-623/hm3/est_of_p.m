function y = est_of_p(x)
r = 0.02; sigma = 0.2; K = 1; T = 1; L = 0.5; N = 100; M = fix(T / x);
a = log(L); b = log(K) + 3 * sigma * T^0.5 + abs(r - sigma^2 / 2) * T;
dt = T / M; dx = (b - a) / N;
alpha0 = 1 - sigma^2 * dt / dx^2;
alpha1 = sigma^2 * dt / (2 * dx^2) + (r - sigma^2 / 2) * dt / dx;
alpha2 = sigma^2 * dt / (2 * dx^2) - (r - sigma^2 / 2) * dt / dx;
for i = 1 : (N + 1)
    u(1, i) = max(0, exp(a + (i - 1) * dx) - K);
end
for i = 1 : (M + 1)
    u(i, N + 1) = exp(b) - K * exp(- r * (T - dt * (i - 1)));
    u(i, 1) = 0;
end
for i = 2 : (M + 1)
    for j = 2 : N
        u(i, j) = (alpha0 - r * dt) * u(i - 1, j) + alpha1 * u(i - 1, j + 1) + alpha2 * u(i - 1, j - 1);
    end
end
for i = 1 : (N + 1)
    if ((a + dx * (i - 1) <= 0) & (a + dx * i > 0))
        q = i;
    end
end
y = (u(M + 1, q) + u(M + 1, q + 1)) / 2;
end

