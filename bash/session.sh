#!/bin/bash

#Paths
DEFAULT_DIR="/home/hjk/session"
OLD_DIR="$(pwd)"
#Flags
FLAG_AUTORUN="FALSE"
FLAG_DIR="FALSE"
FLAG_CLEAR="TRUE"

#Check directory

if [ "$OLD_DIR" != "$DEFAULT_DIR" ]
then
	cd $DEFAULT_DIR
	FLAG_DIR="TRUE"
else
	FLAG_DIR="FALSE"
fi

#Keyboard

setxkbmap -layout us,ru -option grp:alt_shift_toggle

#Mouse

xset m 0


#Config

xrdb /home/hjk/.Xresources
xrdb -merge /home/hjk/.uxterm_settings

#Autorun

if  [ "$FLAG_AUTORUN" == "TRUE" ]
then
	echo AUTORUN enabled
	./autorun.py
else
	echo AUTORUN disabled
fi


#Cleanup

if [ "$FLAG_DIR" == "TRUE" ]
then
	cd $OLD_DIR
	FLAG_DIR="FALSE"
else
	FLAG_DIR="FALSE"
fi

if [ "$FLAG_CLEAR" == "TRUE" ]
then
	clear
	FLAG_CLEAR="FALSE"
else
	FLAG_CLEAR="FALSE"
fi
