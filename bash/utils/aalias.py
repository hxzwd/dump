#!/usr/bin/ipython
import os
import sys

def main(Alias):
	if Alias == "":
		return []
	else:
		bashrcPath = "/home/hjk/.bashrc"
		File = open(bashrcPath, "r")
		Lines = File.readlines()
		File.close()
		Position = Lines.index("#Insert place\n")
		PartOne = Lines[:Position + 1]
		PartTwo = Lines[Position + 1:]
		Lines = PartOne + [Alias + "\n"] + PartTwo
		Data = "".join([line for line in Lines])
		os.system("rm /home/hjk/.bashrc")	
		File = open(bashrcPath, "w+")
		File.write(Data)
		File.close()
		return Lines

def ShowHelpMessage():
	HelpMessage = "\nOptions:\n" +\
	"help:<show|true> - Show help message\n" +\
	'a:"<aliase>" or alias:"<aliase>" - Set new aliase\n' +\
	'-i - Run in interactive mode\n'
	print HelpMessage


Args = [ arg.split(":") for arg in sys.argv if ":" in arg]
Params = [ arg[0] for arg in Args ]
Values = [ arg[1] for arg in Args ]
Alias = ""

for index, value in enumerate(Params):
	if value == "alias" or value == "a":
		Alias = Values[index]
	if ( value == "help" or value == "h" ) and ( Values[index] == "show" or Values[index] == "true" ):
		ShowHelpMessage()

#print Args
#rint Alias

Lines = main(Alias)
#os.system("source ~/.bashrc")