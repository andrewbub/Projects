#!/usr/bin/env python2.7

import functools
import hashlib
import itertools
import multiprocessing
import os
import string
import sys

# Constants

ALPHABET    = string.ascii_lowercase + string.digits
ARGUMENTS   = sys.argv[1:]
CORES       = 1
HASHES      = 'hashes.txt'
LENGTH      = 1
PREFIX      = ''

# Functions

def usage(exit_code=0):
    print '''Usage: {} [-a alphabet -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file'''.format(os.path.basename(sys.argv[0]))
    sys.exit(exit_code)

def md5sum(s):
    return hashlib.md5(s).hexdigest()

def permutations(length, alphabet=ALPHABET):
    if length == 1:
        for n in alphabet:
            yield n
    else:
        for i in alphabet:
            for x in permutations(length-1, alphabet):
                yield i + x

def smash(hashes, length, alphabet=ALPHABET, prefix=''):
    pswd = [prefix + x for x in permutations(length, alphabet) if md5sum(prefix + x) in hashes]
    return pswd

# Main Execution

if __name__ == '__main__':
    # Parse command line arguments
    args = sys.argv[1:]
    while len(args) and args[0].startswith('-') and len(args[0]) > 1:
        arg = args.pop(0)
        if arg == '-a':
            ALPHABET = args.pop(0) 
        elif arg == '-c':
            CORES = int(args.pop(0))
        elif arg == '-l':
            LENGTH = int(args.pop(0))
        elif arg == '-p':
            PREFIX = args.pop(0)
        elif arg == '-s':
            HASHES = args.pop(0)
        elif arg == '-h':
            usage(0)
        else:
            usage(1)


    #  Load hashes set
    hashes = set()
    with open(HASHES) as f:
        content = f.readlines()
    for x in content:
        hashes.add(x.rstrip())


    # Execute smash function to get passwords
    if CORES == 1 and LENGTH ==1:
        passwords = smash(hashes, LENGTH, ALPHABET, PREFIX)
    else:
        prefix_length = LENGTH / 2
        new_length = LENGTH - prefix_length
        new_prefixes = permutations(prefix_length, ALPHABET)
        subsmash = functools.partial(smash, hashes, new_length, ALPHABET)
        pool = multiprocessing.Pool(CORES)
        passwords = itertools.chain.from_iterable(pool.imap(subsmash, [PREFIX + new for new in new_prefixes]))

    # Print passwords
    for password in passwords:
        print password

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
