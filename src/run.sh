#!/usr/bin/env bash

llcancel -u edu-cmc-pv17-528-15
rm result_* sortingNetworkExec.* core.*
make clean
make
chmod +x sortingNetworkExec

mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_500.out --stderr result_q_500.err  sortingNetworkExec 500 500 5000 "result_500.txt"
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_1000.out --stderr result_q_1000.err sortingNetworkExec 1000 1000 10000 "result_10000.txt"
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_2000.out --stderr result_q_2000.err sortingNetworkExec 2000 2000 20000 "result_20000.txt"
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_4000.out --stderr result_q_4000.err sortingNetworkExec 4000 4000 40000 "result_40000.txt"
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_5000.out --stderr result_q_5000.err sortingNetworkExec 5000 5000 50000 "result_50000.txt"
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_6000.out --stderr result_q_6000.err sortingNetworkExec 6000 6000 60000 "result_60000.txt"
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_7000.out --stderr result_q_7000.err sortingNetworkExec 7000 7000 70000 "result_60000.txt"

#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_500.out --stderr result_q_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_1000.out --stderr result_q_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_2000.out --stderr result_q_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_4000.out --stderr result_q_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_5000.out --stderr result_q_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_6000.out --stderr result_q_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_q_7000.out --stderr result_q_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_500.out --stderr result_q_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_1000.out --stderr result_q_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_2000.out --stderr result_q_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_4000.out --stderr result_q_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_5000.out --stderr result_q_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_6000.out --stderr result_q_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_7000.out --stderr result_q_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_500.out --stderr result_q_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_1000.out --stderr result_q_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_2000.out --stderr result_q_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_4000.out --stderr result_q_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_5000.out --stderr result_q_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_6000.out --stderr result_q_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_7000.out --stderr result_q_7000.err sortingNetworkExec 7000 7000 p

#*******************************************************
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_500.out --stderr result_p_cpu_2_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_1000.out --stderr result_p_cpu_2_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_2000.out --stderr result_p_cpu_2_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_4000.out --stderr result_p_cpu_2_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_5000.out --stderr result_p_cpu_2_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_6000.out --stderr result_p_cpu_2_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 2 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_2_7000.out --stderr result_p_cpu_2_7000.err sortingNetworkExec 7000 7000 p
#
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_500.out --stderr result_p_cpu_4_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_1000.out --stderr result_p_cpu_4_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_2000.out --stderr result_p_cpu_4_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_4000.out --stderr result_p_cpu_4_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_5000.out --stderr result_p_cpu_4_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_6000.out --stderr result_p_cpu_4_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 4 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_4_7000.out --stderr result_p_cpu_4_7000.err sortingNetworkExec 7000 7000 p
#
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_500.out --stderr result_p_cpu_8_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_1000.out --stderr result_p_cpu_8_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_2000.out --stderr result_p_cpu_8_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_4000.out --stderr result_p_cpu_8_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_5000.out --stderr result_p_cpu_8_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_6000.out --stderr result_p_cpu_8_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 8 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_8_7000.out --stderr result_p_cpu_8_7000.err sortingNetworkExec 7000 7000 p
#
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_500.out --stderr result_p_cpu_16_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_1000.out --stderr result_p_cpu_16_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_2000.out --stderr result_p_cpu_16_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_4000.out --stderr result_p_cpu_16_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_5000.out --stderr result_p_cpu_16_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_6000.out --stderr result_p_cpu_16_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 16 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_16_7000.out --stderr result_p_cpu_16_7000.err sortingNetworkExec 7000 7000 p
#
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_500.out --stderr result_p_cpu_32_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_1000.out --stderr result_p_cpu_32_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_2000.out --stderr result_p_cpu_32_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_4000.out --stderr result_p_cpu_32_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_5000.out --stderr result_p_cpu_32_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_6000.out --stderr result_p_cpu_32_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 32 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_32_7000.out --stderr result_p_cpu_32_7000.err sortingNetworkExec 7000 7000 p
#
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_500.out --stderr result_p_cpu_64_500.err  sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_1000.out --stderr result_p_cpu_64_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_2000.out --stderr result_p_cpu_64_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_4000.out --stderr result_p_cpu_64_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_5000.out --stderr result_p_cpu_64_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_6000.out --stderr result_p_cpu_64_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 64 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_64_7000.out --stderr result_p_cpu_64_7000.err sortingNetworkExec 7000 7000 p
#
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_500.out --stderr result_p_cpu_128_500.err   sortingNetworkExec 500 500 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_1000.out --stderr result_p_cpu_128_1000.err sortingNetworkExec 1000 1000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_2000.out --stderr result_p_cpu_128_2000.err sortingNetworkExec 2000 2000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_4000.out --stderr result_p_cpu_128_4000.err sortingNetworkExec 4000 4000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_5000.out --stderr result_p_cpu_128_5000.err sortingNetworkExec 5000 5000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_6000.out --stderr result_p_cpu_128_6000.err sortingNetworkExec 6000 6000 p
#mpisubmit.bg --nproc 128 --mode smp -e "OMP_NUM_THREADS=2" --stdout result_p_cpu_128_7000.out --stderr result_p_cpu_128_7000.err sortingNetworkExec 7000 7000 p

