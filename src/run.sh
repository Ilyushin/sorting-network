#!/usr/bin/env bash

rm result_* sortingNetworkExec.*
make clean
make
chmod +x sortingNetworkExec
#mpisubmit.bg --nproc 128 --mode smp sortingNetworkExec 500 500 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_500.out --stderr result_q_500.err  sortingNetworkExec 500 500 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_1000.out --stderr result_q_1000.err sortingNetworkExec 1000 1000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_2000.out --stderr result_q_2000.err sortingNetworkExec 2000 2000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_3000.out --stderr result_q_3000.err sortingNetworkExec 3000 3000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_4000.out --stderr result_q_4000.err sortingNetworkExec 4000 4000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_5000.out --stderr result_q_5000.err sortingNetworkExec 5000 5000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_6000.out --stderr result_q_6000.err sortingNetworkExec 6000 6000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_7000.out --stderr result_q_7000.err sortingNetworkExec 7000 7000 q
mpisubmit.bg --nproc 128 --mode smp --stdout result_q_8000.out --stderr result_q_8000.err sortingNetworkExec 8000 8000 q

#mpisubmit.bg --nproc 128 --mode smp --stdout result_500.out --stderr result_500.err sortingNetworkExec 500 500
#mpisubmit.bg --nproc 128 --mode smp --stdout result_1000.out --stderr result_1000.err sortingNetworkExec 1000 1000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_2000.out --stderr result_2000.err sortingNetworkExec 2000 2000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_3000.out --stderr result_3000.err sortingNetworkExec 3000 3000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_4000.out --stderr result_4000.err sortingNetworkExec 4000 4000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_5000.out --stderr result_5000.err sortingNetworkExec 5000 5000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_6000.out --stderr result_6000.err sortingNetworkExec 6000 6000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_7000.out --stderr result_7000.err sortingNetworkExec 7000 7000
#mpisubmit.bg --nproc 128 --mode smp --stdout result_8000.out --stderr result_8000.err sortingNetworkExec 8000 8000
#
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_500.out --stderr result_1_cpu_q_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_1000.out --stderr result_1_cpu_q_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_2000.out --stderr result_1_cpu_q_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_3000.out --stderr result_1_cpu_q_3000.err sortingNetworkExec 3000 3000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_4000.out --stderr result_1_cpu_q_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_5000.out --stderr result_1_cpu_q_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_6000.out --stderr result_1_cpu_q_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_7000.out --stderr result_1_cpu_q_7000.err sortingNetworkExec 7000 7000 q
#mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_8000.out --stderr result_1_cpu_q_8000.err sortingNetworkExec 8000 8000 q
