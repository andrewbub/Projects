// Andrew Bub CSE30872 - ChallengeIB: Isomorphic Mapping
// November 11, 2017
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Prototypes --------------------------------------------------------------------------------------------------
bool iso(string, string); // determines if isomorphic

// Main Execution ----------------------------------------------------------------------------------------------
int main()
{
	string line;
	string s, t;
	bool b;

	while(getline(cin, line))
	{
		// Read in the 2 words
		stringstream ss;
		ss.str(line);

		ss >> s;
		ss >> t;

		// Determine if Isomorphic
		if(s.length() != t.length()) // if different lengths, not isomorphic
		{
			b = false;
		} else {
			b = iso(s, t);
		}

		// Dislpay Result
		if(b)
		{
			cout << "Isomorphic" << endl;
		} else {
			cout << "Not Isomorphic" << endl;
		}
	}

	return 0;
}

// Function -------------------------------------------------------------------------------------------------
bool iso(string s, string t)
{
	int map_s[256] = {0}; // initialize all letter counts to 0
	int map_t[256] = {0}; // initialize all letter counts to 0

	for(int i = 0; i < s.length(); i++)
	{
		if(map_s[s[i]] != map_t[t[i]]) // if the letter at i does not map from s to t
			return false;

		map_s[s[i]] = i + 1; // update s map
		map_t[t[i]] = i + 1; // update t map
	}

	return true;
}
