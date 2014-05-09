# https://www.codeeval.com/open_challenges/34/

while read line; do
    if [ ${#line} -le 1 ]; then
        continue
    fi
    IFS=';'
    arr=($line)
    IFS=','
    values=(${arr[0]})
    unset IFS

    goal=${arr[1]}
    begin=0
    end=$((${#values[@]}-1))
    pairs=0
    lastPair=
    while (($begin < $end)); do
        sum=$((values[begin]+values[end]))
        if [ $sum -eq $goal ] && [[ "${values[begin]},${values[end]}" != $lastPair ]]; then
            if ((pairs != 0)); then
                echo -n ";"
            fi
            echo -n "${values[begin]},${values[end]}"
            pairs=$((pairs+1))
            lastPair="${values[begin]},${values[end]}"
        fi
        if ((values[begin]+values[end] <= goal)); then
            begin=$((begin+1))
        else
            end=$((end-1))
        fi
    done
    if ((pairs == 0)); then
        echo -n "NULL"
    fi
    printf "\n"
done < $1
