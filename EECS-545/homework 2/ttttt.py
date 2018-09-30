from numpy import *
import numpy as np

a = [[1.0,2.0,3.0],[-4,5,-6],[7,8,9]]
a = np.array(a)
# # a_train =a[0:3,:]
# # a_test = a[3:a.shape[0],:]
# # mid = np.median(a,axis=0)
# # row = a.shape[0]
# # col = a.shape[1]
# # print(a[0,1])
# # print(row)
# # print(col)
# # print(mid[0])
# # for i in range(row):
# #     for j in range(col):
# #         if a[i,j] >= mid[j]:
# #             a[i,j] = 2
# #         else:
# #             a[i,j] = 1
# #
# # list_a = [1,2,3,4,5,6]
# # list_b = [1,1,1,1,1,1]
# # list_c = [(1-i) for i in list_a]
# for i in range(a.shape[0]):
#     for j in range(a.shape[1]):
#         if a[i,j] == 2:
#             print (i,'+',j)

# # # Process the data
# z = np.genfromtxt('spambase.data', dtype = float, delimiter = ',')
# np.random.seed(0) # Seed the random number generator
# rp = np.random.permutation(z.shape[0]) # random permutation of indices
# z = z[rp,:] # shuffle the rows of z
# x = z[:,:-1]
# y = z[:,-1]
#
# # Quantize variables with option 2 where values equal to the median to 1
# mid = np.median(x,axis=0)
# row_num = x.shape[0]
# col_num = x.shape[1]
# for i in range(row_num):
#     for j in range(col_num):
#         if x[i,j] > mid[j]:
#             x[i,j] = 2
#         else:
#             x[i,j] = 1
#
# y = list(y)
# train_x, test_x = x[:2000,:], x[2000:,:]
# train_y, test_y = y[:2000], y[2000:]
# pi_1 = sum(train_y)/len(train_y)
# pi_hat = [(1-pi_1), pi_1]
# nk = [(1-pi_1)*2000, pi_1*2000]
# pk_hat_xis1_given_y = np.zeros((2,len(train_x[0])))
# for i in range(len(train_x)):
#     pk_hat_xis1_given_y[0] += (train_x[i] == 1) * (train_y[i] == 0) * 1/nk[0]
#     pk_hat_xis1_given_y[1] += (train_x[i] == 1) * (train_y[i] == 1) * 1/nk[1]
#
# print(pk_hat_xis1_given_y)

b = [1,2,3,4,2,2,4,1,6,7,3]

print(b.index(max(b)))