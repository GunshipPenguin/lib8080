#!/usr/bin/env bash

TEST_DIR="test/integration"

run_test () {
    echo -n "Running test binary $1... "

    ACTUAL=$(./binloader $TEST_DIR/test_bins/$1)
    EXPECTED=$(cat ${TEST_DIR}/test_bins/output/${1}.out)

    if [ "$ACTUAL" != "$EXPECTED" ]
    then
        echo Outpt differs from expected output
        echo "*******ACTUAL OUTPUT*******"
        echo "$ACTUAL"
        echo "*******EXPECTED OUTPUT*******"
        echo "$EXPECTED"
        echo "*******END EXPECTED OUTPUT*******"
        exit 1
    else
        echo Output matches!
    fi
}

run_test TEST.COM
run_test CPUTEST.COM
run_test 8080PRE.COM
run_test 8080EXM.COM
exit 0
