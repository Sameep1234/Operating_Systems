#!/usr/bin/env bash
# AU1940049 Sameep Vani

# Read directory name from user
read -p "Enter the directory name: " DIR
cd $DIR # Change to the specified directory

# ls -lR = Shows list of files and directories in log format and recusively checks the sub directories
# awk = Scans patterns and text
# {print $9} = Get me the 9th column of the command
# '|' = Pipelining operator
# Overall, I get the names of all the files stored in fileNames variable.
fileName="$(ls -alR | awk '{print $9}')" # Recursively store filename into the variable
fileSize="$(ls -alR --block-size=KB | awk '{print $5}')" # Recursively store fileSize into the variable and size should be in KB
month="$(ls -alR | awk '{print $6}')" # Recursively store month into the variable
date="$(ls -alR | awk '{print $7}')" # Recursively store dates into the variable
access="$(ls -alR | awk '{print $1}')" # Recursively store access into the variable
user="$(ls -alR | awk '{print $3}')"  # Recursively store user into the variable

paste <(printf %s "$fileName") <(printf %s "$fileSize") <(printf %s "$month") <(printf %s "$date") <(printf %s "$access") <(printf %s "$user\n")
# paste=Merges lines of files
# printf=prints on the terminal
# %s=specify that the variables are strings

# Display total number of files in specified directory
# find -type f = Find all "files"
# wc -l = Counting the number of these files
echo # Just for extra spacing
echo "Number of Files"
find -type f | wc -l

# Size of the directory
echo # Just for extra spacing
echo "Size of the directory"
du -sh
# du = Disk usage
# Since nothing is specified, du will automatically take the current directory
# sh = summarize in human readable form