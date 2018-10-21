import numpy as np

def dist2(x,c):
    ndata,dimx = x.shape
    ncenters, dimc = c.shape

    xsum = np.sum(x**2,axis = 1)
    xsum = xsum[:,np.newaxis]
    csum = np.sum(c**2,axis = 1)
    csum = csum[:,np.newaxis]

    n2 =  xsum.dot(np.ones([1,ncenters]))+ np.ones([ndata,1]).dot(csum.T)- 2*x.dot(c.T)
    return n2

a = np.array([[1,2,3], [4,5,6],[7,8,9]])
b = np.array([[2,3,4], [3,4,5]])
xx = np.sum(a**2, axis = 1)
yy = np.sum(b**2, axis = 1)
xx = xx[:,np.newaxis]
yy = yy[:,np.newaxis]

print(np.ones([2,1]).dot(yy.T))
print(dist2(a,b))