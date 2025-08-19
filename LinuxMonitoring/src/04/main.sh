#!/bin/bash

if [ $# != 0 ]; then
    echo "Error, must be 0 arguments" >&2
else
    . con.sh
    if ! [ -x out.sh ]; then
        chmod +x out.sh
    fi
    ./out.sh $column1_background $column1_font_color $column2_background $column2_font_color
fi