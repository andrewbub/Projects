Challenge IIB: Matrix

Given an M x N matrix of integers, write a program that computes a path of minimal weight from left to right across the matrix. A path starts anywhere in column 1 and consists of a sequence of steps terminating in column N. Each step consists of traveling from column I to column I + 1 in an adjacent (horizontal or diagonal) row. The first and last rows (rows 1 and M) of a matrix are considered adjacent (i.e. the matrix wraps so that it represents a horizontal cylinder).

Given matrices, you are to output the minimum weight followed by the minimum path (i.e. the row to take for the corresponding columns).

Input:
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 8 6 4
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 1 2 3
2 2
9 10
9 10

Output:
16
1 2 3 4 4 5
11
1 2 1 5 4 5
19
1 1
