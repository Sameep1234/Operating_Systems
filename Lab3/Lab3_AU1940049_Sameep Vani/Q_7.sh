#!/usr/bin/env bash
# AU1940049 Sameep Vani

# Read the neccessary inputs
read -p "Mention the path of specific directory: " DIR
read -p "Mention the newer date: (mm/dd/yy) " newDate
read -p "Mention the older date: (mm/dd/yy) " oldDate

# Change directory to the read input
cd $DIR

# List all files newer than a specified date
echo "Files Newer than $newDate are"
find . -type f -newermt "$newDate 0:00:00"
# find = Search for files in directory hierarchy
# . = Starting point of the search. By default it is '.' implying current active directory
# -type = Represents type of file to be searched.
# f = Stands for regular files
# -newerbt = Filter for finding files that are "newer" (mt means modification time) than the specified date.

# List all files older than a specified date
echo # Just some extra spacing
echo "Files older than $oldDate are"
find . -type f -not -newermt "$oldDate 0:00:00"
# -not = Essentially gets older than specified date.