import os
import sys
import numpy as np
import pandas as pd
import re
import pickle


fs = os.listdir('data/set_1')
fsn = [ i[:i.index('.')] for i in fs ]
Counter = 0
DF = []

for F in fsn[:-2]:
	file = open('data/set_1/' + F + '.txt', 'r')
	d = file.readlines()
	file.close()

	dt = ""
	for i, v in enumerate(d):
		if 'Параметер' in v:
			dt = d[i]

	if dt != "":
		dt = dt.strip().split(';')
		dt = [ i.strip() for i in dt[1:] if i != '' ]
		
	ind = [ i + 1 for i, v in enumerate(d) if v == '\n' ]
	ind = [0] + ind[:-1]

	p = re.compile('[0-9]{2}\-[0-9]{2}')
	cells = [ p.findall(d[i])[0] for i in ind if p.findall(d[i]) != None ]

	d = [ i for i in d if ( p.findall(i) != [] or 'СУЗ' in i or 'ДКЭВ' in i ) and not 'нет' in i ]
	d = [ ([i], p.findall(i))[p.findall(i) != []] for i in d ]
	d = [ i[0] for i in d ]

	dd = []
	for i in d:
		if 'СУЗ' in i:
			q = i.strip().split(';')
			q = [i.strip().replace(',', '.') for i in q if i != '']
			q = q[1:]
			dd.append(q)
			continue
		if 'ДКЭВ' in i:
			p = re.compile('\{{1}[0-9,\s;]*\}{1}')
			q = p.findall(i)
			q = [ i.replace(';', '').replace('{', '').replace('}', '').replace(',', '.').strip() for i in q ]
			q = [ [ float(j) for j in i.split(' ') ] for i in q ]
			q = [ (i[0] + i[1] - (i[2] + i[3]))/sum(i) for i in q ]
			dd.append(q)

			
	dds = [ [ str(j) for j in i ] for i in dd ]
	df = pd.DataFrame(np.array([dt] + dds).T, columns = ['dt'] + cells)
	Counter += len(dt)
	df.to_csv('data/pandas/' + F + '.csv', sep = '\t')
	DF.append(df)
	
	
file = open('data/cells.bin', 'wb')
pickle.dump(DF, file)
file.close()
