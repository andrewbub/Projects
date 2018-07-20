Homework 05 - Andrew Bub
===========
Prompt: https://www3.nd.edu/~pbui/teaching/cse.20289.sp17/homework05.html

ACTIVITY 1
1. I generated all the candidate password combinations by first creating a function that created all permutations of words and numbers
for the given length. Then I used a smash function which returned all password permutations of the specified length that were in hashes.
Then I used a md5sum function which took those permutations and hashes and genereated the MD5 digest for the string input.
I filtered the candidates to contain only valid passwords by calling the smash function, inputting the hashses given in the input file.
I handled processing on multiple cores by using an if else statement. If CORES == 1 and LENGTH == 1, the program only used one core. 
Else, the program would use the value of CORES for the number of cores. I verified that my code works properly by using the tes_hulk.sh
program, and it passed all the tests. 
2.	Processes	|	Time
	1		|	3 hours 18 minutes
	2		|	2 hours 41 minutes
	4		|	1 hour 46 minutes
	8		|	1 hour 12 minutes
	16		|	44 minutes
The number of processes utilized affected the amount of time required to crack the password, where the more processes, the less time
it took.
3. A longer password would make it more difficult to brute force hack, because it took a long time for the program to run to complete
for passwords of length 7 and 8 because there were so many permutations to create and check.

ACTIVITY 2
1. The iv_map.py script keeps track of line numbers by using the count variable. Every time through the for loop, which iterates every
line of the stdin, the value of count (which started at 1) increases by 1. It removes undesirable characters by using an if statement 
to only allow characters that are in the variable alphabet, which I defined to be letters, digits, whitespace, and the - character.
2. The iv_reduce.py script aggregates the results for each word by using a if else statment to create a set of the line numbers, if 
the word is already in the dictionary or not. It outputs the results in the correct format by usinga  for loop that creates a list of
the nums and prints the word followed by the list of the line numbers 


