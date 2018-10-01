N = 100; u = 1.1; d = 0.9;
k1 = 0.5; k2 = 2;
q_u = (1-d)/(u-d); q_d = 1-q_u;
P = zeros(N+1,N+1);
for i = 1:N+1
    P(N+1,i) = payoff(u^(i-1)*d^(N-i+1),k1,k2);
end
for j = N:-1:1
    for k = 1:j
        P(j,k) =max(q_u*P(j+1,k+1)+(1-q_u)*P(j+1,k), payoff(u^(k-1)*d^(j-k),k1,k2));
    end
end
P(1,1)