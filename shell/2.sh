#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <number> <word>"
    exit 1
fi

n=$1
word=$2

awk -v n="$n" -v w="$word" 'BEGIN { for (i=1; i<=n; i++) print w }'