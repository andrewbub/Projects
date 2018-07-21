# challengeIIF

import sys
import math

def calcmiles(tacolist):
    count = 0
    total = 0
    for i in tacolist:
        j = math.pow(2,count)
        add = j * i
        total += add
        count += 1

    print long(total)


notend = True
while notend:
    tacolist = []
    numtacos = sys.stdin.readline()
    if not numtacos:
        notend = False
        break
    if numtacos == '0\n':
        print '0'
        continue
    tacos = sys.stdin.readline().split()
    [ tacolist.append(int(i)) for i in tacos ]
    calcmiles(sorted(tacolist, reverse=True))
