#!/usr/bin/env bash

chmod +x sortingNetworkExec
mpisubmit.bg --nproc 128 --mode smp sortingNetworkExec 10000 10000
