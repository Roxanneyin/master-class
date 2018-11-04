r = 0.02; sigma = 0.2; K = 1; T = 1; L = 0.5; N = 100; M = 556;
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
x = a: dx : b; s = exp(x);
figure(1)
plot(s, u(M + 1, :))

[call_1,put_1] = blsprice(1, K, r, T, sigma);
[call_L2, put_L2] = blsprice(L^2, K, r, T, sigma);
real_p = call_1 - L^(2 * r / sigma^2 - 1) * call_L2;
for i = 1 : (N + 1)
    if ((a + dx * (i - 1) <= 0) & (a + dx * i > 0))
        p = i;
    end
end
est_p = (u(M + 1, p) + u(M + 1, p + 1)) / 2;
error = real_p - est_p

m = 1056 : -1 : 556;
delta_t = []; error = [];
for i = 1 : length(m)
    delta_t = [delta_t, T / m(i)];
    est_p = est_of_p(T / m(i));
    error = [error, real_p - est_p];
end
rate = [];
for i = 1 : length(error) - 1
    rate = [rate, abs((error(i + 1) - error(i)) / error(i))];
end
delta_t(1) = [];
figure(3)
plot(delta_t, rate)