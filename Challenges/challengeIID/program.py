# Andrew Bub, RJ Stempak, Nick Ribera
#challenge contest2E
import sys

def longest_morph(word_list):
    #build adjacency list
    for word in word_list:
        for next_word in word_list:
            if is_diff_one(word, next_word) and word != next_word:
                word_list[word].append(next_word)
    longest_path = []
    for word in sorted(word_list):
        new_path = DFS(word_list, word)
        if len(longest_path) < len(new_path):
            longest_path = new_path
    return len(longest_path), longest_path

def is_diff_one(origin_word, next_word):
    #if more than one char off then definite false
    if abs(len(origin_word) - len(next_word)) > 1:
        return False

    differences = 0
    if len(origin_word) <= len(next_word):
        for i in range(len(origin_word)):
            if origin_word[i] != next_word[i]:
                differences+=1
    else:
        for i in range(len(next_word)):
            if origin_word[i] != next_word[i]:
                differences+=1

    if differences > 1:
        return False

    return True

def DFS(graph, start):
    visited = [start]
    stack = [v for v in sorted(graph[start]) if v not in visited]

    while stack:
        vertex = stack.pop()
        if vertex not in visited and vertex < visited[-1]:
            visited.append(vertex)

            #stack becomes all unvisited neighbors of vertex
            stack = [v for v in sorted(graph[vertex]) if v not in visited]

    #longest DFS path
    return visited[::-1]


def main():
    word_list = {}
    for word in sys.stdin:
        word_list[word.strip()] = []

    longest_morph(word_list)
    length, word_chain = longest_morph(word_list)

    #output
    print length
    for word in word_chain:
        print word
if __name__ == "__main__":
    main()
