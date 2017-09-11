import numpy as np
from pyfann import libfann as lf
from math import *

def draw_fig(fig, fig2):
	tmp = ""
	tmp2 = ""
	for index, value in enumerate(fig):
		if(fig2[index] < 0):
			tmp2 += 'X'
		if(fig2[index] > 0):
			tmp2 += ' '
		if(value < 0):
			tmp += 'X'
		if(value > 0):
			tmp += ' '
		if((index + 1) % 5 == 0):
			print(tmp2 + '\t\t' + tmp)
			tmp = ""
			tmp2 = ""
		else:
			continue

def draw_fig2(fig):
	tmp = ""
	for index, value in enumerate(fig):
		if(value < 0):
			tmp += 'X'
		if(value > 0):
			tmp += ' '
		if((index + 1) % 5 == 0):
			print(tmp)
			tmp = ""
		else:
			continue
			

f = file("rec.txt", "w+")

data = []
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, 1, 1,   1, -1, 1, -1, 1,   -1, 1, 1, 1, -1])
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, -1, -1, 1, 1,   1, -1, -1, 1, 1,   -1, 1, 1, -1, 1])
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, -1, -1, 1, 1,   1, -1, -1, 1, 1,   -1, 1, 1, -1, 1])
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, -1, 1,   1, 1, -1, -1, 1,   1, 1, -1, 1, -1])
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, -1, 1,   1, 1, -1, -1, 1,   1, -1, 1, 1, -1])

for i in data:
	draw_fig(i, data[0])


f.write(str(len(data)) + " " + str(25) + " " + str(25) + "\n")

for index, value in enumerate(data):
	ws = ""
	for i in value:
		ws += str(i) + " "
	ws += "\n"
	for i in data[0]:
		ws += str(i) + " "
	ws += "\n"
	f.write(ws)

f.close()

f = file("rec2.txt", "w+")

data = []
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   -1, 1, 1, 1, 1])
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, 1, 1,   1, 1, -1, 1, 1,   1, 1, -1, 1, 1])
data.append([1, -1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   1, -1, 1, 1, 1])
data.append([1, 1, 1, 1, 1,  -1, 1, 1, -1, 1,  -1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   -1, 1, 1, 1, 1])
data.append([-1, 1, 1, 1, -1,  1, -1, 1, -1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   1, 1, 1, 1, 1])

for i in data:
	draw_fig(i, data[0])

f.write(str(len(data)) + " " + str(25) + " " + str(25) + "\n")

for index, value in enumerate(data):
	ws = ""
	for i in value:
		ws += str(i) + " "
	ws += "\n"
	for i in data[0]:
		ws += str(i) + " "
	ws += "\n"
	f.write(ws)

f.close()

max_iterations = 500000
iterations_between_reports = 1000
desired_error = 0.01

ann = lf.neural_net()

ann.create_standard_array((25, 1))
ann.set_activation_function_hidden(lf.SIGMOID_SYMMETRIC)
ann.set_activation_function_output(lf.LINEAR)
ann.train_on_file("rec3.txt", max_iterations, iterations_between_reports, desired_error)

ann.save("rec.net")

"""
idata = [1, 1, 1, 1, -1,  -1, 1, 1, -1, 1,  1, -1, -1, 1, 1,   1, 1, -1, -1, 1,   -1, 1, 1, -1, 1]
odata = ann.run(idata)
print odata
draw_fig([round(i) for i in odata], idata)
idata = [1, 1, 1, 1, 1,  -1, 1, 1, -1, 1,  1, -1, -1, 1, 1,   1, -1, -1, 1, 1,   -1, 1, 1, -1, 1]
odata = ann.run(idata)
print odata
draw_fig([round(i) for i in odata], idata)
idata = [1, -1, 1, 1, -1,  1, 1, -1, -1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   -1, 1, 1, 1, 1]
odata = ann.run(idata)
print odata
draw_fig([round(i) for i in odata], idata)
idata = [-1, 1, 1, -1, 1,  1, -1, -1, 1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   -1, 1, 1, 1, 1]
odata = ann.run(idata)
print odata
draw_fig([round(i) for i in odata], idata)
"""

xy = ['0', 'X', 'Y']
idata = [1, 1, 1, 1, -1,  -1, 1, 1, -1, 1,  1, -1, -1, 1, 1,   1, 1, -1, -1, 1,   -1, 1, 1, -1, 1]
odata = ann.run(idata)
draw_fig2(idata)
print odata[0]
if(odata[0] < 0.0):
	print '\nY\n'
if(odata[0] > 0.0):
	print '\nX\n'
idata = [1, 1, 1, 1, 1,  -1, 1, 1, -1, 1,  1, -1, -1, 1, 1,   1, -1, -1, 1, 1,   -1, 1, 1, -1, 1]
odata = ann.run(idata)
draw_fig2(idata)
print odata[0]
if(odata[0] < 0.0):
	print '\nY\n'
if(odata[0] > 0.0):
	print '\nX\n'

idata = [1, -1, 1, 1, -1,  1, 1, -1, -1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   -1, 1, 1, 1, 1]
odata = ann.run(idata)
draw_fig2(idata)
print odata[0]
if(odata[0] < 0.0):
	print '\nY\n'
if(odata[0] > 0.0):
	print '\nX\n'

idata = [-1, 1, 1, -1, 1,  1, -1, -1, 1, 1,  1, 1, -1, 1, 1,   1, -1, 1, 1, 1,   -1, 1, 1, 1, 1]
odata = ann.run(idata)
draw_fig2(idata)
print odata[0]
if(odata[0] < 0.0):
	print '\nY\n'
if(odata[0] > 0.0):
	print '\nX\n'

