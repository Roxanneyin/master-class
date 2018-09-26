## read in the data
library(faraway)
data(uswages)
## get the X matrix
dim(uswages)
uswages$exper[uswages$exper < 0] = NA
uswages = na.omit(uswages)
n = dim(uswages)[1]
p = 2
## use the lm() function
temp = lm(wage ~ educ + exper, data = uswages)
summary(temp)
##residual sum of squares
sigma = residuals(temp)
summary(sigma)
which.max(sigma)
## compute mean and median
mean(sigma)
median(sigma)
## fit the model
yhead = fitted(temp)
cor(sigma,y)
plot(y,sigma)
## log wage as response
ystar = log(uswages$wage)
tempstar = lm(ystar ~ educ + exper, data = uswages)
