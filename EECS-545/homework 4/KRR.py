import numpy as np
import scipy.io as sio

# Load the data and preprocessed the data
bodyfat_data = sio.loadmat('bodyfat_data.mat')
x = bodyfat_data['X']
y = bodyfat_data['y']
n,d = x.shape
train_num = 150
x_train = np.mat(x[:train_num,:]); x_bar = np.mat(np.mean(x_train, axis=0))
x_train = x_train - x_bar; x_test = np.mat(x[train_num:,:])
y_train = np.mat(y[:train_num]); y_bar = np.mean(y_train)
y_train = y_train - y_bar; y_test = np.mat(y[train_num:])