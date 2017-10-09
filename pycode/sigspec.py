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
	
def pl(a = freqpm, b = A0, n = Pnum):
	if n == 0:
		n = len(a)
	return plt.plot(a[:n], b[:n])

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
	
#s = "10*np.sin(10*2*pi*t) + 8*np.sin(5*2*pi*t) + 15 + noise(normal, 0.0, 1.0)"
#s0 = "10*np.sin(10*2*pi*t) + 8*np.sin(5*2*pi*t) + 15"

s = "10*np.sin(10*2*pi*t) + 8*np.sin(5*2*pi*t - pi/4.0) + 15"
tp = [0.0, 5.0, 0.001]
pn = 250
d = sigspec(s, tp)

A0 = d['A']
freqpm = d['f']
X = d['X0']
Ph = [phase(i) for i in X]

picks = hlp(A0, freqpm)


plt.grid(True)
plt.figure(1)
P1 = pl(freqpm, A0, pn)
plt.figure(1)
P2 = plp(picks)
plt.figure(2)
plt.grid(True)
P3 = pl(freqpm, Ph, pn)