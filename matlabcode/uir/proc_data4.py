import os
import sys
import pickle

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

f = open("general_data.txt", "w+")
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



