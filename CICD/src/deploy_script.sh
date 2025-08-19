#!/bin/bash

scp cat/s21_cat lifeboal@192.168.100.11:/usr/local/bin/
scp grep/s21_grep lifeboal@192.168.100.11:/usr/local/bin/

ssh lifeboal@192.168.100.11 ls -lah /usr/local/bin/
