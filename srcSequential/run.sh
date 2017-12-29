#!/usr/bin/env bash

#llcancel -u edu-cmc-pv17-528-15
rm result_* sortingNetworkExec.* core.*
make clean
make
chmod +x sortingNetworkExec
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_500.out --stderr result_1_cpu_q_500.err  sortingNetworkExec 500 500
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_1000.out --stderr result_1_cpu_q_1000.err sortingNetworkExec 1000 1000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_2000.out --stderr result_1_cpu_q_2000.err sortingNetworkExec 2000 2000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_3000.out --stderr result_1_cpu_q_3000.err sortingNetworkExec 3000 3000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_4000.out --stderr result_1_cpu_q_4000.err sortingNetworkExec 4000 4000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_5000.out --stderr result_1_cpu_q_5000.err sortingNetworkExec 5000 5000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_6000.out --stderr result_1_cpu_q_6000.err sortingNetworkExec 6000 6000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_7000.out --stderr result_1_cpu_q_7000.err sortingNetworkExec 7000 7000
mpisubmit.bg --nproc 1 --mode smp --stdout result_1_cpu_q_8000.out --stderr result_1_cpu_q_8000.err sortingNetworkExec 8000 8000
