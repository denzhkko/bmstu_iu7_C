#!/bin/bash

# BUILD
gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -c ./main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wvla -c ./funcs.c

gcc ./main.o ./funcs.o -o main.exe

# TEST

TEST_DIR='./test_data/'
RES_BIN='./res.bin'
RES_TXT='./res.txt'

# TEST INCORRECT PARAM

echo -n "Incorrect param: "

./main.exe st ${TEST_DIR}s_in_one_item.bin $RES_BIN &> $RES_TXT

if cmp -s "$RES_TXT" "${TEST_DIR}g_out_incorrect_param.txt"; then
    echo -e "bin:\e[32mCORRECT\e[0m"
else
    echo -e "bin:\e[31mINCORRECT\e[0m"
fi

echo ''

# TEST SORT
SUB_DIR='sort_tests/'
for in_file_bin in $( ls ${TEST_DIR}${SUB_DIR}s_in_*.bin ); do
    out_file_bin=${in_file_bin/in/out}
    out_file_txt=${out_file_bin/bin/txt}

    ./main.exe sb $in_file_bin $RES_BIN &> $RES_TXT

    echo -n "${in_file_bin} -> "

    if cmp -s "$RES_BIN" "$out_file_bin"; then
        echo -n -e "bin:\e[32mCORRECT\e[0m "
    else
        echo -n -e "bin:\e[31mINCORRECT\e[0m "
    fi

    if cmp -s "$RES_TXT" "$out_file_txt"; then
        echo -e "txt:\e[32mCORRECT\e[0m"
    else
        echo -e "txt:\e[31mINCORRECT\e[0m"
    fi
done

echo ''

# TEST FIND
SUB_DIR='fd_tests/'
for in_file_bin in $( ls ${TEST_DIR}${SUB_DIR}f_in_*.bin ); do
    out_file_txt=${in_file_bin/in/out}
    out_file_txt=${out_file_txt/bin/txt}
    SUB_STR='cat'

    ./main.exe fb $in_file_bin $SUB_STR &> $RES_TXT

    echo -n "${in_file_bin} -> "

    if cmp -s "$RES_TXT" "$out_file_txt"; then
        echo -e "\e[32mCORRECT\e[0m"
    else
        echo -e "\e[31mINCORRECT\e[0m"
    fi
done

echo ''

# TEST FIND
SUB_DIR='append_tests/'
for in_primary_file_bin in $( ls ${TEST_DIR}${SUB_DIR}a_primary_in_*.bin); do
    in_file_bin=${in_primary_file_bin/primary_/}
    in_file_txt=${in_file_bin/bin/txt}
    out_file_bin=${in_file_bin/in/out}
    out_file_txt=${in_file_txt/in/out}

    cp $in_primary_file_bin $in_file_bin

    # echo $in_file_bin
    # echo $in_file_txt
    # echo $out_file_bin
    # echo $out_file_txt

    cat $in_file_txt | ./main.exe ab $in_file_bin &> $RES_TXT

    # echo "cat $in_file_txt | ./main.exe ab $in_file_bin &> $RES_TXT"

    echo -n "${in_file_bin} -> "

    if cmp -s "$in_file_bin" "$out_file_bin"; then
        echo -n -e "bin:\e[32mCORRECT\e[0m "
    else
        echo -n -e "bin:\e[31mINCORRECT\e[0m "
    fi

    if cmp -s "$out_file_txt" "$RES_TXT"; then
        echo -e "txt:\e[32mCORRECT\e[0m"
    else
        echo -e "txt:\e[31mINCORRECT\e[0m"
    fi

done


# CLEAR
rm *.o
# rm *.exe
rm $RES_BIN
# rm $RES_TXT
