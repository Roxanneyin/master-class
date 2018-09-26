% syms x
% fx = exp(abs(x));
% x = -1:0.01:1;
% plot(x,eval(fx))
%n = 10;
n = 20;
leng = 2/n;
x1 = -1:leng:1;
y1 = exp(abs(x1));
c1 = newtdd(x1,y1,n+1);
a = -1:0.01:1;
p1 = nest(n,c1,a,x1);
plot(a,p1,'r')
hold on
x2 = cos((1:2:2*(n+1)-1)*pi/(2*(n+1)));
y2 = exp(abs(x2));
c2 = newtdd(x2,y2,n+1);
p2 = nest(n,c2,a,x2);
p_true = exp(abs(a));
error1 = norm(p1 - p_true,'inf')
error2 = norm(p2 - p_true, 'inf')
plot(a,p2,'b')
plot(a,p1 - p_true,'r')
hold on
plot(a,p2 - p_true,'b')