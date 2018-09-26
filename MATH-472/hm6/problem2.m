m = 0; n = 10000;
for j = 1:n
     s = 0; b = 0; k = 1000; sqdelt = sqrt(0.01);
    for i = 1:k
        a = b;
        b = b + sqdelt * randn;
        if i >= 800 & i <= 1000
            if a * b <= 0
                s = 1;
            end
        end
    end
    if s == 0;
        m = m + 1;
    end
end
(2 / pi) * asin(sqrt(8/10))
m/10000