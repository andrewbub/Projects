// Andrew Bub CSE30872 - ChallengeIE: Binary Strings
// November 11, 2017
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Global Variables ----------------------------------------------------------------------------------------------
vector<int> B_STRING;

// Prototypes ----------------------------------------------------------------------------------------------------
void perms(int); // calculates and outputs all permutations of binary strings

// Main Execution ------------------------------------------------------------------------------------------------
int main()
{
	int N, K; // length N, with K 1's
	bool first = true;

	while(cin >> N >> K)
	{
		// output blank line between cases
		if(!first)
			cout << endl;

		// fill B_STRING vector
		for(int i = 0; i < N; i++)
		{
			if(K)
			{
				B_STRING.push_back(1);
				K--;
			} else {
				B_STRING.push_back(0);
			}
		}

		sort(B_STRING.begin(), B_STRING.end()); // sort vector for next_permutation

		perms(N); // find and display all permutations

		first = false;
		B_STRING.clear(); // clear vector for next cycle

		
	}
	return 0;
}

// Functions -----------------------------------------------------------------------------------------------------
void perms(int N)
{
	do {
		for(int i = 0; i < N; i++)
		{
			cout << B_STRING[i];
		}
		cout << endl;

	}while(next_permutation(B_STRING.begin(), B_STRING.end()));
}
