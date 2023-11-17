#!/bin/bash

get_pmos() {
    exec 3<> /dev/cpu_dma_frequency
    echo "0" >&3
    echo "waiting for a click"
    while :; do sleep 2073600; done
    echo "clicked!"
}

# Sample run script
latency_test() {
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
    dmesg | sed -n "$msgstart,$msgend" | grep "avg" | tee -a output.txt
}

# Disable CPU Prefetching
wrmsr -a 0x1a4 0xf

export AEPWatch=1
export EMon=0

export PATH=$PATH:`pwd`/subtests/bin
testapp=$1
#./subtests/30_stridebw.sh
repdev=`mount | grep ReportFS | awk {'print \$1'}`
testdev=`mount | grep LatencyFS | awk {'print \$1'}`
runtime=1

if [ -z $repdev ] || [ -z $testdev ]; then
	echo "Please run mount.sh first"
	exit 1
fi

get_pmos&

echo =====Workload description====
echo Run: $testapp
echo LatFS on: $testdev
echo RepFS on: $repdev
echo Config:
cat config.json
echo Press any key to continue...
read


for i in `seq $runtime`; do
    export TAG=repeatr$i
    echo Tag: $TAG
    latency_test
    
    mv output.txt ./$TAG.output.txt
done

wrmsr -a 0x1a4 0x0

# this should kill your own descendents, says the internet
pkill -P $$

