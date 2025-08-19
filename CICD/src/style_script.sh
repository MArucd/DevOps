#!/bin/bash

if [ ! -f "style_res.txt" ]; then
    echo "Error: style_res.txt file doesn't exist"
    echo "Run the code style check to generate the file"
    exit 1
fi

if [ -s "style_res.txt" ]; then
    exit 1
else
    echo "No style errors were found"
    echo "Code is clang-formatted"
fi