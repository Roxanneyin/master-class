% input n, k
format long
[a,b] = sparsesetup(n);
[x,i] = Jacobi_Method(a, b, k);
error = norm(a * x - b,'inf');