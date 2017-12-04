#!/bin/bash

SESN="mysession"
WINN="win0"
FLNEW="TRUE"

FLRUN=$(ps -la | grep -e "tmux" -o)
FLKILL="FALSE"

for arg in $@
do
	cmd=$(echo $arg | grep -e "-[a-zA-Z][\=]*" -o)
	val=$(echo $arg | grep -e "\=.*$" -o)
	val=${val:1:${#val}}
	if [[ "$cmd" == "-n" ]]
	then
		FLNEW="TRUE"
#		if [[ "$val" == "no" ]]
#		then
#			FLNEW="FALSE"
#		fi
	fi
	if [[ "$cmd" == "-i=" ]]
	then
		SESN="$val"
	fi
	if [[ "$cmd" == "-a" ]]
	then
		FLNEW="FALSE"
#		if [[ "$val" == "yes" ]]
#		then
#			FLNEW="FALSE"
#		fi
	fi
	if [[ "$cmd" == "-w=" ]]
	then
		WINN="$val"
	fi
	if [[ "$cmd" == "-k" ]]
	then
		FLKILL="TRUE"
	fi
done

#if [[ "$FLKILL" == "TRUE" ]]

if [[ "$FLRUN" != "" ]]
then
	if [[ "$FLKILL" == "FALSE" ]]
	then
		echo "TMUX ALREADY STARTED"
		exit
	else
		echo "KILL TMUX SERVER..."
		tmux kill-server
		exit
	fi
fi


if [[ "$FLNEW" == "TRUE" ]]
then
	echo "START NEW SESSION:	YES"
else
	echo "START NEW SESSION:	NO"
fi
echo "SESSION NAME:		$SESN"
echo "STARTUP WINDOW NAME: 	$WINN"


SL=$(tmux list-sessions | grep $SESN)
if [[ "$SL" != "" ]]
then
	if [[ "$FLNEW" == "TRUE" ]]
	then
		tmux kill-session -t $SESN
		tmux new -s $SESN -n $WINN
	else
		tmux attach-session -t $SESN
	fi
fi


tmux new -s $SESN -n $WINN
