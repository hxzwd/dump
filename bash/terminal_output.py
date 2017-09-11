#!/usr/bin/ipython

import os
import sys
import curses
import traceback




ParamsList = {
	"BOLD" : curses.A_BOLD,
	"UNDERLINE" : curses.A_UNDERLINE,
}

Keys = [["BOLD", "B", "b"],
	["UNDERLINE", "U", "u"]]

Colors = {
	"RED" : curses.COLOR_RED,
	"GREEN" : curses.COLOR_GREEN,
	"WHITE" : curses.COLOR_WHITE,
	"BLUE" : curses.COLOR_BLUE,
	"BLACK" : curses.COLOR_BLACK,
	"YELLOW" : curses.COLOR_YELLOW,
	"CYAN" : curses.COLOR_CYAN,
	"MAGENTA" : curses.COLOR_MAGENTA,
	"DEFAULT" : -1
}

NumOfThemes = 24
ThemeList = []
ExceptionInfo = ""

def Test(StandardScreen):
	StandardScreen.border(0)
	StandardScreen.addstr(12, 25, "SKJDFKLSJDFLKJSDLKFJ")

def PrintString(StandardScreen, String):
	pass

def Print(StandardScreen, String):
	StandardScreen.addstr(String)

def PrintInPoint(StandardScreen, String, Position = (0, 0)):
	StandardScreen.addstr(Position[0], Position[1], String)

def GetChar(StandardScreen):
	StandardScreen.getch()

def Pause(StandardScreen):
	StandardScreen.getch()

def Refresh(StandardScreen):
	StandardScreen.refresh()

def Close(StandardScreen):
	curses.endwin()

def Start():
	return curses.initscr()


def GetKey(key):
	for keys in Keys:
		if key in keys:
			return keys[0]
	return ""

def GetParams(Keys):
	return [ParamsList[GetKey(key)] for key in Keys]

def GetParam(key):
	return ParamsList[GetKey(key)]

def CheckParams(Params):
	CheckedParams = []
	for param in Params:
		if GetKey(param) != "" or type(param) == int:
			CheckedParams.append(param)
		else:
			continue
	return CheckedParams

def ThemeNumberGenerator(Amount):
	IndexList = range(1, Amount)
	for index in IndexList:
		yield index


def ColorsFunction():
	curses.start_color()
	curses.use_default_colors()
	return

CurrentScreen = Start()
ColorsFunction()
GetThemeIndex = ThemeNumberGenerator(NumOfThemes)

def GetStandardScreen():
	return CurrentScreen

def CPrint(String, Point = []):
	if Point == []:
		Print(CurrentScreen, String)
	else:
		PrintInPoint(CurrentScreen, String, Position = Point)

def PPrint(String, Params = [], Point = []):
	Params = CheckParams(Params)
	if Params == []:
		CPrint(String, Point)
	else:
		Screen = GetStandardScreen()
		Params.reverse()
		Param = Params.pop()
		Flag = True
		CPrint("PARAM:\t" + str(Param) + "\n")
		if type(Param) != int:
			FirstParam = GetParam(Param)
		else:
			for index, value in enumerate(ThemeList):
				if value[0] == Param:
					FirstParam = curses.color_pair(Param)
					Flag = True
					break
				else:
					Flag = False
					continue
		if Flag:
			if Point == []:
				Screen.addstr(String, FirstParam)
			else:
				Screen.addstr(Point[0], Point[1], String, FirstParam)
		else:
			CPrint(String, Point)

def InitTheme(TextColor, BackgroundColor, Generator):
	index = Generator.next()
	TextColorKey = TextColor
	BackgroundColorKey = BackgroundColor
	TextColor = Colors[TextColorKey]
	BackgroundColor = Colors[BackgroundColorKey]
	curses.init_pair(index, TextColor, BackgroundColor)
	ThemeList.append([index, (TextColor, BackgroundColor), (TextColorKey, BackgroundColorKey)])

def AddNewTheme(Colors, DefaultBackGround = True):
	TextColor = Colors[0]
	BackgroundColor = Colors[1]
	if DefaultBackGround:
		BackgroundColor = "DEFAULT"
	InitTheme(TextColor, BackgroundColor, GetThemeIndex)

def ThemesInfo():
	if ThemeList == []:
		return ""
	Result = "Theme list[%d]:\n" % len(ThemeList)
	for index, value in enumerate(ThemeList):
		Result += str(index) + ":\n" +\
		"\tIndex: " + str(value[0]) + "\n" +\
		"\tText color: " + value[2][0] + "\n" +\
		"\tBackground color: " + value[2][1] + "\n"
	return Result

def PrintThemesInfo():
	PPrint(ThemesInfo())

def GetObjectDir(Object, cols = 3):
	Methods = dir(Object)
	Row = ""
	Table = ""
	for index, value in enumerate(Methods):
		Row = Row + value + "\t"
		if ((index + 1) % cols == 0):
			Row = Row[:-1] + "\n"
			Table += Row
			Row = ""
		else:
			continue
	return Table

def PrintObjectDir(Object, cols = 3):
	CPrint(GetObjectDir(Object, cols))


G = lambda x: GetParam(x)
P = lambda x: CPrint(x)

Table = ""

try:
	
	curses.cbreak()
#	curses.nl()
	
	#Test(CurrentScreen)
	AddNewTheme(["RED", "BLACK"])
	PrintThemesInfo()
	CPrint("938492084902384902384290384\n")
	CPrint("SKJDFKLSJDFLKJSDLKFJ")
	PPrint("\n\n\t\tBOLD BOLD BOLD BOLD\n\n", ["b"])
	PPrint("\t\tUNDERLINED DSJFJSF\n\n", ["u"])
	PPrint("\t\tCOLORS TEST\n\n", [1])
	CPrint(str(dir(CurrentScreen)))
	CPrint(str(dir(CurrentScreen)))
	CPrint(str(dir(CurrentScreen)))
	CPrint("1\n")
	CPrint("2\n")
	CPrint("3\n")
	CPrint("4\n")
	CPrint("5\n")
	Table = GetObjectDir(CurrentScreen)
#	PrintObjectDir(CurrentScreen)
	Refresh(CurrentScreen)
	Pause(CurrentScreen)
	
	
	
	Close(CurrentScreen)
except Exception, Error:
	ExceptionInfo = sys.exc_info()[0]
		
	
	
	Close(CurrentScreen)
	print "Exception:\n", ExceptionInfo
	print dir(ExceptionInfo)
	print ExceptionInfo.__str__
	print str(Error)


