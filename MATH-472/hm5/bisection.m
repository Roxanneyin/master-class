function y = bisection(f,a,b,TOL)
if sign(f(a)) * sign(f(b)) >= 0
    error('f(a)f(b)<0 not satisfied');
end
while (b-a)/2 >TOL
    c = (a + b)/2;
    if f(c) == 0
        break
    end
    if sign(f(a)) * sign(f(c)) < 0
        b = c;
    else a = c;
    end
end
y = (a + b)/2;
end

