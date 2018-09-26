% input n, k
format long
[a,b] = sparsesetup(n);
[x,i] = Gauss_Seidel(a, b, k);
error = norm(a * x - b,'inf');