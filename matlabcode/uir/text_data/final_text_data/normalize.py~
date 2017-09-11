import pandas as pd
import numpy as np
import sys
import os
import re

InputFiles = ['TeachingData_finall.txt', 'TestData_finall.txt']
Files = [open(i, 'r') for i in InputFiles]
OutputFiles = [open(f.name[0:f.name.index('.')] + '_normalized.txt', 'w+') for f in Files]
TargetColumns = [0, 2]

Df = [pd.read_csv(i) for i in InputFiles]


for index, df in enumerate(Df):
	tmp = map(lambda x: x[0].split('\t'), df.values.tolist())
	tmp = map(lambda x: [float(k) for k in x], tmp)
	df = pd.DataFrame(tmp)
	for i in TargetColumns:
		m = np.mean(df[i].tolist())
		df[i] = map(lambda x: x - m, df[i])
	str_buffer = ["".join(str(k) + '\t' for k in j[:-1]) + str(j[-1]) + '\n' for j in df.values.tolist()]
	str_buffer = "".join(k for k in str_buffer)
	OutputFiles[index].write(str_buffer)




for i in Files:
	i.close()
for i in OutputFiles:
	i.close()


