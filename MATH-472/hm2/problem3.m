n = 5; % input n
H=hilbert_matrix(n);
b = ones(n,1);
b = b';
[A,b] = gauss_em(H,b);
x = back_sub(A,b)