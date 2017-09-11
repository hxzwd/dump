#!/bin/bash


#Flags
FLAG_GUI_MODE="FALSE"
FLAG_NO_GUI_MODE="TRUE"

#Set up wmname
wmname LG3D


for arg in "$@"
do

	if [ "$arg" == "gui" ]
	then
		FLAG_GUI_MODE="TRUE"
	else
		if [ "$arg" == "nogui" ]
		then
			FLAG_NO_GUI_MODE="TRUE"
		else
			echo "Invalid argument:" $arg
		fi
	fi

done

if [ "$FLAG_GUI_MODE" == "TRUE" -a "$FLAG_NO_GUI_MODE" == "TRUE" ]
then
	echo "FLAG_GUI_MODE SET ON AND FLAG_NO_GUI_MODE SET ON"
	echo "CHOOSE ONE VARIANT"
	exit
fi

#Run matlab

if [ "$FLAG_GUI_MODE" == "TRUE" ]
then
	echo "Run in gui mode..."
	/home/hjk/qt_projects/MATLAB/bin/./matlab &
	exit
fi

if [ "$FLAG_NO_GUI_MODE" == "TRUE" ]
then
	echo "Run in nodesktop mode..."
	/home/hjk/qt_projects/MATLAB/bin/./matlab -nodesktop
	exit
fi
