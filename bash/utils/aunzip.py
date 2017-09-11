#!/usr/bin/ipython

import sys
import os
from zipfile import PyZipFile
from termcolor import colored

DebugMode = True

CurrentPath = os.getcwd()
FilesList = os.listdir(CurrentPath)
ZipFilesList = [file for file in FilesList if '.zip' in file]

if DebugMode:
	print "Current path ", CurrentPath
	print "Files in ", CurrentPath, ":\n"
	for file in FilesList:
		print (file, colored(file, "red"))[file in ZipFilesList]
	print ""

if len(sys.argv) < 2:
	sys.exit()

Tmp = []
Tmp = [file for file in sys.argv[1:] if file in ZipFilesList]
Names = [file[:file.find(".")] for file in Tmp]
for index, zip_file in enumerate(Tmp):
	if DebugMode:
		print colored(zip_file, "green")
	if Names[index] not in FilesList:
		os.mkdir(Names[index])
	os.system("unzip " + zip_file + " -d " + Names[index])
	
		
