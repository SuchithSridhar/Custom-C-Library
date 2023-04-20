#!/bin/bash

path="./test/data/"
readline_test_count=3
readfile_test_count=2
pass_count=0
test_count=1

end_count=$readline_test_count

for i in $(seq -f "%02g" $test_count $end_count)
do
    ./test/lib_test ./test/data/test$i.in "readline" > ./test/data/test$i.out
    if cmp -s ./test/data/test$i.out ./test/data/test$i.exp; then
        printf "==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n" $i
        ((pass_count = pass_count + 1))
    else
        printf "==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n" $i
        diff --color ./test/data/test$i.exp ./test/data/test$i.out
    fi
    ((test_count = test_count + 1))
done

((end_count = test_count + readfile_test_count - 1))

for i in $(seq -f "%02g" $test_count $end_count)
do
    ./test/lib_test ./test/data/test$i.in "readfile" > ./test/data/test$i.out
    if cmp -s ./test/data/test$i.out ./test/data/test$i.exp; then
        printf "==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n" $i
        ((pass_count = pass_count + 1))
    else
        printf "==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n" $i
        diff --color ./test/data/test$i.exp ./test/data/test$i.out
    fi
    ((test_count = test_count + 1))
done
