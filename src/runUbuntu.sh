#!/usr/bin/env bash
make clean
make -f MakefileUbuntu
chmod +x sortingNetworkExec
mpirun -np 4 ./sortingNetworkExec 100 100 4 "result.txt"