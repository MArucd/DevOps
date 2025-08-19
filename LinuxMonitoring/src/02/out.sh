#!/bin/bash

function out {
    echo HOSTNAME = $(hostname)
    echo TIMEZONE = $(cat /etc/timezone) $(date +%z)
    echo USER = $(whoami)
    echo OS = $(cat /etc/issue | awk '{print $1 $2}')
    echo DATE = $(date)
    echo UPTIME = $(uptime -p)
    echo UPTIME_SEC = $(cat /proc/uptime | awk '{print $1}')
    echo IP = $(hostname -I)
    echo MASK = $(ifconfig | grep -A 1 "wlp3s0" | tail -1 | awk '{print $4}')
    echo GATEWAY = $(ip r | awk '/default/{print$3}')
    echo RAM_TOTAL = $(free -m | awk '/Mem:/ {printf "%.3f GB\n", $2/1024}')
    echo RAM_USED = $(free -m | awk '/Mem:/ {printf "%.3f GB\n", $3/1024}')
    echo RAM_FREE = $(free -m | awk '/Mem:/ {printf "%.3f GB\n", $4/1024}')
    echo SPACE_ROOT = $(df -m / | awk 'NR==2 {printf "%.2f MB\n", $2}')
    echo SPACE_ROOT_USED = $(df -m / | awk 'NR==2 {printf "%.2f MB\n", $3}')
    echo SPACE_ROOT_FREE = $(df -m / | awk 'NR==2 {printf "%.2f MB\n", $4}')
}