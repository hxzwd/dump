import numpy as np
import matplotlib.pyplot as plt
import pickle
import os
import sys
import pandas as pd
import time
import datetime
import re

from math import *
from cmath import *

f1 = '34-43_data.csv'
f2 = '36-43_data.csv'

n1 = f1[ : f1.find('.')]
n2 = f2[ : f2.find('.')]

os.chdir('data')

df1 = pd.DataFrame.from_csv(f1, sep = '\t')
df2 = pd.DataFrame.from_csv(f2, sep = '\t')

file = open('ch_data.dump', 'wb')

Obj = { n1 : df1, n2 : df2 }
pickle.dump(Obj, file)
file.close()

P = df1[df1.columns[1]].values
Of = df2[df2.columns[1]].values



#file1 = open(n1 + '.dump', 'wb')
#file2 = open(n2 + '.dump', 'wb')
file1 = open('P.dump', 'wb')
file2 = open('Of.dump', 'wb')

pickle.dump(P, file1)
pickle.dump(Of, file2)
file1.close()
file2.close()

os.chdir('../')

