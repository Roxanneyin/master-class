import pandas as pd

data = pd.read_csv('C:/Users/Roxanne/Documents/GitHub/master-class/FIN-608/project2/return.csv')
data.index = data['TICKER']
data.index = [pd.to_datetime(d) for d in data.index]
data = data.dropna(axis = 1)

mse = lambda a,b: (a-b)**2/len(a)