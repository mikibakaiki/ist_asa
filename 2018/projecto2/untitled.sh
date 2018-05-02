#!/bin/bash
failed=0
passed=0
RED='\033[0;31m'
NC='\033[0m' # No Color
GREEN='\033[0;32m'
BOLD='\e[1m'
NORMAL='\e[0m'

for x in tests-proj2/*.in; do
    if [ -e ${x%.in} ]; then
        ./test < $x > ${x%.in}.txt ;
    fi

    diff -cB -w ${x%.in}.out ${x%.in}.txt > ${x%.in}.diff ;

    if [ -s ${x%.in}.diff ]; then
        failed=$((failed+1))
        printf "${RED}FAILED: $x. ${NC}See file ${x%.in}.diff\n" ;
    else
        passed=$((passed+1))
        printf "${BOLD}${GREEN}PASSED: ${NORMAL}$x\n"
        rm -f ${x%.in}.diff ${x%.in}.outhyp ;
    fi
done

rm -f saved*

printf "${NORMAL}${NC}Done.\n"