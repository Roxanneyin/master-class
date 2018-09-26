n = 10^5;
x = rand(4,n);
b = sum(x.*x);
s = 0;
for i = 1:n
    if b(i) <= 1
        s = s+1;
    end
end
s/n * 16