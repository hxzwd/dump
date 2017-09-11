from math import *
import numpy as np
from subprocess import call
import sys

configs = []
function_name = ""
x_min = 0
x_max = 0
x_steps = 0
x_step = 0
file_name = ""
num_in = 0
num_out = 0
y_ticks = []
x_ticks = []
program = ""

if(len(sys.argv) != 0):
	for index, value in enumerate(sys.argv):
		if index == 0 or index == 1:
			continue
		else:
			configs.append(value)

if(configs == []):
	configs.append("gen.cfg")


for config_file in configs:
	configs = []
	function_name = ""
	x_min = 0
	x_max = 0
	x_steps = 0
	x_step = 0
	file_name = ""
	num_in = 0
	num_out = 0
	y_ticks = []
	x_ticks = []
	f = file(config_file, "r")
	for line in f:
		param = ""
		if ":" in line:
			param = line.split(':')[-1].strip()
		else:
			continue
		if param == "":
			continue
		if "function" in line:
			function_name = param
		if "output file" in line:
			file_name = param
		if "number of inputs" in line:
			num_in = int(param)
		if "number of outputs" in line:
			num_out = int(param)
		if "input maximum" in line:
			x_max = float(param)
		if "input minimum" in line:
			x_min = float(param)
		if "number of steps" in line:
			x_steps = int(param)
		if "step size" in line:
			x_step = float(param)
		if "execute" in line:
			if param == "none":
				continue
			else:
				program = param
			
	f.close()

	def func(x):
		l = function_name.find('(')
		r = function_name.find(')')
		a = function_name[l + 1: r]
		a = a.replace('x', str(x))
		fn = function_name[:l + 1] + a + function_name[r:]
		return eval(fn)



	x_steps = int(abs(x_max - x_min)/x_step)
	x_ticks = np.linspace(x_min, x_max, x_steps)
	x_ticks = [x_min + index*x_step for index, value in enumerate(xrange(x_steps + 1))]


	y_ticks = [func(i) for i in x_ticks]

	f = file(file_name, "w+")
	f.write(str(len(x_ticks)) + " " + str(num_in) + " " + str(num_out))

	for index, value in enumerate(x_ticks):
		print value
		print y_ticks[index]
		f.write("\n" + str(value) + " 1.0" + "\n" + str(y_ticks[index]))

	f.close()

	print "input max: ", x_max
	print "input min: ", x_min
	print "step: ", x_step
	print "steps: ", x_steps
	print "x size: ", len(x_ticks)
	print "y size: ", len(y_ticks)
	print "file name: ", file_name
	print "num of inputs and outputs: ", num_in, num_out

	if program != "":
		print "call ", program
		call([program])

