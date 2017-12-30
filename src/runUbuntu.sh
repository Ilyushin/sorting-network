#!/usr/bin/env bash
make clean
make -f MakefileUbuntu
chmod +x sortingNetworkExec
mpirun -np 4 ./sortingNetworkExec 10 10 4 "result.txt"