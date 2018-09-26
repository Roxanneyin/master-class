function x = Newtons_meth(k)
syms u v
f1 = u^3 - v^3 + u;
f2 = u^2 + v^2 - 1;
df =jacobian([f1,f2],[u,v]);
n = 2; u = 1; v = - 1;
x = [u;v];
for i = 1:k
    f = [eval(f1); eval(f2)];
    df1 = eval(df);
    [A,B] = gauss_em(df1,-f);
    s = back_sub(A,B);
    x = x + s';
    u = x(1); v = x(2);
end
end
