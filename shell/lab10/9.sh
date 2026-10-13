#!/bin/bash

for subdir in "$1"/*/; do
    # -perm +111 checks if ANY execute bit (user, group, or other) is set
    count=$(find "$subdir" -maxdepth 1 -type f -perm +111 | wc -l)
    
    # Optional: removes extra whitespace macOS 'wc -l' sometimes outputs
    count=$(echo $count | tr -d ' ') 
    
    echo "$subdir: $count"
done