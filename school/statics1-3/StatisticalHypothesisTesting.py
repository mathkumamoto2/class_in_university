import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import pandas as pd

rng4=np.random.default_rng(41)
M4=10000

def t_diff_simu(n,m1,m2,alpha):
    x=rng4.normal(loc=1,scale=1.0,size=(M4,n))
    y=rng4.normal(loc=1,scale=1.0,size=(M4,n))
    p=stats.ttest_ind(x,y,axis=1,equal_var=True).pvalue
    return int(np.count_nonzero(p<alpha))

for n,a,b,alpha in []
