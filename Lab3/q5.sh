#!/usr/bin/env bash
# AU1940049 Sameep Vani

echo "Select an operation"
echo # Just extra spacing

# List the menu for the user
echo "a. Display Current Directory"
echo "b. List Directory"
echo "c. Make a new directory"
echo "d. Change Directory"
echo "e. Copy file"
echo "f. Rename file"
echo "g. Delete file"
echo "h. Edit content of file"
echo "i. Exit"

option=j # Declare a var with default option "j" so that it enters while loop
while [[ $option != "i" ]] # While loop untill "i" is pressed
do
    read -p "Option: " option # Read option from the user

    if [[ $option == 'a' ]]; 
    then
        pwd
    elif [[ $option == 'b' ]];
    then
        ls
    elif [[ $option == 'c' ]];
    then
        directoryName=default
        read -p "Directory Name: " directoryName
        mkdir $directoryName
        echo "Created new directory!"
    elif [[ $option == 'd' ]];
    then
        destination=temp1
        read -p "Where do you want to go? " destination
        cd $destination
        echo "Changed Directory to"
        pwd # Just to show the user that directory has been changed.
    elif [[ $option == 'e' ]];
    then
        source=default
        destination=default
        read -p "Which file do you want to copy? " source
        read -p "Where do you want to copy? " destination

        touch $source # Ensuring that there won't be any error.

        cp $source $destination
        echo "Copied!"
    elif [[ $option == 'f' ]];
    then
        source=default
        destination=default
        read -p "Which file do you want to rename? " source
        read -p "What do you want to name it as? " destination
        
        touch $source

        mv $source $destination
        echo "Renamed!"
    elif [[ $option == 'g' ]];
    then
        source=default
        read -p "Which file do you want to delete? " source

        touch $source
        
        rm -rf $source
        echo "File deleted Successfully!"
    elif [[ $option == 'h' ]];
    then
        source=default
        read -p "Which file do you want to edit? " source

        nano $source
    elif [[ $option == 'i' ]];
    then
        echo "Exited"
    else
        echo "Please select a valid option"
    fi
done