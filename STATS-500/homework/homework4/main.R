library(faraway)
data(sat)
temp = lm(total ~ expend + salary + ratio + takers, data = sat)
summary(temp)
## plot residuals vs fitted values
plot(temp$fitted, temp$residual, xlab = "Fitted", ylab = "Residuals")
abline(h = 0)
par(mfrow = c(1,2))
plot(sat$expend, temp$residual, xlab = "Expend", ylab = "Residuals")
plot(sat$salary, temp$residual, xlab = "Salary", ylab = "Residuals")
par(mfrow = c(1,2))
plot(sat$ratio, temp$residual, xlab = "Ratio", ylab = "Residuals")
plot(sat$takers, temp$residual, xlab = "Takers", ylab = "Residuals")
y = lm(total ~ expend + salary + ratio + takers + I(takers^2), data = sat)
summary(y)
par(mfrow = c(1,1))
plot(y$fitted, y$residual, xlab = "Fitted", ylab = "Residuals")
abline(h = 0)
## QQ-plot
ri = rstudent(y)
par(mfrow = c(1,2))
qqnorm(ri, ylab = "Residuals")
qqline(ri)
## Histogram
hist(ri, xlab = "Residuals")
## Half-normal plot for leverages
par(mfrow = c(1,1))
halfnorm(lm.influence(y)$hat, nlab = 4, ylab = "Leverages")
abline(h = 2*(5+1)/50)
sat[c(2,5,7,44),]
summary(sat)
max(abs(ri))
which(-ri == max(abs(ri)))
## compute p-value
2*(1 - pt(max(abs(ri)), df = 50-6-1))
## compare to alpha/n
0.05/50
