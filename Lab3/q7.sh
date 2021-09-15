#!/usr/bin/env bash
# AU1940049 Sameep Vani

# Read the neccessary inputs
read -p "Mention the path of specific directory: " DIR
read -p "Mention the newer date: (mm/dd/yy) " newDate
read -p "Mention the older date: (mm/dd/yy) " oldDate

# Change directory to the read input
cd $DIR

# List all files newer than a specified date
find . -type f -newermt "$newDate 0:00:00"

# List all files older than a specified date
find . -type f -not -newermt "$olderDate 0:00:00"