#!/usr/bin/env bash

rm ./results/result_*

scp edu-cmc-pv17-528-15@bluegene1.hpc.cs.msu.ru:/home_edu/edu-cmc-pv17/edu-cmc-pv17-528-15/sorting-network/src/result* ./results/
scp edu-cmc-pv17-528-15@bluegene1.hpc.cs.msu.ru:/home_edu/edu-cmc-pv17/edu-cmc-pv17-528-15/sorting-network/srcSequential/result* ./results/


