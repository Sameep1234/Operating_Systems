#!/usr/bin/env bash
# AU1940049 Sameep Vani

# Read directory name from user
read -p "Enter the directory name: " DIR
cd $DIR # Change to the specified directory

fileName="$(ls -lR | awk '{print $9}')" # Recursively store filename into the variable
fileSize="$(ls -lR --block-size=KB | awk '{print $5}')" # Recursively store filename into the variable and size should be in KB
month="$(ls -lR | awk '{print $6}')" # Recursively store month into the variable
date="$(ls -lR | awk '{print $7}')" # Recursively store dates into the variable
access="$(ls -lR | awk '{print $1}')" # Recursively store access into the variable
user="$(ls -lR | awk '{print $3}')"  # Recursively store user into the variable

paste <(printf %s "$fileName") <(printf %s "$fileSize") <(printf %s "$month") <(printf %s "$date") <(printf %s "$access") <(printf %s "$user\n")
# paste=Merges lines of files
# printf=prints on the terminal
# %s=specify that the variables are strings