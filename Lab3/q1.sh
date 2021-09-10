#!/usr/bin/env bash
# AU1940049 Sameep Vani

if [ -d "/home/sameep/Downloads" ] # Check whether directory exists
then
    cd /home/sameep/Downloads # If exits then recursively show sub-directory
    ls -R
else
    echo "Directory Does not exist" # Print error msg if directory not found
fi