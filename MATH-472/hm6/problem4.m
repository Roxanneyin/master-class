S0 = 100; r = 0.01; sigma = 0.2;
K = 100; T = 1;
g = @(x)max(x - K, 0);
zmin = -10; zmax = 10; h = []; e = [];
for i = 1:15
    m = 2^i;
    E = european_option_price(g, S0, r, T, sigma, zmin, zmax, m);
    price = Cbs(T,S0,K,r,sigma);
    error = abs(E - price);
    e = [e, error];
    h = [h, (zmax - zmin)/m];
end
loglog(h, e)