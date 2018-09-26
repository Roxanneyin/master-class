## read in the data
library(faraway)
data(uswages)
## dimension of the data
dim(uswages)
## numerical summaries
summary(uswages)
## missing values
uswages$exper[uswages$exper < 0] = NA
uswages$wage[uswages$wage > 3000] = NA
## new summary
summary(uswages)
## categorical variable
uswages$race = factor(uswages$race)
uswages$smsa = factor(uswages$smsa)
uswages$ne = factor(uswages$ne)
uswages$mw = factor(uswages$mw)
uswages$so = factor(uswages$so)
uswages$we = factor(uswages$we)
uswages$pt = factor(uswages$pt)
levels(uswages$race) = c("white", "black")
levels(uswages$smsa) = c("no", "yes")
levels(uswages$ne) = c("no", "yes")
levels(uswages$mw) = c("no", "yes")
levels(uswages$so) = c("no", "yes")
levels(uswages$we) = c("no", "yes")
levels(uswages$pt) = c("full", "part")
summary(uswages)
## graphical summaries
attach(uswages)
hist(wage)
##interesting of range[2200, 2400]
boxplot(wage)
reigon_to_data <- aggregate(wage ~ ne + mw + so + we, data = uswages, mean)
plot(educ,wage)
plot(exper,wage)
plot(race,wage)
plot(smsa,wage)
reigon_to_data