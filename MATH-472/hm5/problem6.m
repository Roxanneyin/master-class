f1 = @(x)x^3/(x^2 + 1);
yb16 = com_trap_rule(f1,0,1,16)
yb32 = com_trap_rule(f1,0,1,32)
syms x
vpa(abs(int(x^3/(x^2 + 1),0,1) - yb16),4)
vpa(abs(int(x^3/(x^2 + 1),0,1) - yb32),4)
f2 = @(x)x/sqrt(x^4 + 1);
yh16 = com_trap_rule(f2,0,1,16)
yh32 = com_trap_rule(f2,0,1,32)
syms x
vpa(abs(int(x/sqrt(x^4 + 1),0,1) - yh16),4)
vpa(abs(int(x/sqrt(x^4 + 1),0,1) - yh32),4)