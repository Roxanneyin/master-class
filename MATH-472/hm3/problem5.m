% input n,k
format long
[a,b] = sparsesetup2(n);
[x,i] = conj_grad(a, b, k);
err = norm((b - a * x),'inf');