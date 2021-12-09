#!/bin/bash

file=$1
echo $file
gnome-terminal --geometry 70x40-0+0 -- watch --color -d "cd $PWD && gcc -fdiagnostics-color=always -Wextra -Wall -Werror -std=c99 -pedantic $file && ./a.out"

