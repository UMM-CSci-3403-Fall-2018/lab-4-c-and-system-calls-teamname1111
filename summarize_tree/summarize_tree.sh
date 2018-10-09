#!/bin/bash
#cd into the desired directory
cd $1
#count all the directories in all the directories in the directory
num_dirs=$(find . -type d | wc -l)
#count all the files in all the directories in the directory
num_regular=$(find . -type f | wc -l)
#output the result
echo "There were $num_dirs directories."
echo "There were $num_regular regular files."
