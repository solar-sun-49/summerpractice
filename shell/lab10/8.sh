#!/bin/bash

read -p "Enter the word to search for: " word
grep -l "$word" *