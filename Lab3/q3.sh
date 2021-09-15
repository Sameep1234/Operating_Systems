#!/usr/bin/env bash
# AU1940049 Sameep Vani

read -p 'value of X: ' X # Read the value of number of seconds from user
read -p 'value of M: ' M # Read the value of frequency from user
for ((i=1;i<=M;i++)); do 
    gcc ./q3.c && ./a.out; sleep $X; done