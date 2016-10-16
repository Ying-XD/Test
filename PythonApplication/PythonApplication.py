import pandas as pd
from pandas.core.frame import *
df=pd.read_csv('data_practice.txt',names=['ip','dt','flag'])
df.sort(['ip','dt','flag'],ascending=True)

df_res = df.groupby(['ip','dt']).apply(lambda df:DataFrame([[len(df), len(df[df["flag"] == 1])]]));

df_res = df_res.reset_index()
del df_res['level_2']

df_res = df_res.rename(columns={0: 'count', 1: 'count_1'})
print (df_res)

print ("count_1 >= 2")
df_res = df_res[df_res['count_1'] >= 2]

print (df_res)


