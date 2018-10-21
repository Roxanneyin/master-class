import numpy as np
import scipy.io as sio

# Load the data and preprocessed the data
bodyfat_data = sio.loadmat('bodyfat_data.mat')
x = bodyfat_data['X']
y = bodyfat_data['y']
n,d = x.shape
train_num = 150; m = n - train_num
x_train = x[:train_num,:]; x_test = x[train_num:,:]
x_train_bar = np.mean(x_train, axis=0)
y_train = y[:train_num]; y_test = y[train_num:]
y_train_bar = np.mean(y_train)

# Helper function
def dist2(x,c):
    ndata,dimx = x.shape
    ncenters, dimc = c.shape

    xsum = np.sum(x**2,axis = 1)
    xsum = xsum[:,np.newaxis]
    csum = np.sum(c**2,axis = 1)
    csum = csum[:,np.newaxis]

    n2 =  xsum.dot(np.ones([1,ncenters]))+ np.ones([ndata,1]).dot(csum.T)- 2*x.dot(c.T)
    return n2

sigma = 15; lamda = 0.003
kernel = np.exp(-1/2/sigma**2 * dist2(x_train, x_train))
kernel_prime = np.exp(-1/2/sigma**2 * dist2(x_train, x_test))
On = 1/train_num * np.ones([train_num, train_num]); Om = 1/m * np.ones([m, m])
kernel_tilda = kernel - kernel.dot(On) - On.dot(kernel) + (On.dot(kernel)).dot(On)
kernel_prime_tilda = kernel_prime - kernel_prime.dot(Om) - On.dot(kernel_prime) + (On.dot(kernel_prime)).dot(Om)

# Kernel ridge regression with offset
y_pre_train = []
for i in range(train_num):
    y_pre_train.append(y_train_bar + (np.mat(y_train - y_train_bar).T
                                         * np.mat(kernel_tilda + train_num * lamda * np.eye(train_num)).I
                                         * np.mat(kernel_tilda[:,i]).T)[0,0])
y_pre_test = []
for i in range(m):
    y_pre_test.append(y_train_bar + (np.mat(y_train - y_train_bar).T
                                         * np.mat(kernel_tilda + train_num * lamda * np.eye(train_num)).I
                                         * np.mat(kernel_prime_tilda[:,i]).T)[0,0])

# Compute MSE
MSE_train = sum([(y_train[i] - y_pre_train[i])**2 for i in range(train_num)])/train_num
MSE_test = sum([(y_test[i] - y_pre_test[i])**2 for i in range(n-train_num)])/(n-train_num)
print("MSE for training data is: ", MSE_train[0])
print("MSE for test data is: ", MSE_test[0])

# Compute offset b
b = y_train_bar - (np.mat(y_train - y_train_bar).T
                   * np.mat(kernel_tilda + train_num * lamda * np.eye(train_num)).I
                   * np.mat(kernel.dot(On)[:,0] - ((On.dot(kernel)).dot(On))[0,0]).T)[0,0]
print("offset b is: ", b)