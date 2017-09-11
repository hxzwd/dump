#!/usr/bin/ipython

import sys
sys.path.append('../')
import colors



def main():
	pass
	return "Exit from testscript.py\n"



colors.SetColor("RED")
print "TEST TEST TEST"
sys.stdout.write("STDOUT TEST TEST TEST\n")
colors.Reset()
print "PRINT RESET TEST"
sys.stdout.write("STDOUT RESET TEST\n")


Result = main()
print Result
