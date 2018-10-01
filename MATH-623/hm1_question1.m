r = 0.05; N = 100; u = 2;
sigma_d = 0.5; sigma_u = 0.8;
K1 = 0.2; K2 = 20;
dt = 1/N; d = 1/u;
q_d = []; q_u = []; E_Q_range = []; E_Q = [];
for i = 1:1000
    q_u = [q_u, 1/1000*i];
    q_d = [q_d, (q_u(i)-r*dt/(u-1))*u];
    E_Q_range = [E_Q_range, q_u(i)*(u-(1+r*dt))^2 + q_d(i)*(1/u-(1+r*dt))^2 + (1-q_u(i)-q_d(i))*(1-(1+r*dt))^2];
    if  (q_u(i) <= ((u-1+u*r*dt)/(u^2-1))) & (r*dt/(u-1))
        if (E_Q_range(i) <= (sigma_u^2)) & (E_Q_range(i) >= (sigma_d^2))
            total = 0; times = 0;
            for j = 0:N % times for up
                for k = 0:(N-j) % times for hold
                    times = factorial(N)/(factorial(j)*factorial(N-j-k)*factorial(k));
                    S_N = (u^j)*(d^(N-j-k));
                    f_S_N = maxfunc(S_N,K1,K2);
                    total = total + times*(q_u(i)^j)*((1-q_u(i)-q_d(i))^k)*(q_d(i)^(N-j-k))*f_S_N/((1+r*dt)^N);
                end
            end
            E_Q = [E_Q, total];
        end
    end
end
E_Q
max(E_Q)
min(E_Q)