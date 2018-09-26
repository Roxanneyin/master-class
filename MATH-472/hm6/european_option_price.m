function E = european_option_price(g, S0, r, T, sigma, zmin, zmax, m)
h = (zmax - zmin)/m;
z = zmin : h : zmax; % m+1 points
f = @(z)exp(-r * T) * g(S0 * exp(sigma * sqrt(T) * z + (r - sigma ^ 2 / 2) * T)) * normpdf(z);
y0 = f(zmin); ym = f(zmax);
sumyi = 0;
for i = 2:m
    sumyi = sumyi + f(z(i));
end
E = h / 2 * (y0 + ym + 2 * sumyi);
end

