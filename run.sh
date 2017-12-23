#!/usr/bin/env bash

mpisubmit.bg --nproc 128 --mode smp  ./src/sortingNetworkExec 10000 10000
