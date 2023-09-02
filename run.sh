#!/bin/bash
mkdir build
cd build
cmake ..
make -j

numactl --membind 0 taskset -c 2 ./optanestudy 
numactl --membind 1 taskset -c 2 ./optanestudy 