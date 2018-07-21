# Andrew Bub, RJ Stempak, Nick Ribera
#challenge contest2E
import sys

def hiphop(distance):
    if distance == 0:
        return 0

    hops = [1]
    while sum(hops) != distance:

        if can_return(hops + [hops[-1]+1], distance):
            hops.append(hops[-1] + 1)
        elif can_return(hops + [hops[-1]], distance):
            hops.append(hops[-1])
        else:
            hops.append(hops[-1] - 1)

    return len(hops)

def can_return(potential_hops, distance):
    curr_hop = potential_hops[-1]
    hop_distance = sum(potential_hops)
    while curr_hop != 1:
        hop_distance+=(curr_hop - 1)
        curr_hop-=1
        if hop_distance>distance:
            return False

    return True

for line in sys.stdin:
    start, end = line.split()
    print "{} -> {} takes {} hops".format(start, end, hiphop(int(end) - int(start)))