#*******************************************************
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_500.out --stderr result_q_cpu_2_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_1000.out --stderr result_q_cpu_2_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_2000.out --stderr result_q_cpu_2_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_4000.out --stderr result_q_cpu_2_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_5000.out --stderr result_q_cpu_2_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_6000.out --stderr result_q_cpu_2_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 2 --mode smp --stdout result_q_cpu_2_7000.out --stderr result_q_cpu_2_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_500.out --stderr result_q_cpu_4_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_1000.out --stderr result_q_cpu_4_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_2000.out --stderr result_q_cpu_4_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_4000.out --stderr result_q_cpu_4_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_5000.out --stderr result_q_cpu_4_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_6000.out --stderr result_q_cpu_4_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 4 --mode smp --stdout result_q_cpu_4_7000.out --stderr result_q_cpu_4_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_500.out --stderr result_q_cpu_8_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_1000.out --stderr result_q_cpu_8_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_2000.out --stderr result_q_cpu_8_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_4000.out --stderr result_q_cpu_8_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_5000.out --stderr result_q_cpu_8_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_6000.out --stderr result_q_cpu_8_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 8 --mode smp --stdout result_q_cpu_8_7000.out --stderr result_q_cpu_8_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_500.out --stderr result_q_cpu_16_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_1000.out --stderr result_q_cpu_16_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_2000.out --stderr result_q_cpu_16_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_4000.out --stderr result_q_cpu_16_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_5000.out --stderr result_q_cpu_16_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_6000.out --stderr result_q_cpu_16_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 16 --mode smp --stdout result_q_cpu_16_7000.out --stderr result_q_cpu_16_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_500.out --stderr result_q_cpu_32_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_1000.out --stderr result_q_cpu_32_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_2000.out --stderr result_q_cpu_32_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_4000.out --stderr result_q_cpu_32_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_5000.out --stderr result_q_cpu_32_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_6000.out --stderr result_q_cpu_32_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 32 --mode smp --stdout result_q_cpu_32_7000.out --stderr result_q_cpu_32_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_500.out --stderr result_q_cpu_64_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_1000.out --stderr result_q_cpu_64_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_2000.out --stderr result_q_cpu_64_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_4000.out --stderr result_q_cpu_64_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_5000.out --stderr result_q_cpu_64_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_6000.out --stderr result_q_cpu_64_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 64 --mode smp --stdout result_q_cpu_64_7000.out --stderr result_q_cpu_64_7000.err sortingNetworkExec 7000 7000 q
#
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_500.out --stderr result_q_cpu_128_500.err  sortingNetworkExec 500 500 q
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_1000.out --stderr result_q_cpu_128_1000.err sortingNetworkExec 1000 1000 q
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_2000.out --stderr result_q_cpu_128_2000.err sortingNetworkExec 2000 2000 q
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_4000.out --stderr result_q_cpu_128_4000.err sortingNetworkExec 4000 4000 q
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_5000.out --stderr result_q_cpu_128_5000.err sortingNetworkExec 5000 5000 q
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_6000.out --stderr result_q_cpu_128_6000.err sortingNetworkExec 6000 6000 q
#mpisubmit.bg --nproc 128 --mode smp --stdout result_q_cpu_128_7000.out --stderr result_q_cpu_128_7000.err sortingNetworkExec 7000 7000 q

