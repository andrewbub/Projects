// Andrew Bub CSE30872 - Challenge04: Bear's Vents
// October 13, 2017
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// Global Variables -----------------------------------------------------------
vector<int> VENTS;
vector< pair<int, int> > DISTANCES;

// Prototypes ----------------------------------------------------------------
pair<int, int> calculate(int); // calculate distances and return ideal vent
void display(string, pair<int, int>);

// Main Execution ------------------------------------------------------------
int main()
{
	string room;
	int num; // number of vents
	int v; // individual vent
	pair<int, int> vent; // selected vent

	while(cin >> room >> num)
	{
		for(int i = 0; i < num; i++)
		{
			cin >> v;
			VENTS.push_back(v);
		}

		vent = calculate(num);
		display(room, vent);

		VENTS.clear();
		DISTANCES.clear();
	}

	return 0;
}

// Functions -----------------------------------------------------------------
pair<int, int> calculate(int num)
{
	int distance;
	for(int i = 0; i < num; i++)
	{
		distance = 0;

		for(int j = 0; j < num; j++)
		{
			if(VENTS[i] < VENTS[j])
				distance += (VENTS[j] - VENTS[i]);
			else
				distance += (VENTS[i] - VENTS[j]);
		}

		DISTANCES.push_back(make_pair(distance, VENTS[i]));
	}

	sort(DISTANCES.begin(), DISTANCES.end());

	return DISTANCES[0];
}

void display(string room, pair<int, int> vent)
{
	cout << room << " " << vent.second << " " << vent.first << endl;
}
