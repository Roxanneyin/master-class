import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import pylab as pl

# Generating data
np.random.seed(0)
n = 200 # sample size
K = 2 # number of lines
e = np.array([0.7, 0.3]) # mixing weights
w = np.array([-2, 1]) # slopes of lines
b = np.array([0.5, -0.5]) # offsets of lines
v = np.array([0.2, 0.1]) # variances
x = np.zeros([n])
y = np.zeros([n])
for i in range(0,n):
    x[i] = np.random.rand(1)
    if np.random.rand(1) < e[0]:
        y[i] =w[0] * x[i] + b[0] + np.random.randn(1) * np.sqrt(v[0])
    else:
        y[i] = w[1] * x[i] + b[1] + np.random.randn(1) * np.sqrt(v[1])

X = np.c_[np.ones(n).T, x]
plt.plot(x, y, 'bo')
t = np.linspace(0, 1, num = 100)
plt.plot(t, w[0] * t + b[0], 'k')
plt.plot(t, w[1] * t + b[1], 'k')

# Implement EM algorithm
## Initialization
e_weight = np.array([.5, .5])
w_slope = np.array([1., -1.])
b_offset = np.array([0., 0.])
sig_var = np.array([np.var(y), np.var(y)])
iteration = 500
gamma = np.zeros([n, K])
Loglike = np.zeros(iteration)
loglike = 0
for j in range(iteration):
    new_loglike = 0
    for i in range(n):
        s = 0
        for k in range(K):
            s += e_weight[k] * norm.pdf(y[i], loc=w_slope[k] * x[i] + b_offset[k], scale=np.sqrt(sig_var[k]))
        new_loglike += np.log(s)
    ## E step
    sum = np.zeros(n)
    for i in range(n):
        sum[i] = e_weight[0] * norm.pdf(y[i], loc=w_slope[0] * x[i] + b_offset[0], scale=np.sqrt(sig_var[0])) \
                 + e_weight[1] * norm.pdf(y[i], loc=w_slope[1] * x[i] + b_offset[1], scale=np.sqrt(sig_var[1]))
        for k in range(K):
            gamma[i, k] = e_weight[k] * norm.pdf(y[i], loc=w_slope[k] * x[i] + b_offset[k], scale=np.sqrt(sig_var[k])) / sum[i]

    ## M step
    e_weight = np.sum(gamma, axis=0) / n
    for k in range(K):
        [b_offset[k], w_slope[k]] = np.asarray((np.asmatrix(X).T * np.asmatrix(np.diag(gamma[:, k])) * np.asmatrix(X)).I
                                               * np.asmatrix(X).T * np.asmatrix(np.diag(gamma[:, k])) * np.asmatrix(y).T)
        numerator = 0; denominator = 0
        for i in range(n):
            numerator += (y[i] - w_slope[k] * x[i] - b_offset[k])**2 * gamma[i, k]
            denominator += gamma[i, k]
        sig_var[k] = numerator / denominator
    if abs(new_loglike - loglike) < 10**-4:
        times = j
        break
    else:
        loglike = new_loglike
        Loglike[j] = loglike
print("The number of iterations to reach convergence is: ", times + 1)
print("The estimated model parameters are as follows: ")
print("mixing weights: ", e_weight)
print("slopes of lines: ", w_slope)
print("offsets of lines: ", b_offset)
print("variances: ", sig_var)
plt.plot(t, w_slope[0] * t + b_offset[0], ':')
plt.plot(t, w_slope[1] * t + b_offset[1], ':')

plt.figure()
iter = pl.frange(1,times)
plt.plot(iter, Loglike[:times], label = 'log-likelihood')
plt.show()