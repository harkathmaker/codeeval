# https://www.codeeval.com/open_challenges/70/

while read line; do
    if [ ${#line} -le 1 ]; then
        continue
    fi
    IFS=','
    rects=($line)
    unset IFS

    if [ $(( ${rects[0]} > ${rects[6]} || ${rects[4]} > ${rects[2]} ||
           ${rects[3]} > ${rects[5]} || ${rects[7]} > ${rects[1]} )) -eq 1 ]; then
        echo "False"
    else
        echo "True"
    fi
done < $1
