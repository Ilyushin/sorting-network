#!/usr/bin/env bash
make clean
make -f MakefileUbuntu
chmod +x sortingNetworkExec
mpirun -np 2 ./sortingNetworkExec 4 4