#*******************************************************
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_500.out --stderr result_h_cpu_2_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_1000.out --stderr result_h_cpu_2_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_2000.out --stderr result_h_cpu_2_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_4000.out --stderr result_h_cpu_2_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_5000.out --stderr result_h_cpu_2_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_6000.out --stderr result_h_cpu_2_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 2 --mode smp --stdout result_h_cpu_2_7000.out --stderr result_h_cpu_2_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_500.out --stderr result_h_cpu_4_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_1000.out --stderr result_h_cpu_4_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_2000.out --stderr result_h_cpu_4_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_4000.out --stderr result_h_cpu_4_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_5000.out --stderr result_h_cpu_4_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_6000.out --stderr result_h_cpu_4_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 4 --mode smp --stdout result_h_cpu_4_7000.out --stderr result_h_cpu_4_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_500.out --stderr result_h_cpu_8_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_1000.out --stderr result_h_cpu_8_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_2000.out --stderr result_h_cpu_8_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_4000.out --stderr result_h_cpu_8_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_5000.out --stderr result_h_cpu_8_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_6000.out --stderr result_h_cpu_8_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 8 --mode smp --stdout result_h_cpu_8_7000.out --stderr result_h_cpu_8_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_500.out --stderr result_h_cpu_16_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_1000.out --stderr result_h_cpu_16_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_2000.out --stderr result_h_cpu_16_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_4000.out --stderr result_h_cpu_16_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_5000.out --stderr result_h_cpu_16_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_6000.out --stderr result_h_cpu_16_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 16 --mode smp --stdout result_h_cpu_16_7000.out --stderr result_h_cpu_16_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_500.out --stderr result_h_cpu_32_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_1000.out --stderr result_h_cpu_32_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_2000.out --stderr result_h_cpu_32_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_4000.out --stderr result_h_cpu_32_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_5000.out --stderr result_h_cpu_32_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_6000.out --stderr result_h_cpu_32_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 32 --mode smp --stdout result_h_cpu_32_7000.out --stderr result_h_cpu_32_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_500.out --stderr result_h_cpu_64_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_1000.out --stderr result_h_cpu_64_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_2000.out --stderr result_h_cpu_64_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_4000.out --stderr result_h_cpu_64_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_5000.out --stderr result_h_cpu_64_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_6000.out --stderr result_h_cpu_64_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 64 --mode smp --stdout result_h_cpu_64_7000.out --stderr result_h_cpu_64_7000.err sortingNetworkExec 7000 7000 h
#
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_500.out --stderr result_h_cpu_128_500.err  sortingNetworkExec 500 500 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_1000.out --stderr result_h_cpu_128_1000.err sortingNetworkExec 1000 1000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_2000.out --stderr result_h_cpu_128_2000.err sortingNetworkExec 2000 2000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_4000.out --stderr result_h_cpu_128_4000.err sortingNetworkExec 4000 4000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_5000.out --stderr result_h_cpu_128_5000.err sortingNetworkExec 5000 5000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_6000.out --stderr result_h_cpu_128_6000.err sortingNetworkExec 6000 6000 h
#mpisubmit.bg --nproc 128 --mode smp --stdout result_h_cpu_128_7000.out --stderr result_h_cpu_128_7000.err sortingNetworkExec 7000 7000 h