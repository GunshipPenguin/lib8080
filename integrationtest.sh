#!/usr/bin/env bash

TEST_DIR="test/integration"

run_test () {
    echo -n "Running test binary $1... "

    OUTPUT=$(./binloader $TEST_DIR/test_bins/$1)

    if [ "$OUTPUT" != "$(cat ${TEST_DIR}/test_bins/output/${1}.out)" ]
    then
        echo Outpt differs from expected output
        exit 1
    else
        echo Output matches!
    fi
}

run_test TEST.COM
run_test CPUTEST.COM
exit 0
