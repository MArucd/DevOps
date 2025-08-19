#!/bin/bash

reset='\033[0m'

declare -A color_nums=(
            [1]="white"
            [2]="red"
            [3]="green"
            [4]="blue"
            [5]="purple"
            [6]="black" )

declare -A colors_background=( 
            [white]="\033[97m"
            [red]="\033[91m"
            [green]="\033[92m"
            [blue]="\033[96m"
            [purple]="\033[95m"
            [black]="\033[30m" )

declare -A colors_font=( 
            [white]="\033[107m"
            [red]="\033[101m"
            [green]="\033[102m"
            [blue]="\033[106m"
            [purple]="\033[105m"
            [black]="\033[40m" )