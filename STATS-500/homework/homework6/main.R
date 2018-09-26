library(faraway)
data(sat)
# ordinary least squares
yols = lm(total ~ takers + ratio + salary + expend, data = sat)
summary(yols)
# least absolute deviations
library(quantreg)
ylad = rq(total ~ takers + ratio + salary + expend, data = sat)
summary(ylad)
# Huber's method
library(MASS)
yhuber = rlm(total ~ takers + ratio + salary + expend, data = sat)
summary(yhuber)
# least trimmed squares
ylts = ltsreg(total ~ takers + ratio + salary + expend, data = sat, nsamp = "exact")
round(ylts$coef, 3)
# extract matrix of predictors for ltsreg
x = sat[,1:4]
## bootstrap 1000 times
bcoef = matrix(0, nrow = 1000, ncol = 5)
for(i in 1:1000){ 
newy <- ylts$fit + ylts$resid[sample(50, rep = T)] 
bcoef[i,] <- ltsreg(x, newy, nsamp = "best")$coef 
}
## 95% C.I. for parameters
colnames(bcoef) = c("(Intercept)","expend","ratio","salary","takers")
apply(bcoef, 2, function(x) quantile(x, c(0.025, 0.975)))

## compute p-value
ri = rstudent(yols)
2*(1 - pt(max(abs(ri)), df = 50-5-1))
## compare to alpha/n
0.05/50
#there is no outliers
## compute cook's distance
cook = cooks.distance(yols)
plot(dfbeta(yols)[,1], ylab = "Change in beta0 coef")
abline(h=0)
identify(dfbeta(yols)[,1])
halfnorm(cook, nlab = 2, ylab = "Cook's distance")
sat[c(44),]
plot(dfbeta(yols)[,2], ylab = "Change in beta1 coef")
abline(h=0)
identify(dfbeta(yols)[,2])
plot(dfbeta(yols)[,3], ylab = "Change in beta2 coef")
abline(h=0)
identify(dfbeta(yols)[,3])
plot(dfbeta(yols)[,4], ylab = "Change in beta3 coef")
abline(h=0)
identify(dfbeta(yols)[,4])
sat1 = sat[-c(44),]
## new least squares
yols1 = lm(total ~ takers + ratio + salary + expend, data = sat1)
coef(yols1)
