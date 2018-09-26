function num = cond_num(A)
num = matrix_norm(A)*matrix_norm(inv(A));
end