#!/bin/bash

APP='../app.exe'
RES_FILE='./result.txt'
RES_DIR='res/'

mkdir -p $RES_DIR

# CLEAN

rm -f ${RES_DIR}*

# Test

echo "NEGATIVE TESTS:"

EMPTY_FILE='./empty_file.txt'

for f_args in $( ls neg_*_args.txt ); do
    f_src=${f_args/args/src}
    f_dest=${f_src/src/dest}
    res_f_dest="${RES_DIR}${f_dest}"
    res_f_out="${RES_DIR}${f_dest/dest/out}"
    test_num=$(echo $f_src | cut -c5-6)
    expected_rc="$(cat ${f_args/args/rc})"
    args="$(cat $f_args)"
    f_valgrind_log="${res_f_dest/dest/valgrind_log}"

    echo -n "${test_num}. "

    # bash "$f_args" &> "$res_f_out"
    valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all \
        --log-file=${f_valgrind_log} -- \
        $args &> "$res_f_out"

    rc=$?

    if [ ! -f "$res_f_dest" ]
    then
        touch "$res_f_dest"
    fi

    echo -n "dst_file: "
    if cmp -s "$res_f_dest" "$EMPTY_FILE"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "out_file: "
    if cmp -s "$res_f_out" "$EMPTY_FILE"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "rc: "
    if [ "${rc}" -eq "$expected_rc" ]; then
        echo -e "\e[32mCORRECT\e[0m"
    else
        echo -e "\e[31mINCORRECT (${rc})\e[0m"
    fi
done;

echo ""

echo "POSITIVE TESTS:"

EMPTY_FILE='./empty_file.txt'

for f_args in $( ls pos_*_args.txt ); do
    f_src=${f_args/args/src}
    f_dest=${f_src/src/dest}
    res_f_dest="${RES_DIR}${f_dest}"
    res_f_out="${RES_DIR}${f_dest/dest/out}"
    test_num=$(echo $f_src | cut -c5-6)
    args="$(cat $f_args)"
    f_valgrind_log="${res_f_dest/dest/valgrind_log}"

    echo -n "${test_num}. "

    valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all \
        --log-file=${f_valgrind_log} -- \
        $args &> "$res_f_out"

    rc=$?

    if [ ! -f "$res_f_dest" ]
    then
        touch "$res_f_dest"
    fi

    echo -n "dst_file: "
    if cmp -s "$res_f_dest" "$f_dest"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "out_file: "
    if cmp -s "$res_f_out" "$EMPTY_FILE"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "rc: "
    if [ "${rc}" -eq "0" ]; then
        echo -e "\e[32mCORRECT\e[0m"
    else
        echo -e "\e[31mINCORRECT (${rc})\e[0m"
    fi
done;

echo ""
