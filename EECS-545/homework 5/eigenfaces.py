import numpy as np
import scipy.io as sio
import matplotlib.pyplot as plt

# Proceed with the data
yale = sio.loadmat('yalefaces.mat')
yalefaces = yale['yalefaces']
n = yalefaces.shape[2]
d = yalefaces.shape[0] * yalefaces.shape[1]
x = np.zeros([d, n])
for i in range(0, yalefaces.shape[2]):
    x[:, i] = np.reshape(yalefaces[:, :, i], d)

# Compute sample covariance matrix
mu = x.mean(axis=1)
x_bar = np.tile(mu, (n, 1)).T
s = (x - x_bar).dot((x - x_bar).T) / n

# Singular value decomposition
lamda, u = np.linalg.eig(s)
idx = lamda.argsort()[::-1]
lamda = lamda[idx]
u = u[:,idx]
plt.semilogy(lamda)
for i in range(d):
    percent = sum(lamda[:i]) / sum(lamda)
    if percent > 0.95:
        print('number of principal components needed to represent 95% of total variation is: ', i)
        print('percentage reduction in dimension is: ', '%.2f%%' % ((d - i) / d * 100))
        break
for i in range(d):
    percent = sum(lamda[:i]) / sum(lamda)
    if percent > 0.99:
        print("number of principal components needed to represent 99% of total variation is: ", i)
        print("percentage reduction in dimension is: ", '%.2f%%' % ((d - i) / d * 100))
        break

# Plot eigenvectors
fig =  plt.figure(num='eigenfaces',figsize=(8,8.5))
fig.suptitle('sample mean & 19 principal eigenvectors')
plt.subplot(4,5,1)
plt.title('sample mean')
plt.imshow(np.reshape(mu, (yalefaces.shape[0], yalefaces.shape[1])), cmap = plt.get_cmap('gray'))

for i in range(19):
    plt.subplot(4,5,2+i)
    plt.title('Num: %d' % (1 + i))
    plt.imshow(np.reshape(u[:,i], (yalefaces.shape[0], yalefaces.shape[1])), cmap = plt.get_cmap('gray'))
plt.show()
plt.close()