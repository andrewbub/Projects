// Andrew Bub CSE30872 - Challenge08: Illuminati
// November 4, 2017
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Global Variables -------------------------------------------------------------------------------------------------
const int TARGET = 13;
vector<int> TUPLE;
bool possible;

// Prototypes -------------------------------------------------------------------------------------------------------
bool calc(int, long); // recursively calculate all possible TUPLE permutations

// Main Execution ---------------------------------------------------------------------------------------------------
int main()
{
	string line;
	int n;

	while(getline(cin, line)) // read in line-by-line
	{
		stringstream ss;
		ss.str(line);

		while(ss >> n)
		{
			TUPLE.push_back(n); // vector allows for different length of tuples
		}

		sort(TUPLE.begin(), TUPLE.end()); // sort TUPLE for permutation calculation

		possible = false;

		do{
			if(calc(1, TUPLE[0]))
			{
				possible = true;
				break;
			}
		} while(next_permutation(TUPLE.begin(), TUPLE.end())); // brute force try all permutations for calculations

		if(possible)
			cout << "Illuminati!" << endl;
		else
			cout << "Nothing to see" << endl;
	
		TUPLE.clear(); // clear TUPLE for next iteration
	}

	return 0;
}


// Functions --------------------------------------------------------------------------------------------------------
bool calc(int n, long t)
{
	if(n == TUPLE.size()) // if all elements of TUPLE are accounted for
	{
		if(t == TARGET) // if calculation == 13
			return true;
		else
			return false;
	}

	// recursively try all allowed operations for every permutation
	return calc(n+1, t + TUPLE[n]) || calc(n+1, t - TUPLE[n]) || calc(n+1, t*TUPLE[n]);
}
