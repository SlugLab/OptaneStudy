#!/bin/bash

rm -f output.txt

start=`dmesg | tail -1 | cut -d "[" -f2 | cut -d "]" -f1`	
msg="BASIC_LAT_TEST"
echo "task=1,message=$msg" | tee -a output.txt
echo "task=1,message=$msg" > /proc/lattester

while true; do
    x=`dmesg | grep 'LATTester_LAT_END' | tail -1 | cut -d "[" -f2 | cut -d "]" -f1`
    if (( $(echo "$x > $start" | bc -l) )); then
	break;
    fi
    sleep 1
done

msgstart=`dmesg | grep -n 'LATTester_START' | tail -1 | awk -F':' {' print $1 '}`
msgend=`dmesg | grep -n 'LATTester_LAT_END' | tail -1 | awk -F':' {' print $1 '}`
msgend+="p"
dmesg | sed -n "$msgstart,$msgend" | grep "average" | tee -a output.txt
