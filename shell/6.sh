#!/bin/bash
read -p "Enter the path of the file/directory: " path

if [ -d "$path" ]; then
    echo "'$path' is a valid directory."
elif [ -e "$path" ]; then
    echo "'$path' exists, but it is a file, not a directory."
else
    echo "'$path' does not exist."
fi