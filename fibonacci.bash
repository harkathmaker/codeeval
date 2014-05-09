#!/bin/bash
# https://www.codeeval.com/open_challenges/22/

while read line; do
    n=$line
    if ((n==0)); then
        echo 0
        continue
    elif ((n==1)); then
        echo 1
        continue
    fi
    n_k=0
    n_k1=1
    k=2
    while ((k < n)); do
        n_kn=$((n_k + n_k1))
        n_k=$n_k1
        n_k1=$n_kn
        k=$((k+1))
    done
    echo $((n_k + n_k1))
done < $1
