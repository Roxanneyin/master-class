function A = matrix_norm(A)
m = size(A,1);
n = size(A,2);
b = zeros(m,1);
for i = 1:m
    for j = 1:n
        b(i)=b(i)+abs(A(i,j));
    end
end
A = max(b);
end

