#!/bin/bash

# Read the main string
text="Lil cabin spring house (Temp/Hum): 9.30c - 98.00"

# Split the string by space
readarray -d " " -t strarr <<< "$text"

# Print each value of the array by 
# using loop
for (( n=0; n < ${#strarr[*]}; n++))
do
 echo "${strarr[n]}"
done
echo "${strarr[5]}"
echo "${strarr[7]}"
