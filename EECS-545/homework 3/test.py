import numpy as np

a = np.mat([[1,2,3],[4,8,6]])
b = 1
c = np.insert(a, 0, values=b, axis=0)
print(b,c)
x = np.random.rand()
print(x)