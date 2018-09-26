library(faraway)
data(trees)
library(MASS)
# Box-Cox method for trees data
y = lm(Volume ~ Girth + Height, data = trees)
summary(y)
boxcox(y, plotit = T)
boxcox(y, plotit = T, lambda = seq(0, 1, by = 0.1))
ybc = lm(Volume^(.33) ~ Girth + Height, data = trees)
summary(ybc)
# polynomials backward elimination
## 2nd degree
summary(lm(Volume ~ Girth + Height + I(Girth^2) + I(Height^2) + I(Girth * Height), data = trees))
summary(lm(Volume ~ Girth + Height + I(Girth^2) + I(Girth * Height), data = trees))
summary(lm(Volume ~ Girth + Height + I(Girth^2), data = trees))
ypol = lm(Volume ~ Girth + Height + I(Girth^2), data = trees)
# box-cox & polynomials backward elimination
summary(lm(Volume^(.33) ~ Girth + Height + I(Girth^2) + I(Height^2) + I(Girth * Height), data = trees))
summary(lm(Volume^(.33) ~ Girth + Height + I(Height^2) + I(Girth * Height), data = trees))
summary(lm(Volume^(.33) ~ Girth + Height + I(Height^2), data = trees))
summary(lm(Volume^(.33) ~ Girth + Height, data = trees))
# for (a) and (c) model
## nonlinearlity
ri = rstudent(ybc)
plot(ybc$fitted, ri, xlab = "Fitted", ylab = "STResiduals")
abline(h = 0)
## QQ plot
par(mfrow = c(1,2))
qqnorm(ri, ylab = "Residuals")
qqline(ri)
## Histogram
hist(ri, xlab = "Residuals")
max(abs(ri))
which(ri == max(-abs(ri)))
## compute p-value
2*(1 - pt(max(abs(ri)), df = 31-3-1))
## compare to alpha/n
0.05/31
##[1] 0.03503326
##[1] 0.001612903 不能拒绝原假设，没有outlier
par(mfrow = c(1,1))
## compute cook's distance
cook = cooks.distance(ybc)
halfnorm(cook, nlab = 3, ylab = "Cook's distance")
plot(dfbeta(ybc)[,1], ylab = "Change in beta0 coef")
abline(h=0)
identify(dfbeta(ybc)[,1])
plot(dfbeta(ybc)[,2], ylab = "Change in beta1 coef")
abline(h=0)
identify(dfbeta(ybc)[,2])
plot(dfbeta(ybc)[,3], ylab = "Change in beta2 coef")
abline(h=0)
identify(dfbeta(ybc)[,3])
## 17 18是influential points
# for (b) model
## nonlinearlity
ri = rstudent(ypol)
plot(ypol$fitted, ri, xlab = "Fitted", ylab = "STResiduals")
abline(h = 0)
## QQ plot
par(mfrow = c(1,2))
qqnorm(ri, ylab = "Residuals")
qqline(ri)
## Histogram
hist(ri, xlab = "Residuals")
max(abs(ri))
which(ri == max(-abs(ri)))
## compute p-value
2*(1 - pt(max(abs(ri)), df = 31-4-1))
## compare to alpha/n
0.05/31
##[1] 0.07927363
##[1] 0.001612903不能拒绝原假设，没有outlier
par(mfrow = c(1,1))
## compute cook's distance
cook = cooks.distance(ypol)
halfnorm(cook, nlab = 3, ylab = "Cook's distance")
plot(dfbeta(ypol)[,1], ylab = "Change in beta0 coef")
abline(h=0)
identify(dfbeta(ypol)[,1])
plot(dfbeta(ypol)[,2], ylab = "Change in beta1 coef")
abline(h=0)
identify(dfbeta(ypol)[,2])
plot(dfbeta(ypol)[,3], ylab = "Change in beta2 coef")
abline(h=0)
identify(dfbeta(ypol)[,3])
plot(dfbeta(ypol)[,4], ylab = "Change in beta3 coef")
abline(h=0)
identify(dfbeta(ypol)[,4])
