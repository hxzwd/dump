#!/usr/bin/python3.4

import os
import sys

TutorDir = "/home/hjk/webdata/scripts"
CurrenDir = ""

if "--debug" in sys.argv:
	print("Scripts script")

CurrentDir = os.getcwd()

if CurrentDir != TutorDir:
	os.chdir(TutorDir)

TutorFiles = os.listdir(TutorDir)
Tutors = [ tutor.split(".")[0] for tutor in TutorFiles ]

if "--debug" in sys.argv:
	print("\nAll scripts:")
	for tutor in Tutors:
		print(tutor)


if "--show" in sys.argv or "-s" in sys.argv:
	for index, tutor in enumerate(Tutors):
		if tutor in sys.argv:
			File = open(TutorFiles[index], "r")
			TutorData = File.read()
			File.close()
			print("\nScript " + tutor + ":")
			print(TutorData)
else:
	for index, tutor in enumerate(Tutors):
		if tutor in sys.argv:
			Command = TutorDir + "/./" + TutorFiles[index]
			tmp = [ i.split(":") for i in sys.argv if ":" in i]
			if "--arg" in [i[0] for i in tmp]:
				tmp2 = "--arg"
			else:
				if "-a" in [i[0] for i in tmp]:
					tmp2 = "-a"
				else:
					tmp2 = ""
			if tmp2 != "":
				tmp3= [i[1] for i in tmp][[i[0] for i in tmp].index(tmp2)]
				if tmp3 != "":
					tmp3.replace('"', '')
					Command = Command + " " + tmp3
			if "--debug" in sys.argv:
				print("Tutor: ", tutor)
				print("Index: ", index)
				print("Command: ", Command)
			os.system(Command)

