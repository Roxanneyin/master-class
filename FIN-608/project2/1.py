import pandas as pd
import numpy as np
import itertools as it

def tracking_variance(x,y):
    price_x = np.ones((len(x),1))
    price_y = np.ones((len(y),1))
    for i in range(1,len(x)):
        price_x[i] = price_x[i-1] * (1 + x[i]/100)
        price_y[i] = price_y[i-1] * (1 + y[i]/100)
    return (((price_x - price_y).T).dot(price_x - price_y))[0][0]

my_data = pd.read_excel("C:/Users/Roxanne/Documents/GitHub/master-class/FIN-608/project2/return.xlsx")
my_data = my_data.dropna(axis=1)

my_data.index = [pd.to_datetime(d) for d in my_data['TICKER']]
my_data = my_data.drop('TICKER',axis=1)

pair_list = list(it.combinations(my_data.keys(),2))

tracking_var_list = [tracking_variance(my_data[_[0]],my_data[_[1]]) for _ in pair_list]

min_five_pairs = np.argsort(tracking_var_list)[0:20]
min_five_pairs_tikers = [pair_list[i] for i in min_five_pairs]

print(min_five_pairs_tikers)