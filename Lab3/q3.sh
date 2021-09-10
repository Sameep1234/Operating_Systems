#!/usr/bin/env bash
# AU1940049 Sameep Vani

read -p 'value of X: ' X
read -p 'value of M: ' M
for ((i=1;i<=M;i++)); do 
    gcc ./q3.c && ./a.out; sleep $X; done