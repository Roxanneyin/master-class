function p = value(a,x,c)
s = c(1);
n = length(c);
for i = 2:n
    t = c(i);
    for j = 1:i-1
    t = t * (a - x(j));
    end
    s = s + t;
end
p = s;
end 