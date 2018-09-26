function [A,b] = gauss_em(A,b)
format rat
n = size(A,1);
for i = 1:n-1
    for k = i+1:n
        for j = i+1:n
            A(k,j) = A(k,j) - A(i,j)*A(k,i)/A(i,i);
        end
        b(k) = b(k) - A(k,i)/A(i,i)*b(i);
        A(k,i) = 0;
    end
end
end

