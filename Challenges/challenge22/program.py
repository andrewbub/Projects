# Andrew Bub CSE30872 - Challenge22: Counting
# November 21, 2017
<<<<<<< HEAD
=======
# Only time I've used Python since big integers too difficult in C++
>>>>>>> 053da740f59213d1e6e81423a57aee5f4fe5fb15
import sys

M = range(1001) # allows for memoization

# Recurrence Relation:
# f[1] = 2; (1 and 4)
# f[2] = 5; (11, 14, 41, 44, and 2)
# f[3] = 13; (111, 114, 141, 144, 411, 414, 441, 444, 21, 24, 12, 14, and 3)
# Therefore, f[n] = 2(f[n-1) + f[n-2] + f[n-3]

# Base case for memoization
M[1] = 2
M[2] = 5
M[3] = 13

# Rest of memoization
for i in range(4, 1001):
	M[i] = (2*M[i-1] + M[i-2] + M[i-3])

# Read input and output answer
for n in sys.stdin:
	n = int(n)
	print M[n]
