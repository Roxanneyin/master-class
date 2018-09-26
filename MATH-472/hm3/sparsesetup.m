function [a,b] = sparsesetup(n)
e = ones(n,1);
a = spdiags([-e 3*e -e], -1:1,n,n);
b = ones(n,1);
b(1) = 2; b(n) = 2;
end

