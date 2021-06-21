#!/bin/bash

OK="v"
OK="\u2713"
MESS_CORRECT="\e[32m${OK}\e[0m"
NOTOK="x"
NOTOK="\u2717"
NOTOK="(╯°□°)╯︵ ┻━┻"
MESS_INCORRECT="\e[31m${NOTOK}\e[0m"

APP=../debug_app.exe

TEST_DIR="./"
RES_DIR="res/"

mkdir -p $RES_DIR
rm -f ${RES_DIR}*

echo "NEGATIVE TESTS:"

for f_stdin in ${TEST_DIR}neg_*_stdin.txt
do
    f_stdout=${f_stdin/stdin/stdout}
    f_rc=${f_stdin/stdin/rc}
    expected_rc="$(cat $f_rc)"
    test_num=$(echo $f_stdin | cut -c7-8)
    res_f_stdout=${RES_DIR}${f_stdin/stdin/stdout}
    res_f_stderr=${RES_DIR}${f_stdin/stdin/stderr}
    res_f_valgrind=${RES_DIR}${f_stdin/stdin/valgrind}

    valgrind -q --leak-check=yes --leak-check=full --show-leak-kinds=all \
    --log-file=${res_f_valgrind} -- \
    cat $f_stdin | $APP > $res_f_stdout 2> $res_f_stderr

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

    echo -n " stderr: "
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

for f_stdin in ${TEST_DIR}pos_*_stdin.txt
do
    f_stdout=${f_stdin/stdin/stdout}
    test_num=$(echo $f_stdin | cut -c7-8)
    res_f_stdout=${RES_DIR}${f_stdin/stdin/stdout}
    res_f_stderr=${RES_DIR}${f_stdin/stdin/stderr}
    res_f_valgrind=${RES_DIR}${f_stdin/stdin/valgrind}

    valgrind -q --leak-check=yes --leak-check=full --show-leak-kinds=all \
    --log-file=${res_f_valgrind} -- \
    cat $f_stdin | $APP > $res_f_stdout 2> $res_f_stderr

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
    if cmp -s "$res_f_stdout" "$f_stdout"
    then
        echo -ne $MESS_CORRECT
    else
        echo -ne $MESS_INCORRECT
    fi

    echo -n " stderr: "
    if [ -s "$res_f_stderr" ]
    then
        echo -ne $MESS_INCORRECT
    else
        echo -ne $MESS_CORRECT
    fi

    echo ""
done

echo ""
