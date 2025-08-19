#!/bin/bash

if [ ! -f "testass.txt" ]; then
    echo "Error: test_res.txt file doesn't exist"
    echo "Run make test to generate the file"
    exit 1
fi

if grep -c "\---" testass.txt; then
    echo "Error: tests failed"
    exit 1
else
    echo "No errors were found"
fi