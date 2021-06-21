#!/bin/bash

TEST_DIR="./"
RES_FILE="./result.txt"
RES_DIR="res/"
APP='../debug_app.exe'

mkdir -p $RES_DIR
rm -f ${RES_DIR}*

echo "NEGATIVE TESTS:"

empty_file="${TEST_DIR}empty_file.txt"

for f_args in ${TEST_DIR}neg_*_args.txt
do
    f_out=${f_args/args/out}
    f_in=${f_args/args/in}
    f_rc=${f_args/args/rc}
    test_num=$(echo $f_in | cut -c7-8)
    res_f_dest=${RES_DIR}${f_args/args/dest}
    res_f_out=${RES_DIR}${f_args/args/out}
    res_f_err=${RES_DIR}${f_args/args/err}
    res_f_valgrind=${RES_DIR}${f_args/args/valgrind}
    expected_rc="$(cat ${f_args/args/rc})"

    echo -n "${test_num}. "

    valgrind -q --leak-check=yes --leak-check=full --show-leak-kinds=all \
    --log-file=${res_f_valgrind} -- \
    $APP $(cat $f_args) > $res_f_out 2> $res_f_err

    rc=$?

    echo -n 'out_file: '
    if cmp -s "$res_f_out" "$empty_file"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n 'err_file: '
    if cmp -s "$res_f_err" "$empty_file"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "rc: "
    if [ "$expected_rc" -eq "$rc" ]
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT (${rc})\e[0m"
    fi

    echo -n " memory_leaks: "
    if [ -s $res_f_valgrind ]
    then
        echo -e "\e[31mINCORRECT\e[0m "
    else
        echo -e "\e[32mCORRECT\e[0m   "
    fi

done

echo ""

echo 'POSITIVE TESTS:'

for f_args in ${TEST_DIR}pos_*_args.txt
do
    f_out=${f_args/args/out}
    f_in=${f_args/args/in}
    f_rc=${f_args/args/rc}
    test_num=$(echo $f_in | cut -c7-8)
    res_f_dest=${RES_DIR}${f_args/args/dest}
    res_f_out=${RES_DIR}${f_args/args/out}
    res_f_err=${RES_DIR}${f_args/args/err}
    res_f_valgrind=${RES_DIR}${f_args/args/valgrind}

    echo -n "${test_num}. "

    valgrind -q --leak-check=yes --leak-check=full --show-leak-kinds=all \
    --log-file=${res_f_valgrind} -- \
    $APP $(cat $f_args) > $res_f_out 2> $res_f_err

    rc=$?

    echo -n "out_file: "
    if cmp -s "$res_f_out" "$f_out"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "err_file: "
    if cmp -s "$res_f_err" "$empty_file"
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "rc: "
    if [ "0" -eq "$rc" ]
    then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT (${rc})\e[0m"
    fi

    echo -n " memory_leaks: "
    if [ -s $res_f_valgrind ]
    then
        echo -e "\e[31mINCORRECT\e[0m "
    else
        echo -e "\e[32mCORRECT\e[0m   "
    fi
 
done

echo ""
