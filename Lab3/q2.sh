#!/usr/bin/env bash
# AU1940049 Sameep Vani

read -p 'directory 1: ' directory1 # Read first folder name from user
read -p 'directory 2: ' directory2 # Read second folder name from user

if [[ ! -d "merged_q2" ]]; # Check if merged_q2 folder is there
then
    mkdir merged_q2 # If not, create it
fi

if [[ -d $directory1 ]] && [[ -d $directory2 ]]; # Check if user input is valid
then
    # If valid, then merge the files
    cp -r $directory1/* merged_q2
    cp -r $directory2/* merged_q2
else
    # If not valid, then print error msg
    echo "Directory not found!"
fi