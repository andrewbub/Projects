#!/usr/bin/env python2.7

import sys

counts = {}
for line in sys.stdin:
	word, linenumber = line.split('\t', 1)
	if word in counts:
		counts[word].add(int(linenumber))
	else:
		counts[word] = set()
		counts[word].add(int(linenumber))

for k, v in sorted(counts.items()):
	v = [str(i) for i in sorted(v)]
	nums = ' '.join(v)
	print'{}\t{}'.format(k, nums)
