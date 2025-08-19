#!/bin/bash

if [ $# != 1 ]; then
    echo "Error, must be only 1 parameter" >&2
elif [ -d "$1" ]; then
    if ! [ -x out.sh ]; then
        chmod +x out.sh
    fi
    ./out.sh $1
else
    echo "No such directory" >&2
fi