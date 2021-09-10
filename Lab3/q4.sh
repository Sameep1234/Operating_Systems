#!/usr/bin/env bash
# AU1940049 Sameep Vani

# Printf will print it in specific format
# %n = Display file name
# %s = Display file size
# %z = Date and Time (Human readable format) of last status change
# %A = Access tokens (Human readable format)
# &U = Owner/User name
# \n = new line character
echo "Format below = File Name | Size | Date | Protection | Owner"
stat --printf='%n %s %z %A %U\n' **

# find -type f = Find all "files"
# wc -l = Counting the number of these files
echo # Just for extra spacing
echo "Number of Files"
find -type f | wc -l

# Size of the directory
echo # Just for extra spacing
echo "Size of the directory"
stat --printf='%s' . # "." represents current directory.