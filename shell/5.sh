#!/bin/bash
read -p "Enter a string: " str

rev_str=$(echo "$str" | awk '{ for(i=length;i>0;i--) printf "%s", substr($0,i,1); print "" }')

if [ "$str" == "$rev_str" ]; then
    echo "The string is a Palindrome."
else
    echo "The string is Not a Palindrome."
fi