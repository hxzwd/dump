import numpy as np
import matplotlib.pyplot as plt
import pickle
import os
import sys
import pandas as pd
import time
import datetime
import re

from math import *
from cmath import *

Tbegin = 0.0
Tend = 5.0
Tstep = 0.001

Signal = "10*np.sin(10*2*pi*t) + 8*np.sin(5*2*pi*t)"

Pnum = 250

x = None
T = []
xT = []
Ind = []
Xm = []
freq = []
freqp = []
freqpm = []
i0 = []
Xm0 = []
X0 = []
A0 = []
Ns = []

def sigspec(signal = Signal, Tparams = [Tbegin, Tend, Tstep]):
	p = re.compile('([\s]*[+]{1}[\s]*noise[\(]{1})([^\)]*)([\)]{1})')
	mt = p.findall(signal)
	[Tb, Te, Ts] = Tparams
	T = np.arange(Tb, Te, Ts)
	Ns = [0.0 for i in T]
	#xT = x(T)
	noise = []
	if len(mt) != 0:
		signal = signal.replace("".join(i for i in mt[0]), "")
		noise = mt[0][1].replace(' ', '').split(',')
		noiset = noise[0]
		noisep = [float(i) for i in noise[1:]]
		print("Signa: ", signal, ' with random variable: ', noiset, noisep)
		if noiset == 'normal':
			Ns = np.random.normal(noisep[0], noisep[1], len(T)).tolist()
	else:
		print("Signal: ", signal)
	print("t:\t[", str(Tb), ", ", str(Te), "]")
	print("delta t:\t", str(Tstep))
	x = eval("lambda t: " + signal)
	xT = [x(v) + Ns[i] for i, v in enumerate(T)]
	Ind = range(0, len(T))
	X = np.fft.fft(xT)
	Xm = X.conj()*X
	freq = np.fft.fftfreq(T.shape[-1])
	freqp = [i for i in freq if i >= 0]
	freqpm = [i/Ts for i in freqp]
	i0 = range(0, len(freqpm))
	Xm0 = Xm[:len(freqpm)].real
	X0 = X[:len(freqpm)]
	A0 = [i**0.5/len(freqpm) for i in Xm0]
	return {'p_num' : Pnum, 't_param' : [Tparams], 'signal' : x, 'ind' : Ind, 'time' : T, 'x' : xT, 'X': X, 'X2' : Xm, 'f_all' : freq, 'fp' : freqp, 'f' : freqpm, 'indp' : i0, 'X0' : X0, 'Xm0' : Xm0, 'A' : A0}


def sigspecd(signal, Tparams = [Tbegin, Tend, Tstep]):
	[Tb, Te, Ts] = Tparams
	T = np.arange(Tb, Te, Ts)
	print("D signal, size: ", str(len(signal)))
	print("t:\t[", str(Tb), ", ", str(Te), "]")
	print("delta t:\t", str(Tstep))
	x = signal
	xT = [x[i] for i, v in enumerate(T)]
	Ind = range(0, len(T))
	X = np.fft.fft(xT)
	Xm = X.conj()*X
	freq = np.fft.fftfreq(T.shape[-1])
	freqp = [i for i in freq if i >= 0]
	freqpm = [i/Ts for i in freqp]
	i0 = range(0, len(freqpm))
	Xm0 = Xm[:len(freqpm)].real
	X0 = X[:len(freqpm)]
	A0 = [i**0.5/len(freqpm) for i in Xm0]
	return {'p_num' : Pnum, 't_param' : [Tparams], 'signal' : 'D', 'ind' : Ind, 'time' : T, 'x' : xT, 'X': X, 'X2' : Xm, 'f_all' : freq, 'fp' : freqp, 'f' : freqpm, 'indp' : i0, 'X0' : X0, 'Xm0' : Xm0, 'A' : A0}	

	
def dtpr(A = A0, b = freqpm, p = 7, q = 8):
	N = len(A)
	B = [[v, i] for i, v in enumerate(A)]
	getkey = lambda item: item[0]
	Bs = sorted(B, key = getkey)
	tmp = Bs[p*int(N/q):]
	val = [i[0] for i in tmp]
	ind = [i[1] for i in tmp]
	m = np.mean(val)
	tmp1 = [i for i, v in enumerate(val) if v >= m]
	tmp2 = [ind[j] for j in tmp1 ]
	return [[b[i] for i in tmp2], [A[i] for i in tmp2]]
	
def pl(a = freqpm, b = A0, n = Pnum, col = 'blue'):
	if n == 0:
		n = len(a)
	return plt.plot(a[:n], b[:n], c = col)

def sh():
	plt.show()

def hlp(a = A0, b = freqpm):
	N = len(a)
	tmp1 = a[:3*int(N/4)]
#	m = np.mean(a)
	m = np.mean(tmp1)
	tmp = [ [b[i], v] for i, v in enumerate(a) if v > m ]
	return np.array(tmp).T
	
def plp(data, colr = 'red', size = 50, mrkr = 'v'):
	return plt.scatter(data[0], data[1], s = size, c = colr, marker = mrkr) 
	
def pls(a = T, b = x, Tn = Pnum):
	return plp.plot(a[:Tn], b[:Tn])
	
"""
s = "10*np.sin(10*2*pi*t) + 8*np.sin(5*2*pi*t) + 15 + noise(normal, 0.0, 1.0)"
s0 = "10*np.sin(10*2*pi*t) + 8*np.sin(5*2*pi*t) + 15"
tp = [0.0, 5.0, 0.001]
pn = 250
d = sigspec(s, tp)

A0 = d['A']
freqpm = d['f']

picks = hlp(A0, freqpm)


plt.grid(True)
plt.figure(1)
P1 = pl(freqpm, A0, pn)
plt.figure(1)
P2 = plp(picks)
"""

