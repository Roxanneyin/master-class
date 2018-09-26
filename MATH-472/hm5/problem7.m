f1 = @(x)x/sqrt(x^2 + 9);
ya = romberg(f1,0,4,5);
ya(5,5)
syms x
vpa(abs(int(x/sqrt(x^2 + 9),0,4) - ya(5,5)),4)
int(x/sqrt(x^2 + 9),0,4)
f2 = @(x)x * exp(x)
yc = romberg(f2,0,1,5);
yc(5,5)
syms x
vpa(abs(int(x * exp(x),0,1) - yc(5,5)),4)
int(x * exp(x),0,1)