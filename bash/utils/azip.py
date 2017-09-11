#!/usr/bin/ipython

import os
import sys
from termcolor import colored

DebugMode = True

if len(sys.argv) < 3:
	sys.exit()

ArchiveName = sys.argv[1]
TargetName = sys.argv[2:]

Target = "".join(target + " " for target in TargetName)

if DebugMode:
	print ""
	print colored("Archive name: ", "red"), ArchiveName
	print colored("Target name: ", "red"), TargetName
	print ""

FilesList = os.listdir(os.getcwd())

for target in TargetName:
	if target not in FilesList:
		sys.exit()

os.system("zip " + ArchiveName + " -r " + Target)
