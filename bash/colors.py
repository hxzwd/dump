#!/usr/bin/ipython

import sys
import os
from termcolor import colored

CurrentColor = ""

def SetColor(Color):
	CurrentColor = Color

def Print(String, Color = ""):
	if Color == "":
		if CurrentColor != ""
			print colored(String, CurrentColor)
		else:
			print String
	else:
		print colored(String, Color)



# import sys
# import os
# import curses

# __StandardScreen__ = None

# def ColorsInit():
# 	StandardScreen = curses.initscr()
# #	curses.noecho()
# 	StandardScreen.keypad(True)
# 	__StandardScreen__ = StandardScreen
# 	return StandardScreen

# def ColorsClear(CurrentScreen = None):
# 	Screen = None
# 	if CurrentScreen == None:
# 		Screen = __StandardScreen__
# 	else:
# 		Screen = CurrenScreen
# 	curses.nocbreak()
# 	Screen.keypad(False)
# 	curses.echo()

# def ColorsClose():
# 	curses.endwin()



# import sys

# OldStdout = sys.__stdout__

# Colors = {
# 	"RED" : "\033[1;31m", 
# 	"BLUE" : "\033[1;34m",
# 	"CYAN" : "\033[1;36m",
# 	"GREEN" : "\033[0;32m",
# 	"RESET" : "\033[0;0m",
# 	"BOLD" : "\033[;1m",
# 	"REVERSE" : "\033[;7m"
# }


# A = lambda x: '"' + x + '"'
# B = lambda x: A(x) + ", "
# C = lambda x, y: x != y[-1]
# tmp = Colors.keys()
# tmp = map(lambda x: B(x) if C(x, tmp) else A(x), tmp)
# tmp = "".join(color for color in tmp)

# __doc__ = '\nColors.py\nFunctions:\n' +\
# '1.\tSetColor(Color)\n2.\tReset()\n' +\
# '3.\tPrintDoc()\n' +\
# 'type(Color) is string\n' +\
# 'Color from [' + tmp + ']\n'

# A = None
# B = None
# C = None
# tmp = None

# def SetColor(Color):
# 	sys.stdout.write(Colors[Color])

# def Reset():
# #	sys.stdout.write(RESET)
# #	sys.stdout = sys.__stdout__
# #	sys.stdout = OldStdout
# 	sys.stdout.flush()

# def PrintDoc():
# 	print __doc__
