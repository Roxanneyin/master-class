T =1; K = 100; B = 120; r = 0.1; sigma = 0.25; S0 = 100;
M = 1000; delt = T/M;
t = 0:delt:T; % M + 1 points
N = 1000;
k = M;
S = [];
for i = 1:N
    b = 0; sqdelt = sqrt(delt); St = [];
    for j = 1:k+1
        tk = t(j);
        b = b + sqdelt * randn;
        Stk = S0 * exp((r - 1/2 * sigma^2) * tk + sigma * b);
        St = [St, Stk];
    end
    S = [S; St];
end