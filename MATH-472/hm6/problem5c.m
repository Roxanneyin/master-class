T =1; K = 100; B = 120; r = 0.1; sigma = 0.25; S0 = 100;
M = 1000; delt = T/M;
t = 0:delt:T; % M + 1 points
N = 100000;
k = M; VT = 0;
for i = 1:N
    b = 0; sqdelt = sqrt(delt); l = 0;
    for j = 1:k+1
        tk = t(j);
        b = b + sqdelt * randn;
        Stk = S0 * exp((r - 1/2 * sigma^2) * tk + sigma * b);
        if Stk >= B
            l = 1;
        end
    end
    if l == 0;
        VT = VT + max(Stk - K, 0);
    end
end
E = VT/N * exp(-r * T)