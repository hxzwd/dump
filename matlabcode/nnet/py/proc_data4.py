import os
import sys
import pickle
import pandas as pd
import numpy as np

l = os.listdir(os.getcwd())
l = [i for i in l if 'bin' in i]
l.sort()
d = []

for i in l:
	f = open(i, "rb")
	d.append(pickle.load(f))
	f.close()

f = open("general_data.bin", "wb")
pickle.dump(d, f)
f.close()

f = open("general_data.txt", "w")
for i in d:
	for j in i:
		f.write(j)
f.close()

n = len(d)
n = n/2 - 1
c1 = d[0][0][:-1]
c2 = d[n + 1][0][:-1]

Tmp = [[], []]
tmp = []

for i in range(0, n + 1, 1):
	tmp = d[i][1:]
	tmp = [ i.replace('\n', '') for i in tmp ]
	tmp = [ i.split('\t')[1:] for i in tmp ]
	Tmp[0] = Tmp[0] + tmp
tmp = []
for i in range(n + 1, len(d), 1):
	tmp = d[i][1:]
	tmp = [ i.replace('\n', '') for i in tmp ]
	tmp = [ i.split('\t')[1:] for i in tmp ]
	Tmp[1] = Tmp[1] + tmp

df1 = pd.DataFrame(np.array(Tmp[0]), columns = ["Data/Time", c1])
df2 = pd.DataFrame(np.array(Tmp[1]), columns = ["Data/Time", c2])

fn1 = c1[ c1.rfind(' ') + 1 : ] + "_data.csv"
fn2 = c2[ c2.rfind(' ') + 1 : ] + "_data.csv"

df1.to_csv(fn1, sep = "\t", encoding = "utf-8")
df2.to_csv(fn2, sep = "\t", encoding = "utf-8")


