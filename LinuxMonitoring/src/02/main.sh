#!/bin/bash

. ./out.sh
out
read -p "Do you want to save it in file? (Y/N) " answer
if [[ $answer = "y" || $answer = "Y" ]]; then
    out > $(date +%d_%m_%Y_%H_%M_%S).status
else 
	exit 1
fi