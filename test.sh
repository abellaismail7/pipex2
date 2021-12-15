#!/bin/bash

shtest="< $1 "
pipetest="./pipex $1"

i=0;
for cmd in "$@" 
do
	if [[ $i -ne 0 ]]
	then
		shtest+="$cmd "
		pipetest+=" '$cmd'"
		if [[ $i -ne $(($# - 1)) ]]
		then
			shtest+="| "
		fi
	fi
    i=$((i + 1));
done


echo ">>> $shtest > realout"
bash -c "$shtest > realout"; tput setaf 2; echo " ($?)"; tput sgr0;

echo ">>> $pipetest urout"
bash -c "$pipetest urout"; tput setaf 2; echo " ($?)"; tput sgr0;

diff realout urout

echo ">>>"
cat urout
