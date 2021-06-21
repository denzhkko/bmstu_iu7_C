#!/bin/bash

OK="\u2714"
MESS_CORRECT="\e[32m${OK}\e[0m"
NOTOK="x"
MESS_INCORRECT="\e[31m${NOTOK}\e[0m"

APP=../debug_app.exe

TEST_DIR="./"
RES_FILE="./result.txt"
RES_DIR="res/"

mkdir -p $RES_DIR
rm -f ${RES_DIR}*

echo "NEGATIVE TESTS:"

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
        echo -ne $MESS_CORRECT
    else
        echo -ne $MESS_INCORRECT
        echo -ne "\e[31m(${rc})\e[0m"
    fi

    echo -n " memory_leaks: "
    if [ -s $res_f_valgrind ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo -n " stdout: "
    if [ -s "$res_f_stdout" ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo -n ' stderr: '
    if [ -s "$res_f_stderr" ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo ""
done

echo ""

echo "POSITIVE TESTS:"

for f_args in ${TEST_DIR}pos_*_args.txt
do
    f_f=${f_args/args/f}
    f_s=${f_args/args/s}
    f_out_f=${f_args/args/out_f}
    f_out_s=${f_args/args/out_s}
    test_num=$(echo $f_args | cut -c7-8)
    res_f_out_f=${RES_DIR}${f_args/args/out_f}
    res_f_out_s=${RES_DIR}${f_args/args/out_s}
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
        echo -ne $MESS_CORRECT
    else
        echo -ne $MESS_INCORRECT
        echo -ne "\e[31m(${rc})\e[0m"
    fi

    echo -n " memory_leaks: "
    if [ -s $res_f_valgrind ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo -n " stdout: "
    if [ -s "$res_f_stdout" ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo -n " stderr: "
    if [ -s "$res_f_stderr" ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo -n " file_out_f: "
    if cmp -s "$res_f_out_f" "$f_out_f"
    then
        echo -ne $MESS_CORRECT
    else
        echo -ne $MESS_INCORRECT
    fi

    echo -n " file_out_s: "
    if cmp -s "$res_f_out_s" "$f_out_s"
    then
        echo -ne $MESS_CORRECT
    else
        echo -ne $MESS_INCORRECT
    fi

    echo ""
done

echo ""
