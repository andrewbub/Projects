// Andrew Bub CSE30872 - Challenge06: Longest Distinct Sequence
// October 13, 2017
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

using namespace std;

// Global Variables -----------------------------------------------------------
vector<string> FRUITS; // input of all fruits
set<string> SEQ; // sequence of non-repeating fruits

// Prototypes -----------------------------------------------------------------
int find_longest();

// Main Execution -------------------------------------------------------------
int main()
{
	string line; // line of input
	string fruit; // individual fruit
	int longest;

	while(getline(cin, line))
	{
		istringstream iss;
		iss.str(line);

		while(iss >> fruit)
		{
			FRUITS.push_back(fruit); // add input to the vector
		}

		longest = find_longest();

		cout << longest << endl;

		FRUITS.clear();
	}

	return 0;
}

// Functions ------------------------------------------------------------------
int find_longest()
{
	int longest = 0;
	int start = 0;

	while(start < FRUITS.size())
	{
		for(int i = start; i < FRUITS.size(); i++) // start at increasing fruit in vector and end when repeated 
		{
	//		cout << "start: " << start << " spot: " << i << " fruit: " << FRUITS[i] << endl;
			if(SEQ.count(FRUITS[i]) == 0)
			{
				SEQ.insert(FRUITS[i]); // add fruit to set if a new fruit
				if(i == FRUITS.size() - 1)
				{
					if(SEQ.size() > longest)
						longest = SEQ.size();
					SEQ.clear();
					start++;
					break;
					
				}
			
			} else { // repeated fruit
				if(SEQ.size() > longest)
					longest = SEQ.size(); // update longest sequence of non-repeating fruit
				SEQ.clear();
				start++;
				break;
			}
		}
	}

	return longest;
}
