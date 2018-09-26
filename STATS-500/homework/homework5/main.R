library(faraway)
data(cheddar)
temp = lm(taste ~ Acetic + H2S + Lactic, data = cheddar)
summary(temp)
## plot residuals vs fitted values
ri = rstudent(temp)
plot(temp$fitted, ri, xlab = "Fitted", ylab = "STResiduals")
abline(h = 0)
plot(cheddar$Acetic, ri, xlab = "Acetic", ylab = "STResiduals")
plot(cheddar$H2S, ri, xlab = "H2S", ylab = "STResiduals")
plot(cheddar$Lactic, ri, xlab = "Lactic", ylab = "STResiduals")
## QQ-plot
par(mfrow = c(1,2))
qqnorm(ri, ylab = "Residuals")
qqline(ri)
## Histogram
hist(ri, xlab = "Residuals")
## Half-normal plot for leverages
par(mfrow = c(1,1))
halfnorm(lm.influence(temp)$hat, nlab = 1, ylab = "Leverages")
abline(h = 2*(3+1)/30)
max(abs(ri))
which(ri == max(abs(ri)))
## compute p-value
2*(1 - pt(max(abs(ri)), df = 30-4-1))
## compare to alpha/n
0.05/30
## compute cook's distance
cook = cooks.distance(temp)
plot(dfbeta(temp)[,1], ylab = "Change in beta0 coef")
abline(h=0)
identify(dfbeta(temp)[,1])
halfnorm(cook, nlab = 6, ylab = "Cook's distance")
cheddar[c(1,8,20,30,12,15),]
plot(dfbeta(temp)[,2], ylab = "Change in beta1 coef")
abline(h=0)
identify(dfbeta(temp)[,2])
plot(dfbeta(temp)[,3], ylab = "Change in beta2 coef")
abline(h=0)
identify(dfbeta(temp)[,3])
plot(dfbeta(temp)[,4], ylab = "Change in beta3 coef")
abline(h=0)
identify(dfbeta(temp)[,4])
summary(temp)
cheddar1 = cheddar[-c(30),]
y = lm(taste ~ Acetic + H2S + Lactic, data = cheddar1)
coef(y)
cheddar1 = cheddar[-c(20),]
y = lm(taste ~ Acetic + H2S + Lactic, data = cheddar1)
coef(y)
cheddar1 = cheddar[-c(15),]
y = lm(taste ~ Acetic + H2S + Lactic, data = cheddar1)
coef(y)
cheddar1 = cheddar[-c(12),]
y = lm(taste ~ Acetic + H2S + Lactic, data = cheddar1)
coef(y)
## Partial regression plot
par(mfrow = c(1,2))
delta = residuals(lm(taste ~ H2S + Lactic, data = cheddar))
gamma = residuals(lm(Acetic ~ H2S + Lactic, data = cheddar))
plot(gamma, delta, xlab = "Acetic residuals", ylab = "taste residuals")
tempi = lm(delta ~ gamma)
abline(reg = tempi)
## partial residual plot
plot(cheddar$Acetic, temp$residuals + coef(temp)['Acetic']*cheddar$Acetic, xlab = "Acetic", ylab = "taste(adjusted for Acetic)")
abline(a = 0, b = coef(temp)['Acetic'])

## Partial regression plot
delta = residuals(lm(taste ~ Acetic + Lactic, data = cheddar))
gamma = residuals(lm(H2S ~ Acetic + Lactic, data = cheddar))
plot(gamma, delta, xlab = "H2S residuals", ylab = "taste residuals")
tempi = lm(delta ~ gamma)
abline(reg = tempi)
## partial residual plot
plot(cheddar$H2S, temp$residuals + coef(temp)['H2S']*cheddar$H2S, xlab = "H2S", ylab = "taste(adjusted for H2S)")
abline(a = 0, b = coef(temp)['H2S'])

## Partial regression plot
delta = residuals(lm(taste ~ Acetic + H2S, data = cheddar))
gamma = residuals(lm(Lactic ~ Acetic + H2S, data = cheddar))
plot(gamma, delta, xlab = "Lactic residuals", ylab = "taste residuals")
tempi = lm(delta ~ gamma)
abline(reg = tempi)
## partial residual plot
plot(cheddar$Lactic, temp$residuals + coef(temp)['Lactic']*cheddar$Lactic, xlab = "Lactic", ylab = "taste(adjusted for Lactic)")
abline(a = 0, b = coef(temp)['Lactic'])
result = lm(taste ~ H2S + Lactic, data = cheddar)
summary(result)