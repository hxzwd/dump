#!/usr/bin/ipython

import os
import sys

def main(FileName = ""):
	if FileName == "":
		return ""
	Cmd = "subl"
	Cmd = Cmd + " " + FileName
	Cmd += " >> /home/hjk/session/dump/logs/subl.log"
	Cmd += " 2> /home/hjk/session/dump/logs/subl.log"
	Cmd += " &"
	os.system(Cmd)
	return Cmd



FileName = ""

if len(sys.argv) >= 2:
	FileName = sys.argv[-1]
else:
	pass

#print FileName

Cmd = main(FileName) 
print Cmd
