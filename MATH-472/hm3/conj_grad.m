function [x,i] = conj_grad(a,b,k)
n = length(b);
x = zeros(n,1);
d = b - a * x;
r = d;
er = 1;
for i = 1:k
    if er == 0
        break;
    end
    alpha = r' * r ./ (d' * a * d);
    t = x;
    x = x + alpha * d;
    er = x - t;
    temp = r' * r;
    r = r - alpha * a * d;
    beta = r'* r ./ temp;
    d = r + beta * d;
end
end

