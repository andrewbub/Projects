// Andrew Bub CSE30872 - ChallengeID: Team Photo
// November 11, 2017
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// Global Variables ----------------------------------------------------------------------------------------
vector<int> Team1;
vector<int> Team2;

// Prototypes ----------------------------------------------------------------------------------------------
bool photo(vector<int>, vector<int>);

// Main Execution ------------------------------------------------------------------------------------------
int main()
{
	string line1;
	string line2;
	int n;
	bool b;

	while(getline(cin, line1))
	{
		getline(cin, line2);

		// Read in Team Players' Heights
		// Team1
		stringstream ss1;
		ss1.str(line1);
		while(ss1 >> n)
		{
			Team1.push_back(n);
		}

		// Team2
		stringstream ss2;
		ss2.str(line2);
		while(ss2 >> n)
		{
			Team2.push_back(n);
		}

		// Determine if all players on Team1 are shorter than someone on Team2
		b = photo(Team1, Team2);

		// Display Result
		if(b)
		{
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}

		// Reset for next cycle
		Team1.clear();
		Team2.clear();
	}

	

	return 0;
}

// Functions -----------------------------------------------------------------------------------------------
bool photo(vector<int> Team1, vector<int> Team2)
{
	// sort Teams by least to greatest height
	sort(Team1.begin(), Team1.end());
	sort(Team2.begin(), Team2.end());

	// Determine if photo can be taken with everyone on Team1 shorter than someone on Team2
	for(int i = 0; i < Team1.size(); i++)
	{
		if(Team1[i] >= Team2[i]) // if Team1 plater is same height or taller than the Team2 player
			return false;
	}

	return true;

}
