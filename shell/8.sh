#!/bin/bash
read -p "Enter source file name: " src
read -p "Enter destination file name: " dest

if [ ! -f "$src" ]; then
    echo "Source file does not exist!"
    exit 1
fi

awk '{print}' "$src" > "$dest"

echo "Contents successfully copied from $src to $dest."