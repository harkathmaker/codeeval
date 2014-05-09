#!/bin/bash
# https://www.codeeval.com/open_challenges/10/

while read line; do
    declare -a elements
    elements=($line)
    lastEl=${#elements[@]}
    let lastEl=$lastEl-1
    if ((lastEl <= 0)); then
        continue
    fi
    let mthToLast=lastEl-elements[lastEl]
    if ((mthToLast < lastEl && mthToLast >= 0)); then
        echo "${elements[$mthToLast]}"
    fi
done < $1
