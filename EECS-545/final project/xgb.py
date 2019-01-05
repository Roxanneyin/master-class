import pandas as pd
import numpy as np
import xgboost as xgb

def myfun(x):
    if x>=2.5:
        return 3
    elif x>=0 and x<2:
        return 2
    elif x<= -2.5:
        return 1
    else:
        return 0
    
def fix_div0(x):
    if x == "#DIV/0!":
        return "0"  

#load data and drop useless labels
data = pd.read_csv("FinalAllFeaturesLabel.csv",low_memory=False)
data = data.drop(['STOCK_ABBREVIATION','ABBREVIATION_x',
                  'ABBREVIATION_y','ABBREVIATION_x.1',
                  'ABBREVIATION_y.1','Unnamed: 0.1',
                  'FAVORITE_PERCENT_ASSET100000',
                  'FAVORITE_PERCENT_INCREASE_ASSET100000',
                  'FAVORITE_PERCENT_ASSET500000', 
                  'FAVORITE_PERCENT_INCREASE_ASSET500000',
                  'cnt_1', 'cnt_1.1','cnt_2',
                  'cnt_2.1','cnt_3','cnt_3.1',
                  'cnt_4', 'cnt_4.1','cnt_5',
                  'cnt_5.1','cnt_6','cnt_6.1',
                  'cnt_7', 'cnt_7.1',
                  'DateTime','Unnamed: 0',
                  'rk', 'rkleading1',
                  'FAVORITE_PERCENT_y'
                  ],axis=1)

#data = pd.read_csv("allFeaturesandlabels.csv",low_memory=False)
#data = data.drop(['STOCK_ABBREVIATION','ABBREVIATION_x',
#                  'ABBREVIATION_y','ABBREVIATION',
#                  'cnt_1', 'cnt_1.1','cnt_2',
#                  'cnt_2.1','cnt_3','cnt_3.1',
#                  'cnt_4', 'cnt_4.1','cnt_5',
#                  'cnt_5.1','cnt_6','cnt_6.1',
#                  'cnt_7', 'cnt_7.1',
#                  'DateTime','Unnamed: 0',
#                  'FAVORITE_PERCENT_ASSET100000',
#                  'FAVORITE_PERCENT_INCREASE_ASSET100000',
#                  'FAVORITE_PERCENT_ASSET500000',
#                  'FAVORITE_PERCENT_INCREASE_ASSET500000',
#                  'FAVORITE_PERCENT_y',
#                  'FAVORITE_PERCENT_ROOKIE',
#                  'FAVORITE_PERCENT_INCREASE_ROOKIE',
#                  'FAVORITE_PERCENT_1YEAR',
#                  'FAVORITE_PERCENT_INCREASE_1YEAR',
#                  'FAVORITE_PERCENT_3YEAR',
#                  'FAVORITE_PERCENT_INCREASE_3YEAR',
#                  'FAVORITE_PERCENT_5YEAR',
#                  'FAVORITE_PERCENT_INCREASE_5YEAR'],axis=1)

temp = pd.DataFrame(data.groupby(['DATE'])['return'].mean())
temp = temp.reset_index()
temp = temp.rename(columns={"return":"M_RETURN"})
data = data.merge(temp,left_on="DATE",right_on="DATE")
data["E_RETURN"] = data['return'] - data['M_RETURN']
data = data.drop(['return','returnlag1'],axis=1)
data["E_RETURN_LAG1"] = data.groupby(['STOCK_CODE'])["E_RETURN"].shift(-1)
   
available_feature_names = list(data.columns)
#above contains all the columns of potential labels
stock_pool = list(set(data["STOCK_CODE"]))
#above is the list of all unique stock_codes

#now, let's pick one example and do the analysis
correct_rate = {}
startIndex = 500
sampleSize = 10
endIndex = startIndex + sampleSize
for sample_stock_code in stock_pool[startIndex:endIndex]:
    try:
        #first, pick the required data using the given stock_code
        sample = data[data["STOCK_CODE"]==sample_stock_code]
        #select features
        selected_features = ['CLICK',
                             'POSITIVE_NEWS', 
                             'NEGATIVE_NEWS',
                             "E_RETURN"]
        
        #selected_features = ['CLICK',
        #                     'CLICK_PERCENT_ASSET100000',
        #                     'CLICK_PERCENT_ASSET500000',
        #                     'CLICK_PERCENT_ASSET1000000',
        #                     'FAVORITE_PERCENT_x',
        #                     'PERCENTAGE_ASSET100000',
        #                     'PERCENTAGE_ASSET500000',
        #                     'PERCENTAGE_ASSET1000000',
        #                     'PERCENT_INCREASE',
        #                     "E_RETURN_LAG1"]
        
        sample_data = sample[selected_features]
        sample_data.dropna()
        #drop NA values
        sample_data = sample_data.dropna()
        #convert type
        sample_data.applymap(lambda x: fix_div0(x))
        sample_data.applymap(lambda x: float(x))
        #classify return data into two categories
        sample_data["E_RETURN"] = sample_data["E_RETURN"].map(lambda x: myfun(x))
        #train_test_split
        available_data_num = len(sample_data)
        test_size = int(len(sample_data)/3)
        train_size = available_data_num - test_size
        train = sample_data[0:50]
        test = sample_data[50:]
        #convert to DMatrix
        dtrain = xgb.DMatrix(data = train[selected_features[0:-1]],
                             label=train["E_RETURN"])
        dtest = xgb.DMatrix(data = test[selected_features[0:-1]],
                             label=test["E_RETURN"])
        param = {'max_depth':6,
                 'eta':0.02,
                 'gamma': 0.2,
                 'silent':1, 
                 'num_class':4,
                 'subsample':0.7,
                 'colsample_bytree': 0.7,
                 'min_child_weight': 3,
                 'alpha':0,
                 'lambda':3,
                 'objective': 'multi:softmax',
                 'eval_metric':'mlogloss'}
        
        watchlist = [(dtrain, 'train'),(dtest,"test")]
        numRound = 200
        bst = xgb.train(params = param,
                        dtrain = dtrain,
                        num_boost_round = numRound,
                        evals = watchlist
                        )
        aa = np.array(test["E_RETURN"])
        bb = bst.predict(dtest)
        correct_rate[sample_stock_code] = sum(aa==bb)/len(aa)
    except:
        pass
