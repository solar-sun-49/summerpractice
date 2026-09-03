#!/bin/bash
read -p "Enter a number to reverse: " number

reversed=$(echo "$number" | awk '{ 
    for(i=length; i!=0; i--) 
        printf "%s", substr($0, i, 1) 
    print "" 
}')

echo "Reversed number: $reversed"