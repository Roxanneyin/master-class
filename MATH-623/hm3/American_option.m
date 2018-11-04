r = 0.02; sigma = 0.2; K = 1; T = 1; N = 100;
a = log(K) - 3 * sigma * T^0.5 - (r - sigma^2 / 2) * T;
b = log(K) + 3 * sigma * T^0.5 + abs(r - sigma^2 / 2) * T;
M = 556; dt = T / M; dx = (b - a) / N; u = zeros(M + 1, N + 1);
alpha0 = 1 - sigma^2 * dt / dx^2;
alpha1 = sigma^2 * dt / (2 * dx^2) + (r - sigma^2 / 2) * dt / dx;
alpha2 = sigma^2 * dt / (2 * dx^2) - (r - sigma^2 / 2) * dt / dx;
for i = 1 : (N + 1)
    u(1, i) = max(0, K - exp(a + (i - 1) * dx));
end
for i = 1 : (M + 1)
    u(i, 1) = K * exp(- r * (T - dt * (i - 1))) - exp(a);
    u(i, N + 1) = 0;
end
for i = 2 : (M + 1)
    for j = 2 : N
        u(i, j) = max(K - exp(a + dx * (j - 1)), (alpha0 - r * dt) * u(i - 1, j) + alpha1 * u(i - 1, j + 1) + alpha2 * u(i - 1, j - 1));
    end
end
x = a: dx : b; s = exp(x);
figure(1)
plot(s, u(M + 1, :))
Ex = [];
for i = (M + 1) : -1 : 1
    p = [];
    for j = 1 : (N + 1)
        if (u(i, j) > (K - exp(a + dx * (j - 1))))
            p = [p, exp(a + dx * (j - 1))];
        end
    end
    Ex = [Ex, min(p)];
end
t = 0 : dt : T;
figure(2)
plot(t, Ex)
