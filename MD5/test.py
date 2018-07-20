#!/usr/bin/env python2.7

import string
import itertools

ALPHABET = string.ascii_lowercase + string.digits
length = 2

def permutation(length, ALPHABET):
	for word in itertools.permutations(ALPHABET, length):
		yield ''.join(word)
