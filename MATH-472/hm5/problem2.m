K = [500 550 600 650 700 750 800 850 900 950];
C = [210.3400  166.3140  126.5249  89.0857  59.5878  43.5040  31.3392  25.2330  20.1734  15.7494];
S = 700;
T = 1/4;
r = 0.03;
sigmac1 = [];
for i = 1:10
    fi = @(sigma)Cbs(T,S,K(i),r,sigma) - C(i);
    a = 0.0001; b = 1; TOL = 10^(-6);
    sigmac1(i) = bisection(fi,a,b,TOL);
end
vpa(sigmac1, 6)

sigmac2 = [];
for i = 1:10
    fi = @(sigma)Cbs(T,S,K(i),r,sigma) - C(i);
    x0 = 0.3; x1 = 0.35; TOL = 10^(-6);
    sigmac2(i) = secant(fi,x0,x1,TOL);
end
vpa(sigmac2, 6)
plot (K, sigmac1)
hold on
plot (K, sigmac2)