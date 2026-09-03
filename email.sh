#!/bin/bash
printf "Enter an Email ID to validate: "
read email

if echo "$email" | grep -qE '^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$'; then
    echo "Result: Valid Email ID"
else
    echo "Result: Invalid Email ID"
fi