function x = back_sub(A,b)
n=size(A,1);
for i = n:-1:1
    for j = i+1:n
        b(i) = b(i) - A(i,j)*x(j);
    end
    x(i) = b(i)/A(i,i);
end
end

