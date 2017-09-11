import numpy as np

def nonlin(x, deriv = False):
	if(deriv == True):
		return -np.exp(-x)/((1 + np.exp(-x))*(1 + np.exp(-x)))
	return 1/(1 + np.exp(-x))

X = np.array([	[0, 0, 1],
		[0, 1, 1],
		[1, 0, 1],
		[1, 1, 1]	])

y = np.array([[0, 0, 1, 1]]).T

np.random.seed(1)

syn0 = 2*np.random.random((3, 1)) - 1

for iter in xrange(10000):
	
	l0 = X
	l1 = nonlin(np.dot(l0, syn0))
	
	l1_error = l1 - y
	l1_delta = l1_error * nonlin(l1, True)
	
	syn0 += np.dot(l0.T, l1_delta)
	

print "out after training"
print ["%0.4f" % i for i in l1]

