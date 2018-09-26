x = [0.6 0.7 0.8 0.9 1.0];
y = [1.433329 1.632316 1.896481 2.247908 2.718282];
n = 5;
c = newtdd(x,y,n);
a = 0.98;
p = value(a,x,c);
syms v
pv = c(1);
fv = exp(v^2);
for i = 2:n
    t = c(i);
    for j = 1:i-1
    t = t * (v - x(j));
    end
    pv = pv + t;
end 
pv = vpa(expand(pv),5)
syms u
f = exp(u^2);
for i = 1:n
    f = diff(f,u);
end
% u = linspace(0.6,1);
% plot(u,eval(f))
u = 1;
multi = 1;
for i = 1:n
    multi = multi * (a - x(i));
end
up_bounds = abs(multi) * abs(eval(f)) / factorial(n);
act_error = abs(exp(a^2)-p);
v = linspace(0.5,1);
plot(v,eval(pv - fv))
v = linspace(1,2);
plot(v,eval(pv - fv))