#!/usr/bin/python2.7

import os
import sys
import datetime

ProgramList = {
	"CHROMIUM" : False,
	"CHROMIUM_INCOGNITO" : True,
	"XTERM" : False,
	"GNOME_TERMINAL" : False
}

ElfNames = {
	"CHROMIUM" : "chromium-browser",
	"CHROMIUM_INCOGNITO" : "chromium-browser --incognito",
	"XTERM" : "xterm",
	"GNOME_TERMINAL" : "gnome-terminal"
}

AUTORUN_LOG = True
CLEAR_SCREEN = False
DEFAULT_PATH = "/home/hjk/session"
DEFAULT_LOG_DIR = "log"
DEFAULT_LOG_FULL_PATH = DEFAULT_PATH + "/" + DEFAULT_LOG_DIR
AUTORUN_LOGFILE = "autorun.log"
LOGFILE_DESC = None
PREV_PATH = ""

AutorunFlags = {
	"FLAG_LOGGING" : AUTORUN_LOG,
	"FLAG_CLEAR_SCREEN" : CLEAR_SCREEN
}

Paths = {
	"DEFAULT" : DEFAULT_PATH,
	"LOGS" : DEFAULT_LOG_DIR,
	"LOGS_FULL_PATH" :DEFAULT_LOG_FULL_PATH,
	"PREV" : PREV_PATH
}

AutorunFiles = {
	"LOGFILE" : AUTORUN_LOGFILE,
	"LOGFILE_DESC" : LOGFILE_DESC,
	"LOGFILE_FULL_NAME" : DEFAULT_LOG_FULL_PATH + "/" + AUTORUN_LOGFILE
}

ParamsList = [
	"&",
	"log file"
]

def parse_args(args, fileName = ""):
	prev_path = os.getcwd()
	scriptFile = None
	if len(args) == 0:
		return
	else:
		os.chdir(DEFAULT_PATH)
		if fileName != "":
			if "./" in fileName:
				fileName = fileName.replace("./", "")
			scriptFile = open(fileName, "w+")
		for index, value in enumerate(args):
			if "--add=" in value:
				tmp = value.split("=")
				pass
	if scriptFile != None and fileName != "":
		scriptFile.close()			 
	os.chdir(prev_path)

def Log(message):
	LogFile = AutorunFiles["LOGFILE_DESC"]
	LogFile.write(str(datetime.datetime.now()) + ":" + message)

def sort_params(params = []):
	for index, value in enumerate(ParamsList):	
		if value in params:
			if value == "&":
				params.remove(value)
				params.append(value)
		else:
			continue
	return params

def exec_programm(elfName, params = []):
	cmd = elfName
	cmd_list = []
	programName = ElfNames.keys()[ElfNames.values().index(elfName)]
	message = programName + " runned as " + elfName	
	if len(params) == 0:
		os.system(cmd)
	else:
		params = sort_params(params)
		cmd_list = [cmd]
		for index, value in enumerate(params):
			if value == "&":
				cmd_list += [" ", value]
			if value == "log file":
				cmd_list += [" >> ", AutorunFiles["LOGFILE_FULL_NAME"]]
		message = programName + " runned as " + elfName + " with params: " + "".join(cmd_list[1:])
		cmd = "".join(cmd_list)
		os.system(cmd)
	if AutorunFlags["FLAG_LOGGING"]:
		Log(message)
	return message
 
def run_programms():
	Params = ["&"]
	if AutorunFlags["FLAG_LOGGING"]:
		Params.append("log file")
	for index, value in enumerate(ProgramList):
		if ProgramList[value]:
			message = exec_programm(ElfNames[value], Params)
			print message
def get_status():
	if AutorunFlags["FLAG_LOGGING"]:
		Log("SCRIPT STATUS: ")
	print "Programms:"
	if AutorunFlags["FLAG_LOGGING"]:
		Log("Programms:")
	for index, value in enumerate(ProgramList):
		print str(index) + ":" + value + " " + ("autorun disabled", "autorun enabled")[ProgramList[value]]
		if AutorunFlags["FLAG_LOGGING"]:
			Log(str(index) + ":" + value + " " + ("autorun disabled", "autorun enabled")[ProgramList[value]])
	print "Flags:"
	if AutorunFlags["FLAG_LOGGING"]:
		Log("Flags:")
	for value in AutorunFlags.keys():
		print "Flag " + value + " " + ("off", "on")[AutorunFlags[value]]
		if AutorunFlags["FLAG_LOGGING"]:
			Log("Flag " + value + " " + ("off", "on")[AutorunFlags[value]])
	print "Dirs and files:"
	if AutorunFlags["FLAG_LOGGING"]:
		Log("Dirs and files:")
	for value in AutorunFiles.keys():
		print "Param " + value + " set on " + str(AutorunFiles[value])
		if AutorunFlags["FLAG_LOGGING"]:
			Log("Param " + value + " set on " + str(AutorunFiles[value]))
	for value in Paths.keys():	
		print "Param " + value + " set on " + str(Paths[value])
		if AutorunFlags["FLAG_LOGGING"]:
			Log("Param " + value + " set on " + str(Paths[value]))


def print_hello_message(info = "No info"):
	hello_message = str(datetime.datetime.now()) +\
	"\nAutorun python script" +\
	"\nFile name: " + sys.argv.pop() +\
	"\nLocation: " + os.getcwd() +\
	"\nInfo: " + info + "\n"
	if AutorunFlags["FLAG_LOGGING"]:
		Log(hello_message)
	print hello_message

def setup_log_settings():
	PREV_PATH = os.getcwd()
	LogFile = None
	info = ""
	if DEFAULT_LOG_DIR not in os.listdir(DEFAULT_PATH):
		os.chdir(DEFAULT_PATH)
		os.mkdir(DEFAULT_LOG_DIR)
		LogFile = open(AUTORUN_LOGFILE, "w+")
		os.chdir(PREV_PATH)
	else:
		os.chdir(DEFAULT_PATH)
		os.chdir(DEFAULT_LOG_DIR)
		if AUTORUN_LOGFILE not in os.listdir(os.getcwd()):
			LogFile = open(AUTORUN_LOGFILE, "w+")
		else:
			LogFile = open(AUTORUN_LOGFILE, "w+")
		os.chdir(PREV_PATH)
	LOGFILE_DESC = LogFile
	AutorunFiles["LOGFILE_DESC"] = LogFile
	LogFile.write("\n\n")
	LogFile.write(str(datetime.datetime.now()))
	LogFile.write("\n")
	info = "Logging enabled; Destination is " + AUTORUN_LOGFILE
	return LogFile, info


def cleanup():
	if AutorunFlags["FLAG_CLEAR_SCREEN"]:
		os.system("clear")
		if AutorunFlags["FLAG_LOGGING"]:
			Log("Screen cleanup")
	if AUTORUN_LOG:
		if LOGFILE_DESC != None:
			Log("log file closed")
			LOGFILE_DESC.close()

def main():
	InfoMessage = "No information"
	if AUTORUN_LOG:
		LOGFILE_DESC, InfoMessage = setup_log_settings()	
	print_hello_message(InfoMessage)
	get_status()
	run_programms()
	cleanup()

print sys.argv, len(sys.argv)
main()
os.system("echo")
