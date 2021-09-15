#!/usr/bin/env bash
# AU1940049 Sameep Vani

# Print sorted list of users
echo "Below is the sorted list of all the users"
cut -d: -f1 /etc/passwd | sort
# cut = removes section from each line of files
# -d = Delimeter (which in this case is f1)
# /etc/passwd = contains essential information required during log in.
# | = pipelining operator
# sort = print in sorted order

# Count total number of users
echo # Just some extra spacing
echo "Total number of users are"
cut -d: -f1 /etc/passwd | wc -l
# wc = prints the newline, word and byte count for each file.
# -l = print only count of newline

# Search for any specific user and display no. of times the user logged in
echo # Just some extra spacing
username=default # Declare variable
read -p "Username: " username # Read the name of user as input
echo "Specific user entered $username and its count is"
last | grep -c "$username"
# last = Contains list of previous logged in users
# grep -c $username = search for a specific user only (grep command prints line that matched a pattern and -c counts that)

# Check if specific user is terminally active
echo # Just some extra spacing
username=default # Declare variable
read -p "Username: " username # Read name from terminal
echo "Specific user entered is $username and below is the result for its terminal activity"
ps -aux | awk '{print $1,$11}' | grep "bash" | cat >> checkTerminalActivity.txt
if grep -q "$username" checkTerminalActivity.txt
then
    echo "$username is terminally active"
else
    echo "$username is terminally inactive"
fi

# List of users without password
echo # Just some extra spacing
echo "List of users without password"
sudo getent shadow | grep -Po '^[^:]*(?=:.?:)'
# sudo = superuser do
# getent = gets entries from name service switch lib.
# shadow = gets name with no key/password
# -Po = perl regex and o represents match only those.