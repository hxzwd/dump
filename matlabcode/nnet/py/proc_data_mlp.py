import os
import sys
import pandas as pd
import numpy as np

InputDelay = 15
OutputFile1_inputs = "output_data_34-43_inputs.txt"
OutputFile1_outputs = "output_data_34-43_outputs.txt"
OutputFile2_outputs = "output_data_36-43_outputs.txt"
OutputFile2_inputs = "output_data_36-43_inputs.txt"

#df1 = pd.DataFrame()
#df2 = pd.DataFrame()

#df1.from_csv("34-43_data.csv", sep = "\t")
#df2.from_csv("36-43_data.csv", sep = "\t")

#print df1

File1 = open("34-43_data.csv", "r")
File2 = open("36-43_data.csv", "r")
Data1 = File1.readlines()
Data2 = File2.readlines()
File1.close()
File2.close()


Data1 = [i.split("\t") for i in Data1]
Data2 = [i.split("\t") for i in Data2]

df1 = pd.DataFrame(np.array(Data1))
df2 = pd.DataFrame(np.array(Data2))

data1 = df1[2].get_values()[1:]
data2 = df2[2].get_values()[1:]

Tmp = []
counter = InputDelay
tmp = []

for index, value in enumerate(data1):
	if index < InputDelay:
		continue
	else:
		while counter != 0:
			tmp.append(data1[index - counter])
			counter -= 1
		Tmp.append([tmp, value])
		tmp = []
		counter = InputDelay

tmp = []
counter = InputDelay
Tmp2 = []

for index, value in enumerate(data2):
	if index < InputDelay:
		continue
	else:
		while counter != 0:
			tmp.append(data2[index - counter])
			counter -= 1
		Tmp2.append([tmp, value])
		tmp = []
		counter = InputDelay

File1_inputs = open(OutputFile1_inputs, "w+")
File2_inputs = open(OutputFile2_inputs, "w+")
File1_outputs = open(OutputFile1_outputs, "w+")
File2_outputs = open(OutputFile2_outputs, "w+")

for index, value in enumerate(Tmp):
	tmp1 = "".join(i for i in [ i.replace("\n", " ") for i in value[0] ])
	tmp1 = tmp1[:-1] + "\n"
	tmp2 = value[1].replace("\n", "") + "\n"
	File1_inputs.write(tmp1)
	File1_outputs.write(tmp2)

for index, value in enumerate(Tmp2):
	tmp1 = "".join(i for i in [ i.replace("\n", " ") for i in value[0] ])
	tmp1 = tmp1[:-1] + "\n"
	tmp2 = value[1].replace("\n", "") + "\n"
	File2_inputs.write(tmp1)
	File2_outputs.write(tmp2)


File1_inputs.close()
File2_inputs.close()
File1_outputs.close()
File2_outputs.close()
