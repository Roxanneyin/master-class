function [x,i] = Jacobi_Method(a,b,k)
n = length(b);
d = diag(a);
r = a - diag(d);
x = zeros(n,1);
for i = 1:k
    x = (b - r*x)./d;
    if norm(ones(n,1) - x, 'inf') < 10^(-6)
        break;
    end
end
end

