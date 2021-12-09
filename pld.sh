#!/bin/bash

file=$(ls ~/Downloads/ -t |head -n 1)
cp ~/Downloads/$file .
echo $file just arrived ...
