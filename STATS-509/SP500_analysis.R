X = read.csv("D:\\STUDY\\graduate\\Umich\\Study\\2018 win\\STATS 509\\^GSPC.csv", header = TRUE)
SP500wk = rev(X$Close)
plot(SP500wk)

SP500wk_lreturn = diff(log(SP500wk))
windows()
plot(SP500wk_lreturn, type = 'l')

##以上的数据是daily的，weekly的同理也可以画出来