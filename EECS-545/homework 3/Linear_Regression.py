import numpy as np
import scipy.io as sio

# # Load the data and preprocessed the data
# bodyfat_data = sio.loadmat('bodyfat_data.mat')
# x = bodyfat_data['X']
# y = bodyfat_data['y']
# n,d = x.shape
# x_train = x[:150,:]; x_test = x[150:,:]
# y_train = y[:150]; y_test = y[150:]
# added = np.ones(150)
# x_train = mat(np.vstack((added,x)))
# x_train = np.insert(x_train, 0, values=added, axis=0)
# x_train = np.mat(x_train); y_train = np.mat(y_train)
# theta = (x_train.T * x_train).I * x_train.T * y_train
# print(theta)

import numpy as np
a = np.array([[1,2,3],[4,5,6],[7,8,9]])
b = np.array([[0,0,0]])
d = np.insert(a, 0, values=b, axis=1)
print d 