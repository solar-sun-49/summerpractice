#!/bin/bash
read -p "Enter directory path (leave empty for current directory): " dir
dir=${dir:-.}

file_count=$(ls -l "$dir" | grep "^-" | wc -l)

echo "Number of files in '$dir': $file_count"