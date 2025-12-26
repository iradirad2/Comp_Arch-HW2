#!/bin/bash

for i in {1..3}; do
    bash "example${i}_command" > ex${i}mine
    if cmp -s "example${i}_output" "ex${i}mine"; then 
	echo "example${i} is good"
    else
	echo "example${i} is not good" 
    fi
done
