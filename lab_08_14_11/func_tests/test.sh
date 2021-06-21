#!/bin/bash

APP=../debug_app.exe

TEST_DIR="./"
RES_FILE="./result.txt"
RES_DIR="res/"

mkdir -p $RES_DIR
rm -f ${RES_DIR}*

echo "NEGATIVE TESTS:"

empty_file="${TEST_DIR}empty_file.txt"

for f_args in ${TEST_DIR}neg_*_args.txt
do
    f_f=${f_args/args/f}
    f_s=${f_args/args/s}
    f_out=${f_args/args/out}
    f_rc=${f_args/args/rc}
    test_num=$(echo $f_args | cut -c7-8)
    res_f_out=${RES_DIR}${f_args/args/out}
    res_f_stdout=${RES_DIR}${f_args/args/stdout}
    res_f_stderr=${RES_DIR}${f_args/args/stderr}
    res_f_valgrind=${RES_DIR}${f_args/args/valgrind}
    expected_rc="$(cat ${f_args/args/rc})"

    # echo "f_f = $f_f"
    # echo "f_s = $f_s"
    # echo "f_out = $f_out"
    # echo "test_num = $test_num"
    # echo "res_f_out = $res_f_out"
    # echo "res_f_stdout = $res_f_stdout"
    # echo "res_f_stderr = $res_f_stderr"
    # echo "res_f_valgrind = $res_f_valgrind"
    # echo "expected_rc = $expected_rc"

    valgrind -q --leak-check=yes --leak-check=full --show-leak-kinds=all \
    --log-file=${res_f_valgrind} -- \
    $APP $(cat $f_args) > $res_f_stdout 2> $res_f_stderr

    rc=$?

    echo -n "${test_num}. "

    echo -n "rc: "
    if [ "$expected_rc" -eq "$rc" ]
    then
        echo -ne "\e[32mOK  \e[0m"
    else
        echo -ne "\e[31mX (${rc}) \e[0m"
    fi

    echo -n "memory_leaks: "
    if [ -s $res_f_valgrind ]
    then
        echo -ne "\e[31mX \e[0m "
    else
        echo -ne "\e[32mOK\e[0m "
    fi

    echo -n "stdout: "
    if cmp -s "$res_f_stdout" "$empty_file"
    then
        echo -ne "\e[32mOK\e[0m "
    else
        echo -ne "\e[31mX \e[0m "
    fi

    echo -n 'stderr: '
    if cmp -s "$res_f_stderr" "$empty_file"
    then
        echo -ne "\e[32mOK\e[0m "
    else
        echo -ne "\e[31mX \e[0m "
    fi

    echo ""
done

echo ""

echo "POSITIVE TESTS:"

for f_args in ${TEST_DIR}pos_*_args.txt
do
    f_f=${f_args/args/f}
    f_s=${f_args/args/s}
    f_out=${f_args/args/out}
    test_num=$(echo $f_args | cut -c7-8)
    res_f_out=${RES_DIR}${f_args/args/out}
    res_f_stdout=${RES_DIR}${f_args/args/stdout}
    res_f_stderr=${RES_DIR}${f_args/args/stderr}
    res_f_valgrind=${RES_DIR}${f_args/args/valgrind}

    # echo "f_f = $f_f"
    # echo "f_s = $f_s"
    # echo "f_out = $f_out"
    # echo "test_num = $test_num"
    # echo "res_f_out = $res_f_out"
    # echo "res_f_stdout = $res_f_stdout"
    # echo "res_f_stderr = $res_f_stderr"
    # echo "res_f_valgrind = $res_f_valgrind"

    valgrind -q --leak-check=yes --leak-check=full --show-leak-kinds=all \
    --log-file=${res_f_valgrind} -- \
    $APP $(cat $f_args) > $res_f_stdout 2> $res_f_stderr

    rc=$?

    echo -n "${test_num}. "

    echo -n "rc: "
    if [ "0" -eq "$rc" ]
    then
        echo -ne "\e[32mOK  \e[0m"
    else
        echo -ne "\e[31mX (${rc}) \e[0m"
    fi

    echo -n "memory_leaks: "
    if [ -s $res_f_valgrind ]
    then
        echo -ne "\e[31mX \e[0m "
    else
        echo -ne "\e[32mOK\e[0m "
    fi

    echo -n "stdout: "
    if cmp -s "$res_f_stdout" "$empty_file"
    then
        echo -ne "\e[32mOK\e[0m "
    else
        echo -ne "\e[31mX \e[0m "
    fi

    echo -n "stderr: "
    if cmp -s "$res_f_stderr" "$empty_file"
    then
        echo -ne "\e[32mOK\e[0m "
    else
        echo -ne "\e[31mX \e[0m "
    fi

    echo -n "out_file: "
    if cmp -s "$res_f_out" "$f_out"
    then
        echo -ne "\e[32mOK\e[0m "
    else
        echo -ne "\e[31mX \e[0m "
    fi

    echo ""
done

echo ""
