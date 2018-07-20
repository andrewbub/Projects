#!/bin/sh

BASEDIR=$(dirname $0)
FAILURES=0

if [ ! -x hulk.py ]; then
    echo "hulk.py is not executable!"
    FAILURES=$((FAILURES + 1))
fi

if ! head -n 1 hulk.py | grep -q python2.7; then
    echo "hulk.py is does not have python2.7 in she-bang!"
    FAILURES=$((FAILURES + 1))
fi

if ! ./hulk.py -h 2>&1 | grep -q -i usage; then
    echo "hulk.py -h does not contain usage"
    FAILURES=$((FAILURES + 1))
fi

if [ $(./hulk.py -s $BASEDIR/hashes.txt -l 1 | wc -l) -ne 36 ]; then
    echo "hulk.py -l 1 -ne 36"
    FAILURES=$((FAILURES + 1))
fi

if [ $(./hulk.py -s $BASEDIR/hashes.txt -l 2 | wc -l) -ne 3 ]; then
    echo "hulk.py -l 2 -ne 3"
    FAILURES=$((FAILURES + 1))
fi

if [ $(./hulk.py -s $BASEDIR/hashes.txt -l 3 | wc -l) -ne 232 ]; then
    echo "hulk.py -l 3 -ne 232"
    FAILURES=$((FAILURES + 1))
fi

if [ $(./hulk.py -s $BASEDIR/hashes.txt -l 3 -c 2 | wc -l) -ne 232 ]; then
    echo "hulk.py -l 3 -c 2 -ne 232"
    FAILURES=$((FAILURES + 1))
fi

if [ $(./hulk.py -s $BASEDIR/hashes.txt -l 2 -p a | wc -l) -ne 6 ]; then
    echo "hulk.py -l 2 -p a -ne 232"
    FAILURES=$((FAILURES + 1))
fi

if [ $(./hulk.py -s $BASEDIR/hashes.txt -l 2 -p a -c 2 | wc -l) -ne 6 ]; then
    echo "hulk.py -l 2 -p a -c 2 -ne 232"
    FAILURES=$((FAILURES + 1))
fi

if [ $FAILURES -eq 0 ]; then
    echo "hulk.py tests successful"
    exit 0
else
    echo "hulk.py tests $FAILURES failures"
    exit 1
fi
