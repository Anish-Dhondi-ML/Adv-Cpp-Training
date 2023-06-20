#!/bin/bash

# Prompt the user for their name
echo "What is your name?"
read name

# Greet the user
echo "Hello, $name!"

# Check if the user is of legal drinking age
echo "How old are you?"
read age

if [ "$age" -ge 21 ]; then
    echo "You are of legal drinking age. Cheers!"
else
    echo "Sorry, you are not of legal drinking age."
fi

