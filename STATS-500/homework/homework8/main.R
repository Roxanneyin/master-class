library(faraway)
data(seatpos)
dim(seatpos)

## training and test data
trainseat = seatpos[1:30,]
testseat = seatpos[31:38,]

## linear regression with all predictors
y0 = lm(hipcenter ~ . , data = trainseat)
summary(y0)$r.squared
# mean squared error
mse = function(x, y){mean((x - y)^2)}
mse(y0$fit, trainseat$hipcenter)
# prediction
mse(predict(y0, newdata = testseat), testseat$hipcenter)

## AIC
yaic = lm(hipcenter ~ . , data = trainseat)
yaic2 = step(yaic)
summary(lm(hipcenter ~ Seated + Arm + Leg, data = trainseat))
mse(yaic2$fit, trainseat$hipcenter)
mse(predict(yaic2, newdata = testseat), testseat$hipcenter)

## PCR wich CV
library(stats)
seatpca = prcomp(trainseat[,-9])
matplot(1:8, seatpca$rot[,1:4], type = "l", xlab = "Frequency", ylab = "", lwd = 3)
library(pls)
ypcr = pcr(hipcenter ~ . , data = trainseat, ncomp = 8, validation = "CV", segments = 3)
rmsCV = RMSEP(ypcr, estimate = 'CV')
which.min(rmsCV$val)
# plot the RMSE
plot(rmsCV$val, xlab = "PC number", ylab = "CV RMS")
mse(ypcr$fitted.values[,,4], trainseat$hipcenter)
# get test error
yfit = predict(ypcr, newdata = testseat, ncomp = 4)
mse(testseat$hipcenter, yfit)

## PLS with CV
ypls = plsr(hipcenter ~ . , data = trainseat, ncomp = 8, validation = "CV")
pls_rmsCV = RMSEP(ypls, estimate = 'CV')
plot(pls_rmsCV$val, xlab = "PC number", ylab = "CV RMS")
which.min(pls_rmsCV$val)
dim(ypls$fitted.values)
# 30  1  8
mse(ypls$fitted.values[,,4], trainseat$hipcenter)
ypred.test = predict(ypls, newdata = testseat)
dim(ypred.test)
# 8 1 8
mse(ypred.test[,,4], testseat$hipcenter)

## ridge regression with GCV
library(MASS)
yridge = lm.ridge(hipcenter ~ . , lambda = seq(0, 50, 0.01), data = trainseat)
matplot(yridge$lambda, t(yridge$coef), type = "l", lty = 1, xlab = expression(lambda), ylab = expression(hat(beta)))
# select lambda
select(yridge)
abline(v = 21.52)
which.min(yridge$GCV)
# fitted values
yfit = yridge$ym + scale(trainseat[,-9], center = yridge$xm, scale = yridge$scales) %*% yridge$coef[,2153]
yridge$coef[,2153]
mse(yfit, trainseat$hipcenter)
# prediction
ypred = yridge$ym + scale(testseat[,-9], center = yridge$xm, scale = yridge$scales) %*% yridge$coef[,2153]
mse(ypred, testseat$hipcenter)

## Lasso
require(lars)
set.seed(123)
lmod = lars(as.matrix(trainseat[,-9]), trainseat$hipcenter)
plot(lmod)
cvlmod = cv.lars(as.matrix(trainseat[,-9]), trainseat$hipcenter)
cvlmod$index[which.min(cvlmod$cv)]
testx = as.matrix(testseat[,-9])
predlars = predict(lmod,testx, s = 0.2727273, mode = "fraction")
mse(testseat$hipcenter, predlars$fit)
predlars = predict(lmod, s = 0.2727273, type = "coef", mode = "fraction")
plot(predlars$coef, type = "h", ylab = "Coefficient")
predict(lmod, s = 0.2727273, type = "coef", mode = "fraction")$coef
coef(lm(hipcenter ~ Ht + Arm + Leg, data = seatpos))