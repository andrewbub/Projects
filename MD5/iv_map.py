#!/usr/bin/env python2.7

import sys
import string

alphabet = string.letters + string.digits + string.whitespace + '-'
count = 1

for line in sys.stdin:
	count = count + 1
	for word in line.strip().lower().split():
		word = ''.join([c for c in word if c in alphabet])
		print '{}\t{}'.format(word, count-1)
