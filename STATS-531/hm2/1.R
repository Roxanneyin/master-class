set.seed(123456789)
coeff = 0.6
armaacf1 = coeff^(0:100)
armaacf2 = ARMAacf(ar = coeff, lag.max = 100)
all(abs(armaacf1 - armaacf2) < 1e-6)
plot(armaacf1,type="l", col='red', xlab ="lag")
lines(armaacf2, lty =2, col='blue')
legend("topright", legend = c("our result", "R function"), col = c("red","blue"), lty =c(1,2))

