import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from math import *


def ReadData(file_name = "out.log"):
	File = open(file_name, "r")
	values = []
	x_ticks = []
	y_ticks = []
	z_ticks = []	
	tmp = []
	parts = []

	lines = File.readlines()
	tmp = map(lambda x: x.split(), lines)
	tmp = map(lambda a: map(lambda x: float(x), a), tmp)
	counter = 0
	

	while counter < tmp.count([]):
		values = np.array(tmp[:tmp.index([])]).T.tolist()
		y_ticks.append(values[0])
		x_ticks.append(values[1])
		z_ticks.append(values[2])
		tmp = tmp[tmp.index([]) + 1:]
		counter += 1
		
	
	File.close()
	return [x_ticks, y_ticks, z_ticks]

fig = plt.figure()

ax = fig.gca(projection = '3d')

X = np.arange(0.0, 3.0, 0.1)
Y = np.arange(0.0, 3.0, 0.1)

X, Y = np.meshgrid(X, Y)
Z = np.sin(X + Y)

data = ReadData()

print X.tolist(), data[0]
print Y.tolist(), data[1]
print len(data[0]), '\t', len(X.tolist()), '\t\t', len(data[1]), '\t', len(Y.tolist())

data = ReadData(file_name = "output.txt")

#surf = ax.plot_surface(X, Y, Z, color = "green")
#surf2 = ax.plot_surface(data[0], data[1], data[2], color = "red")



surf3 = ax.plot_surface(data[0], data[1], Z - data[2], color = "blue")

ax.set_zlim(-1.1, 1.1)

plt.show()
