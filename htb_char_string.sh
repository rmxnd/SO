#!/bin/bash

#conta il numero di caratteri (in byte) in una variabile
# echo $var | wc -c

# variable to encode
var="nef892na9s1p9asn2aJs71nIsm"

for counter in {1..40}
do
	var=$(echo $var | base64)

# prints the number of characters of the 35th generated value of the variable "var"
	if [ $counter -eq "35" ]
	then
		output=$(echo $var | wc -c)
		echo "$output"
	fi
done
