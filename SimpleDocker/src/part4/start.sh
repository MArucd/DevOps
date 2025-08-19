#!/bin/bash

gcc server.c -lfcgi -o server
spawn-fcgi -a 127.0.0.1 -p 8080 server
nginx -g "daemon off;"
nginx -s reload