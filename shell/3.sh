#!/bin/bash
current_hour=$(date +%H)

if [ "$current_hour" -lt 12 ]; then
    echo "Good Morning!"
elif [ "$current_hour" -lt 17 ]; then
    echo "Good Afternoon!"
else
    echo "Good Evening!"
fi