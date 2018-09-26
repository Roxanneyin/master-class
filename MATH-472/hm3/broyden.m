function [x,temp1,i] = broyden(k)
syms u v
f1 = u^2 + v^2 - 1;
f2 = (u - 1)^2 + v^2 - 1;
% f1 = u^2 + 4 * v^2 - 4;
% f2 = 4 * u^2 + v^2 - 4;
% f1 = u^2 - 4 * v^2 - 4;
% f2 = (u - 1)^2 + v^2 - 4;
n = 2; u = 1; v = 1;
x = [u;v];
a = eye(n);
for i = 1:k
    f = [eval(f1); eval(f2)];
    temp1 = x;
    x = x - inv(a) * f;
    u = x(1); v = x(2);
    temp2 = f;
    f = [eval(f1); eval(f2)];
    a = a +((f - temp2 - a * (x - temp1)) * (x - temp1)') / ((x - temp1)' * (x - temp1));
    if x - temp1 == 0
        break;
    end
end
end

