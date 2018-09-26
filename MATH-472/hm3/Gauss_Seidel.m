function [x,i] = Gauss_Seidel(a,b,k)
n = length(b);
d = diag(a);
l = tril(a) - diag(d);
u = triu(a) - diag(d);
x = zeros(n,1);
for i = 1:k
    B = b - u * x;
    for j = 1:n
        x(j) = (B(j) - l(j,:) * x)./d(j);
    end
    if norm(ones(n,1) - x, 'inf') < 10^(-6)
        break;
    end
end
end

