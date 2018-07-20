#!/usr/bin/env python2.7

import sys
import time

numSeconds = int(sys.argv[1])
i = 0

while True:
	i += 1
	time.sleep(numSeconds)
	print (i, "I am the sleepy process piping in every", numSeconds, "seconds")

	
