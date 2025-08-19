#!/bin/bash

. color.sh

if [ $# == 4 ]; then
    FLAG=1
    if [[ $1 == [1-6] && $2 == [1-6] && $3 == [1-6] && $4 == [1-6] ]]; then
    color_code_1="${color_nums[$1]}"
    color_code_2="${color_nums[$2]}"
    color_code_3="${color_nums[$3]}"
    color_code_4="${color_nums[$4]}"

    a="${colors_background[$color_code_1]}"
    b="${colors_font[$color_code_2]}"
    c="${colors_background[$color_code_3]}"
    d="${colors_font[$color_code_4]}"
    FLAG=0
    fi
fi

echo ""
    echo -e "${a}${b}HOSTNAME =${reset}${c}${d} $(hostname)${reset}"
    echo -e "${a}${b}TIMEZONE =${reset}${c}${d} $(cat /etc/timezone) $(date +%z)${reset}"
    echo -e "${a}${b}USER =${reset}${c}${d} $(whoami)${reset}"
    echo -e "${a}${b}OS =${reset}${c}${d} $(cat /etc/issue | awk '{print $1 $2}')${reset}"
    echo -e "${a}${b}DATE =${reset}${c}${d} $(date)${reset}"
    echo -e "${a}${b}UPTIME =${reset}${c}${d} $(uptime -p)${reset}"
    echo -e "${a}${b}UPTIME_SEC =${reset}${c}${d} $(cat /proc/uptime | awk '{print $1}')${reset}"
    echo -e "${a}${b}IP =${reset}${c}${d} $(hostname -I)${reset}"
    echo -e "${a}${b}MASK =${reset}${c}${d} $(ifconfig | grep -A 1 "wlp3s0" | tail -1 | awk '{print $4}')${reset}"
    echo -e "${a}${b}GATEWAY =${reset}${c}${d} $(ip r | awk '/default/{print$3}')${reset}"
    echo -e "${a}${b}RAM_TOTAL =${reset}${c}${d} $(free -m | awk '/Mem:/ {printf "%.3f GB\n", $2/1024}')${reset}"
    echo -e "${a}${b}RAM_USED =${reset}${c}${d} $(free -m | awk '/Mem:/ {printf "%.3f GB\n", $3/1024}')${reset}"
    echo -e "${a}${b}RAM_FREE =${reset}${c}${d} $(free -m | awk '/Mem:/ {printf "%.3f GB\n", $4/1024}')${reset}"
    echo -e "${a}${b}SPACE_ROOT =${reset}${c}${d} $(df -m / | awk 'NR==2 {printf "%.2f MB\n", $2}')${reset}"
    echo -e "${a}${b}SPACE_ROOT_USED =${reset}${c}${d} $(df -m / | awk 'NR==2 {printf "%.2f MB\n", $3}')${reset}"
    echo -e "${a}${b}SPACE_ROOT_FREE =${reset}${c}${d} $(df -m / | awk 'NR==2 {printf "%.2f MB\n", $4}')${reset}"

echo ""

if [[ $FLAG -eq 1 || $# != 4 ]]; then
    echo "Column 1 background = default (black)"
    echo "Column 1 font color = default (white)"
    echo "Column 2 background = default (black)"
    echo "Column 2 font color = default (white)"
else
    echo "Column 1 background = $1 ($color_code_1)"
    echo "Column 1 font color = $2 ($color_code_2)"
    echo "Column 2 background = $3 ($color_code_3)"
    echo "Column 2 font color = $4 ($color_code_4)"
fi   