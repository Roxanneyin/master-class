n = 6; % input n(n = 6, 10)
A = matrix(n);
b = A * ones(n,1);  
xc = A\b;
fe = max(abs(ones(n,1)-xc))
emf = fe * matrix_norm(b)/matrix_norm(b - A*xc)
cond_num(A)