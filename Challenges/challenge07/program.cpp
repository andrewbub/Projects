// Andrew Bub CSE30872 - Challenge07: Atypical Division
// November 4, 2017
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// Global Variables ------------------------------------------------------------------------------------------------
int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // array of all digits
vector< pair<int, int> > perms[100]; // vector of all divisible permutations for numbers (index)
int numer, denom; // numerator and denominator for permutations 

// Prototypes ------------------------------------------------------------------------------------------------------
void fill_perms();

// Main Execution --------------------------------------------------------------------------------------------------
int main()
{
	int N;
	bool first = true;
	
	fill_perms();

	cin >> N; // read in first N

	while(N != 0)
	{
		if(! first)
			cout << endl; // blank line after every iteration except last

		if(perms[N].size() == 0) // if no permutations for N
			cout << "There are no solutions for " << N << "." << endl;
		else{
			for(int i = 0; i < perms[N].size(); i++)
			{
				cout << perms[N][i].first << " / ";
				if(perms[N][i].second < 10000) // display leading 0 if necessary
					cout << "0" << perms[N][i].second << " = " << N << endl;
				else
					
					cout << perms[N][i].second << " = " << N << endl;
			}
		}
		
		first = false;
		cin >> N; // read in N for next cycle
	}

	return 0;
}

// Functions -------------------------------------------------------------------------------------------------------
void fill_perms()
{
	do{
		numer = nums[0]*10000 + nums[1]*1000 + nums[2]*100 + nums[3]*10 + nums[4];
		denom = nums[5]*10000 + nums[6]*1000 + nums[7]*100 + nums[8]*10 + nums[9];

		if(numer % denom == 0) // if numer / denom is whole number
			perms[numer/denom].push_back(make_pair(numer,denom));
	}while(next_permutation(nums, nums+10)); // go through all permutations
}