file = open('data/Of.dump', 'rb')
Of = pickle.load(file)
file.close()

dt = 10*60
Tb = 0.0
N = len(Of)
Te = N*dt
Ts = dt
tp = [0.0, N*dt, dt]

dd = sigspecd(Of, tp)

f = dd['f']
A = dd['A']
T = dd['time']
xT = dd['x']
X = dd['X0']
Ph = [phase(i) for i in X]

picks = dtpr(A, f)


"""

plt.figure(1)
plt.grid(True)
e = (max(picks[0]) + min(picks[0]))/2.0
e = [-e, e]
plt.xlim(e)
ax1 = plt.subplot(111)
plp(picks, 'blue')


plt.figure(2)
plt.grid(True)
e = -np.std(f)
e = [e, f[-1]]
plt.xlim(e)
ax2 = plt.subplot(111)
pl(f, A, len(f))


plt.figure(3)
plt.grid(True)
e = -np.std(f)
e = [e, f[int(len(f)/2)]]
plt.xlim(e)
ax31 = plt.subplot(211)
pl(f, A, int(len(f)/2))
ax32 = plt.subplot(212)
e = -np.std(f)
e = [e, f[int(len(f)/4)]]
plt.xlim(e)
plt.grid(True)
pl(f, A, int(len(f)/4))


plt.figure(4)
plt.grid(True)
e = -f[int(len(f)/8)]
e = [e, -e]
plt.xlim(e)
e = [min(A[:int(len(f)/8)]), max(A[:int(len(f)/8)])]
plt.ylim(e)
ax4 = plt.subplot(111)
pl(f, A, int(len(f)/8))



plt.figure(5)
plt.grid(True)
e = -2.5e-5
tmp = [ i for i, v in enumerate(f) if v <= -e ]
pnum = tmp[-1]
e = [e/3.0, -e]
plt.xlim(e)
e = [min(A), max(A)]
plt.ylim(e)
ax5 = plt.subplot(111)
pl(f, A, pnum)

"""



plt.figure(6)
plt.grid(True)
e = [Tb, Te]
plt.xlim(e)
e = [min(xT), max(xT)]
plt.ylim(e)
ax6 = plt.subplot(111)
plt.plot(T, xT, c = 'blue')



v1 = 1.15705e-5
A1 = 0.027002

v2 = 8.23253e-7
A2 = 0.0221438

v0 = 0.0
A0 = 0.0513833

v3 = 1.00974e-5
A3 = 0.0202687

v4 = 1.07516e-5
A4 = 0.0179106

v5 = 1.25943e-5
A5 = 0.0148288


yTi = []
Ai = [A0, A1, A2, A3, A4, A5]
vi = [v0, v1, v2, v3, v4, v5]
wi = [i*2.0*pi for i in vi]
ind = []
epsilon = np.std(vi)/10.0
for i in vi:
	if i == 0.0:
		continue
	for j, v in enumerate(f):
		if abs(v - i) <= epsilon:
			ind.append([i, j])
			break

tmp = [ i[1] for i in ind ]
tmpr = [ X.real[i] for i in tmp ]
tmpi = [ X.imag[i] for i in tmp ]
tmpp = [ Ph[i] for i in tmp ]

Phi = [ 0.0 for i in vi if i != 0.0 ]
Phi = tmpp
[Ph1, Ph2, Ph3, Ph4, Ph5] = tmpp

for i, v in enumerate(Ai):
	if vi[i] == 0.0:
		yTi.append(v)
	else:
		yTi.append(v*np.sin(vi[i]*2*pi*T + Phi[i - 1]))
yT = sum(yTi)


yT0 = np.array([ A0 for i in T ])
yT1 = A1*np.sin(v1*2*pi*T + Ph1)
yT2 = A2*np.sin(v2*2*pi*T + Ph2)
yT3 = A3*np.sin(v3*2*pi*T + Ph3)
yT4 = A4*np.sin(v4*2*pi*T + Ph4)
yT5 = A1*np.sin(v5*2*pi*T + Ph5)
yTi = [yT0, yT1, yT2, yT3, yT4, yT5]

#yT = A1*np.sin(v1*2*pi*T) + A2*np.sin(v2*2*pi*T) + yT0
yT = yT0 + yT1 + yT2 + yT3 + yT4 + yT5


plt.grid(True)
plt.plot(T, yT, c = 'green')

colors = [ 'red', 'green', 'blue', 'magenta', 'yellow', 'cyan' ]
for i, v in enumerate(yTi):
	#plt.grid(True)
	#plt.plot(T, v, c = colors[i])
	pass





plt.figure(7)
e = -1.5e-5
tmp = [ i for i, v in enumerate(f) if v <= -e ]
pnum = tmp[-1]
e = [e/3.0, -e]
ax7 = plt.subplot(111)
plt.xlim(e)
plt.grid(True)
pl(f, Ph, pnum, 'magenta')

"""
plt.figure(7)
e = -1.5e-5
tmp = [ i for i, v in enumerate(f) if v <= -e ]
pnum = tmp[-1]
e = [e/3.0, -e]
ax71 = plt.subplot(211)
plt.xlim(e)
plt.grid(True)
pl(f, X.real, pnum, 'blue')
ax72 = plt.subplot(212)
plt.xlim(e)
plt.grid(True)
pl(f, X.imag, pnum, 'red')


plt.figure(8)
plt.grid(True)
e = -2.5e-5
tmp = [ i for i, v in enumerate(f) if v <= -e ]
pnum = tmp[-1]
e = [e/3.0, -e]
plt.xlim(e)
e = [min(A), max(A)]
ax8 = plt.subplot(111)
picks = dtpr(Ph, f)
plp(picks, 'red')

"""