function xc = secant(f,x0,x1,TOL)
x = [x0, x1];
while abs(x(2) - x(1))>TOL
xc = x(2) - (f(x(2)) * (x(2) - x(1)))/(f(x(2)) - f(x(1)));
x(1) = x(2);
x(2) = xc;
end
end

