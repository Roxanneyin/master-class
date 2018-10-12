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

# Compute parameters
lamda = 10
A = 2 * (x_train.T * x_train + train_num * lamda * np.eye(d)) # d*d matrix
r = -2 * x_train.T * y_train; c = y_train.T * y_train
omega = -A.I * r # d*1 matrix
b = y_bar - omega.T * x_bar.T
print("Estimated omega is: ", omega[0,0], omega[1,0], "Estimated b is: ", b[0,0])

# Compute MSE
MSE = sum([(y_test[i,0] - (omega.T * x_test[i,:].T + b))**2 for i in range(n-train_num)])/(n-train_num)

print("Using remainder for estimating MSE is: ", MSE[0,0])

# Prediction
pred_x = np.mat([100,100])
pred_y = omega.T * pred_x.T + b
print("Predicted response at the input x=[100 100] is: ", pred_y[0,0])