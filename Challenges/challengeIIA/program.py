# challengeIIA

import sys
import itertools

def findgroups(graph, numcnt):
    groups = []
    visited = []
    for num in sorted(graph):
        new_group = DFS(graph, num, visited)
        visited.extend(new_group)
        if new_group:
            groups.append(new_group)

    #PRINTING
    print 'Graph', numcnt, 'has', len(groups), 'groups:'
    for gs in sorted(groups):
        name = ' '.join([str(c) for c in sorted(gs)])
        print name

def DFS(graph, start, visited):
    group = []
    stack = [start]
    while stack:
        vertex = stack.pop()
        if vertex not in visited and vertex not in group:
            group.append(vertex)
            stack.extend([v for v in sorted(graph[vertex]) if v not in visited])

    return group


def main():
    num_graph = 0
    while True:
        num_graph += 1
        nodedict = {}
        numnodes = sys.stdin.readline().strip()
        if not numnodes:
            break
        else:
            for node in range(1, int(numnodes)+1):
                nodedict[node] = set()
            numcons = sys.stdin.readline().strip()
            for con in range(int(numcons)):
                node1, node2 = sys.stdin.readline().split()
                n1, n2 = int(node1), int(node2)
                nodedict[n1].add(n2)
                nodedict[n2].add(n1)

            findgroups(nodedict, num_graph)

if __name__ == "__main__":
    main()
