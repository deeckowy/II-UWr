#!/bin/bash
x=1
while [ $x -gt 0 ]
do
	x=$(netstat -n | grep 79.96.11.200 |wc -l)
done
