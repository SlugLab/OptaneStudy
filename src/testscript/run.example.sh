#!/bin/bash

# Sample run script

# Disable CPU Prefetching
wrmsr -a 0x1a4 0xf

export GOOGLE_APPLICATION_CREDENTIALS=dbuser.json
export AEPWatch=1
export EMon=0

export PATH=$PATH:`pwd`/subtests/bin
testapp=$1
#./subtests/30_stridebw.sh
repdev=`mount | grep ReportFS | awk {'print \$1'}`
testdev=`mount | grep LatencyFS | awk {'print \$1'}`
runtime=20

if [ -z $repdev ] || [ -z $testdev ]; then
	echo "Please run mount.sh first"
	exit 1
fi


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
    
    $testapp $repdev $testdev
    ./parse_bw.py output.txt $runtime 1 > $TAG.summary.txt
    mv output.txt ./$TAG.output.txt

done

wrmsr -a 0x1a4 0x0

aeprelease
