#!/usr/bin/bash

file=$1
echo $file
xterm -geometry '70x40-0+0' -e "cd $PWD && gcc -g -Wextra -Wall -Werror -std=c99 -pedantic $file && gdb a.out"
#gnome-terminal -- watch -n 3600 -d "cd $PWD && gcc -g -Wextra -Wall -Werror -std=c99 -pedantic $file && gdb a.out"

