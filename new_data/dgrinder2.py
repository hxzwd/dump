import os
import sys
import numpy as np
import pandas as pd
import re
import pickle

file = open('data/cells.bin', 'rb')
DF = pickle.load(file)
file.close()

d = DF[0]

for i in DF[1:]:
	d = d.append(i)

d.index = range(0, len(d.index))

file = open('data/merged_cells.bin', 'wb')
pickle.dump(d, file)
file.close()

d.to_csv('data/pandas/merged_cells.csv', sep = '\t')

dd = d[ [ i for i in d.columns if i != 'dt' ] ].values
hh = d[ [ i for i in d.columns if i != 'dt' ] ].columns.tolist()

file = open('data/cells_pure.txt', 'w')

file.write("".join(i + '\t' for i in hh)[:-1] + '\n')

for i in dd:
		file.write("".join(j + '\t' for j in i.tolist())[:-1] + '\n')

file.close()		

