#!/bin/bash

# BUILD

gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -O0 --coverage -c ../main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -O0 --coverage -c ../funcs.c

gcc --coverage main.o funcs.o -o app.exe

echo -n "BUILD "
if [ "0" -ne "$?" ]; then
    echo "\e[31mFAILED\e[0m"
    exit
else
    echo -e "\e[32mSUCCESS\e[0m\n"
fi

# TEST

TEST_DIR='./'
RES_FILE='./result.txt'

echo 'POSITIVE TESTS:'

for pos_in in $( ls ${TEST_DIR}pos_*_in.txt ); do
    pos_out=${pos_in/in/out}
    pos_args=${pos_in/in/args}
    test_num=$(echo $pos_in | cut -c7-8)

    echo -n "${test_num}. "

    bash $pos_args &> $RES_FILE

    rc=$?

    echo -n "out_file: "
    if cmp -s "$RES_FILE" "$pos_out"; then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "rc: "
    if [ "0" -eq "$rc" ]; then
        echo -e "\e[32mCORRECT\e[0m"
    else
        echo -e "\e[31mINCORRECT (${rc})\e[0m"
    fi
done;
echo ""

echo 'NEGATIVE TESTS:'

EMPTY_FILE='./empty_file.txt'

for neg_args in $( ls ${TEST_DIR}neg_*_args.txt ); do
    neg_out=${neg_args/args/out}
    neg_in=${neg_args/args/in}
    test_num=$(echo $neg_in | cut -c7-8)

    echo -n "${test_num}. "

    bash $neg_args > $RES_FILE

    rc=$?

    echo -n 'out_file: '
    if cmp -s "$RES_FILE" "$EMPTY_FILE"; then
        echo -ne "\e[32mCORRECT\e[0m   "
    else
        echo -ne "\e[31mINCORRECT\e[0m "
    fi

    echo -n "rc: "
    if [ "$test_num" -eq "$rc" ]; then
        echo -e "\e[32mCORRECT\e[0m"
    else
        echo -e "\e[31mINCORRECT (${rc})\e[0m"
    fi
done;

echo ""

# GCOV

echo 'GCOV:'

gcov ./main.c
gcov ./funcs.c

mv *.gcov ../

# CLEAR
echo 'CLEAR'

rm *.exe
rm *.o

rm *.gcno
rm *.gcda

rm $RES_FILE
echo "Cleared"
