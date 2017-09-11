import pandas as pd
import numpy as np
import sys
import os
import re

Extension = 'txt'

Files = os.listdir(os.getcwd())

print Files

for i in Files:
	if i[-3:] != Extension:
		Files.remove(i)
Files.remove(sys.argv[0])

print Files 

DataFrames = []

Buffer = []
for i in Files:
	f = open(i, 'r')
	f.readline()
	Buffer.extend(f.readlines())
	f.close()

print len(Buffer)
print Buffer[100:150]

s1 = pd.Series(Buffer)
s2 = s1.str.split(' ')
"""
for index, value in enumerate(s2):
	tmp = list(map(lambda x: [value.remove('') for i in range(0, value.count(''))], value))
#	print value
	tmp = list(map(lambda x: x.count(".") == 1 and float(x.replace(",", ".")) or x, value))
	value.remove(value[0])
	re.search(str(value)
#	s2[index] = tmp """
tmp_indexed = [([str(k)] + [i for i in s2[k] if i != ''][1:]) for k in s2.index]
tmp = [([i for i in s2[k] if i != ''][1:]) for k in s2.index]
tmp = map(lambda x: x[0:-1] + [x[-1].replace('\r\n', '')], tmp)
df = pd.DataFrame(tmp, columns=['Date', 'Time', 'A', 'B'])
df_sorted = df.sort(columns = ['Date', 'Time'])
df = pd.DataFrame(df_sorted.values, columns=['Date', 'Time', 'A', 'B'])

Output_file = open('gout_indexed.txt', 'w+')
tmp_str = df[['A', 'B']].to_string()
Output_file.write(tmp_str[tmp_str.index('\n') + 1:])
Output_file.close()

Output_file = open('gout.txt', 'w+')
tmp_str = df[['A', 'B']].values.tolist()
tmp_str = map(lambda x: x[0] + '\t' + x[1] + '\n', tmp_str)
tmp_str = "".join(i for i in tmp_str)
Output_file.write(tmp_str)
Output_file.close()

"""
tmp2 = tmp
for i in tmp2:
	if i[-1][-1] != '\n':
		tmp2[tmp2.index(i)][-1] += '\n'
#tmp = map(lambda x: x[0:-1] + [x[-1].replace('\r\n', '')], tmp)
tmp3 = [[k for k in i if k.count('.') != 2 and k.count(':') != 2] for i in tmp2]
tmp_str = "".join("".join(i + '\t' for i in k)[:-1] for k in tmp2)

Output_file = open('gout_indexed.txt', 'w+')
Output_file.write(tmp_str)
Output_file.close()"""


