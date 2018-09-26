function y = com_trap_rule(f,a,b,m)
h = (b - a)/m;
x = linspace(a, b, m+1);
sumy = 0;
for i = 2:m
    sumy = sumy +f(x(i));
end
y =h/2 * (f(a) + f(b) + 2 * sumy);
end

