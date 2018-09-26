# question 1
q1 = qnorm(0.9, mean = 1, sd = 2)
q1^3 + 2
q2 = qnorm(0.1, mean = 1, sd = 2)
exp(-q2)

#question 2
qa = qnorm(0.003, mean = 0, sd = 0.025)
exp(qa)-1
VaR_tilde = -(exp(qa)-1)
VaR_tilde
VaR = 100 * 10^6 * VaR_tilde
VaR
## v = 12
dt(0.003, 12)
## v = 6
dt(0.003, 6)
## v = 3
dt(0.003, 3)

#question 3
dat = read.csv("Nasdaq_daily_Jan1_2012_Dec31_2017.csv", header = T)
t = as.Date(dat$Date, format = "%m/%d/%Y")
idx1 = which(is.na(dat$Adj.Close) == FALSE)
times = t[idx1]
acp = dat$Adj.Close[idx1]
acp_lreturn = diff(log(acp))
plot(times, acp, xlab = 'day', ylab = 'adjusted closing price', type = 'l')
plot(acp_lreturn, xlab = 'day', ylab = 'daliy log return', type = 'l')
summary(acp_lreturn)
sd(acp_lreturn)
library(fBasics)
skewness(acp_lreturn)
kurtosis(acp_lreturn)
par(mfrow = c(1,2))
hist(acp_lreturn, xlab = 'daily log returns', breaks = 25, main = 'daily log returns')
boxplot(acp_lreturn)
title('daily log returns')

# question 4
## problem 12 13
data = read.csv("MCD_PriceDaily.csv", head = T)
head(data)
adjPrice = data[, 7]
par(mfrow = c(1,1))
adjp_return = adjPrice[-1]/adjPrice[-1177] - 1
adjp_lreturn = diff(log(adjPrice))
plot(adjp_return, adjp_lreturn, xlab = "Return", ylab = "Log Return")
abline(a = 0,b = 1,col = "red",lwd = 2)
mean(adjp_return)
miu = mean(adjp_lreturn)
sd(adjp_return)
sigma = sd(adjp_lreturn)
adjp_return[1:3]
adjp_lreturn[1:3]

## problem 16 17
niter = 10000 # number of iterations
below = rep(0, niter) # set up storage
set.seed(2015)
for (i in 1:niter)
  {
  r = rnorm(20, mean = miu, 
            sd = sigma) # generate random numbers for 20 times
  prices = 93.07 * exp(cumsum(r)) # cumsum means to get the sum of all r for every time point
  indx = (min(prices) < 85) # if minimum price is less than 85 over next 20 days
  below[i] = 100 * indx - (1 - indx)
}
mu = mean(below)
mu + c(-1,1)* sqrt(mu*(1-mu)/niter)*qnorm(0.975)
## 95% CI is larger than 0, we should bet

niter = 10000 # number of iterations
below = rep(0, niter) # set up storage
set.seed(2016)
for (i in 1:niter)
{
  r = rnorm(20, mean = miu, 
            sd = sigma) # generate random numbers for 20 times
  prices = 93.07 * exp(cumsum(r)) # cumsum means to get the sum of all r for every time point
  indx1 = (min(prices) < 85) # if minimum price is less than 85 over next 20 days
  indx2 = (min(prices) < 84.5)
  below[i] = 100 * indx1 + 25 * indx2 - (1 - indx1)
}
mu = mean(below)
mu + c(-1,1)* sqrt(mu*(1-mu)/niter)*qnorm(0.975)

