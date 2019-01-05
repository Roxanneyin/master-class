import pandas as pd
import numpy as np
import xgboost as xgb

def myfun(x,quantile25,quantile50,quantile75):
    if x >= quantile75:
        return 3
    elif x <= quantile25:
        return 0
    elif x >= quantile50 and x < quantile75:
        return 2
    else:
        return 1
    
def myfun2(x,quantile16,quantile83,quantile33,quantile66):
    if x >= quantile83 or x <= quantile16:
        return 2
    elif x <= quantile66 and x>= quantile33:
        return 0
    else:
        return 1
      
def fix_div0(x):
    if x == "#DIV/0!":
        return "0"  

#load data and drop useless labels
#data = pd.read_csv("FinalAllFeaturesLabel.csv",low_memory=False)
#data = data.drop(['ABBREVIATION_x',
#                  'ABBREVIATION_y','ABBREVIATION_x.1',
#                  'ABBREVIATION_y.1','Unnamed: 0.1',
#                  'FAVORITE_PERCENT_ASSET100000',
#                  'FAVORITE_PERCENT_INCREASE_ASSET100000',
#                  'FAVORITE_PERCENT_ASSET500000', 
#                  'FAVORITE_PERCENT_INCREASE_ASSET500000',
#                  'cnt_1', 'cnt_1.1','cnt_2',
#                  'cnt_2.1','cnt_3','cnt_3.1',
#                  'cnt_4', 'cnt_4.1','cnt_5',
#                  'cnt_5.1','cnt_6','cnt_6.1',
#                  'cnt_7', 'cnt_7.1',
#                  'DateTime','Unnamed: 0',
#                  'rk', 'rkleading1',
#                  'FAVORITE_PERCENT_y'
#                  ],axis=1)

data = pd.read_csv("allFeaFac.csv",low_memory=False)
data = data.drop(['STOCK_ABBREVIATION','ABBREVIATION_x',
                  'ABBREVIATION_y','ABBREVIATION',
                  'cnt_1', 'cnt_1.1','cnt_2',
                  'cnt_2.1','cnt_3','cnt_3.1',
                  'cnt_4', 'cnt_4.1','cnt_5',
                  'cnt_5.1','cnt_6','cnt_6.1',
                  'cnt_7', 'cnt_7.1',
                  'DateTime','Unnamed: 0',
                  'FAVORITE_PERCENT_ASSET100000',
                  'FAVORITE_PERCENT_INCREASE_ASSET100000',
                  'FAVORITE_PERCENT_ASSET500000',
                  'FAVORITE_PERCENT_INCREASE_ASSET500000',
                  'FAVORITE_PERCENT_y',
                  'FAVORITE_PERCENT_ROOKIE',
                  'FAVORITE_PERCENT_INCREASE_ROOKIE',
                  'FAVORITE_PERCENT_1YEAR',
                  'FAVORITE_PERCENT_INCREASE_1YEAR',
                  'FAVORITE_PERCENT_3YEAR',
                  'FAVORITE_PERCENT_INCREASE_3YEAR',
                  'FAVORITE_PERCENT_5YEAR',
                  'FAVORITE_PERCENT_INCREASE_5YEAR'],axis=1)


#temp = pd.DataFrame(data.groupby(['DATE'])['return'].mean())
#temp = temp.reset_index()
#temp = temp.rename(columns={"return":"M_RETURN"})
#data = data.merge(temp,left_on="DATE",right_on="DATE")
#data["E_RETURN"] = data['return'] - data['M_RETURN']
#data = data.drop(['return','returnlag1'],axis=1)
#data["E_RETURN_LAG1"] = data.groupby(['STOCK_CODE'])["E_RETURN"].shift(-1)


available_feature_names = list(data.columns)
#above contains all the columns of potential labels
stock_pool = list(set(data["STOCK_CODE"][100:500]))
#above is the list of all unique stock_codes
return_data = data["return"].dropna()
quantile25 = np.percentile(return_data,25)
quantile50 = np.percentile(return_data,50)
quantile75 = np.percentile(return_data,75)
quantile33 = np.percentile(return_data,33)
quantile66 = np.percentile(return_data,66)
quantile10 = np.percentile(return_data,10)
quantile90 = np.percentile(return_data,90)
quantile83 = np.percentile(return_data,83)
quantile16 = np.percentile(return_data,16)
#now, let's pick one example and do the analysis
correct_rate = {}
i = 0
confusion_matrix = np.zeros((len(stock_pool),4,4))
for sample_stock_code in stock_pool:
    try:
        #first, pick the required data using the given stock_code
        sample = data[data["STOCK_CODE"]==sample_stock_code]
        #select features
