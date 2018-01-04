#!/usr/bin/env bash
make clean
make -f MakefileUbuntu
chmod +x sortingNetworkExec
mpirun -np 5 ./sortingNetworkExec 500 500