// Andrew Bub CSE3072 - Challenge05: Collatz Conjecture
// October 6, 2017
#include <iostream>
#include <map>

using namespace std;

// Global Variables ----------------------------------------------------------
map<unsigned int, unsigned int> CYCLE_LENGTHS;
unsigned int length;

// Prototypes ----------------------------------------------------------------
unsigned int cycle_length(unsigned int);


// Main Execution -----------------------------------------------------------
int main()
{
	unsigned int i, j;
	unsigned int start, end;
	unsigned int cycle;
	unsigned int max_cycle;

	while(cin >> i >> j)
	{
		// start at the greater number
		if(i < j)
		{
			start = j;
			end = i;
		} else {
			start = i;
			end = j;
		}

		for(unsigned int c = start; c >= end; c--)
		{
			cycle = cycle_length(c);
			if(cycle > max_cycle)
				max_cycle = cycle;
		}

		cout << i << " " << j << " " << max_cycle << endl;

		// Reset variables	
		cycle = 0;
		max_cycle = 0;
		length = 0;	
	}

	return 0;
}


// Functions ----------------------------------------------------------------
unsigned int cycle_length(unsigned int n)
{
	if(n == 1)
		return 1;
	
	if(CYCLE_LENGTHS.find(n) == CYCLE_LENGTHS.end()) // if n not in map
	{
		if(n % 2 == 1)
			length = cycle_length(3*n + 1) + 1;
		else
			length = cycle_length(n/2) + 1;

		CYCLE_LENGTHS[n] = length; // add element to map
	}

	return CYCLE_LENGTHS[n];
}
