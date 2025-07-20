#!/bin/bash

# Throw error if no command-line argument is supplied
if [[ -z $1 ]]; then
	echo "Error! Usage: ./run_test.sh <TEST_NUM>"
	exit 1
fi

# Throw error if command-line argument is not a number between 1 and 6
if ! [[ $1 =~ ^[0-9]+$ ]]; then
	echo "Error! Argument must be a number"
	exit 1
fi

# Throw error if command-line argument is not in [1, 6]
if (( $1 > 6 || $1 < 1 )); then
	echo "Error! Argument must be in the range of [1, 6]"
	exit 1
fi

gcc src/main.c -o src/avl
./src/avl $1
python3 data/plot_csv.py $1
