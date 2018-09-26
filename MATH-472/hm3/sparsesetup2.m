function [a,b] = sparsesetup2(n)
e = ones(n,1); n2 = n/2;
a = spdiags([-e 3*e -e],-1:1,n,n);
c = spdiags([e/2],0,n,n); c = fliplr(c); a = a + c;
a(n2+1,n2) = -1; a(n2, n2+1) = -1;
b = zeros(n,1);
b(1) = 2.5; b(n) = 2.5; b(2:n-1) = 1.5; b(n2:n2+1) = 1;
end