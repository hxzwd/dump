#!/usr/bin/python3.4

import os
import sys

TutorDir = "/home/hjk/tutors"
CurrenDir = ""

if "--debug" in sys.argv:
	print("Tutor script")

CurrentDir = os.getcwd()

if CurrentDir != TutorDir:
	os.chdir(TutorDir)

TutorFiles = os.listdir(TutorDir)
Tutors = [ tutor.split(".")[0] for tutor in TutorFiles ]

if "--debug" in sys.argv:
	print("\nAll tutors:")
	for tutor in Tutors:
		print(tutor)


for index, tutor in enumerate(Tutors):
	if tutor in sys.argv:
		File = open(TutorFiles[index], "r")
		TutorData = File.read()
		File.close()
		print("\nTutor " + tutor + ":")
		print(TutorData)
		