#        selected_features = ['CLICK',
#                             'POSITIVE_NEWS', 
#                             'NEGATIVE_NEWS',
#                             "E_RETURN_LAG1"]
        magic_str = "return"
#                             'CLICK_PERCENT_ASSET100000',
#                             'CLICK_PERCENT_ASSET500000',
#                             'CLICK_PERCENT_ASSET1000000',
#                             'PERCENTAGE_ASSET100000',
#                             'PERCENTAGE_ASSET500000',
#                             'PERCENTAGE_ASSET1000000',
#                             'PERCENT_INCREASE',
#'CLICK',
#                             'FAVORITE_PERCENT_x',
        selected_features = ['CLICK',
                             'FAVORITE_PERCENT_x',
                             'beta',
                             'book_to_price',
                             'comovement',
                             'earnings_yield',
                             'growth',
                             'leverage',
                             'liquidity',
                             'momentum',
                             'non_linear_size',
                             'residual_volatility',
                             'size',
                              magic_str]
        
        sample_data = sample[selected_features]
        sample_data.dropna()
        #drop NA values
        sample_data = sample_data.dropna()
        #convert type
        sample_data.applymap(lambda x: fix_div0(x))
        sample_data.applymap(lambda x: float(x))
        #classify return data into two categories
        sample_data[magic_str] = sample_data[magic_str].map(lambda x: myfun(x,quantile25,quantile50,quantile75))
        #train_test_split
        available_data_num = len(sample_data)
        test_size = int(len(sample_data)/5)
        train_size = available_data_num - test_size
        train = sample_data[0:train_size]
        test = sample_data[train_size:]
        #convert to DMatrix
        dtrain = xgb.DMatrix(data = train[selected_features[0:-1]],
                             label=train[magic_str])
        dtest = xgb.DMatrix(data = test[selected_features[0:-1]],
                             label=test[magic_str])
        param = {'max_depth':4, 
                 'eta':0.02,
                 'gamma':0.5,
                 'silent':1, 
                 'subsample':0.2,
                 'alpha':0,
                 'lambda':2,
                 'num_class':4,
                 'objective':'multi:softmax',
                 'eval_metric':'mlogloss'}
        
        watchlist = [(dtrain, 'train'),(dtest,"test")]
        numRound = 1000
        bst = xgb.train(params = param,
                        dtrain = dtrain,
                        num_boost_round = numRound,
                        early_stopping_rounds=10,
                        evals = watchlist)
        aa = np.array(test[magic_str])
        bb = bst.predict(dtest)
        for k in range(len(aa)):
            confusion_matrix[i,aa[k],int(bb[k])] += 1
        correct_rate[sample_stock_code] = sum(aa==bb)/len(aa)
        
    except:
        pass
    i += 1
  
sum_all_stocks = np.sum(confusion_matrix,axis=0)
predicted_accuracy_by_actural_value = (sum_all_stocks.T / np.sum(sum_all_stocks,axis=1)).T
#all_list = list(correct_rate.keys())
#code_list = []
#name_list = []
#for i in all_list:
#    if correct_rate[i] >= 0.6:
#        code_list.append(i)
#        name_list.append(data[data["STOCK_CODE"]==i]['STOCK_ABBREVIATION'].iloc[0])
#    
#code = pd.DataFrame(code_list)
#code.to_csv("code_1.csv")   
#name = pd.DataFrame(name_list)
#name.to_csv("name_1.csv")

np.mean(list(correct_rate.values()))

#import matplotlib.pyplot as plt
##plt.hist(data["E_RETURN_LAG1"].dropna(), bins='auto')  # arguments are passed to np.histogram
##plt.title("Histogram with 'auto' bins")
##plt.xlim(-15,15)
##plt.show()
#
#plt.hist(list(correct_rate.values()), bins='auto')  # arguments are passed to np.histogram
#plt.show()
