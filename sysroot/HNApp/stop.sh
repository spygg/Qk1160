# !/bin/sh                                                                      
kill -9 $(ps -o pid,comm | grep -i $1 | awk '{print $1}')
