#!/bin/bash
# https://www.codeeval.com/open_challenges/106/

declare -a letters=(M D C L X V I)
declare -a values=(1000 500 100 50 10 5 1)

letterLength=${#letters[@]}

while read line; do
    output=""
    for ((i=0; i<$letterLength; i++));
    do
        while [ $line -ge ${values[$i]} ]; do
            let line=$line-${values[$i]}
            output="$output${letters[$i]}"
        done
        exception=$((2*(i/2)+2))
        if (( line >= values[i]-values[exception] )) ; then
            let line=$line-${values[$i]}+${values[$exception]}
            output="$output${letters[$exception]}${letters[$i]}"
        fi
    done
    echo $output
done < $1
