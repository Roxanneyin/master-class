p1 = 2; p2 = 3; p3 = 5; p4 = 7; n = 10 ^ 5;
w = halton(p1,n);
x = halton(p2,n);
y = halton(p3,n);
z = halton(p4,n);
s = 0;
for i = 1:10 ^5
    if (2 * w(i) - 1)^2 + (2 * x(i) - 1)^2 + (2 * y(i) - 1)^2 + (2 * z(i) - 1)^2 < 1
        s = s + 1;
    end
end
s / 10^5 * 16
pi ^ 2 / 2