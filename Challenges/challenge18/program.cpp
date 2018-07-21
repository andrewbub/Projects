// Andrew Bub CSE30872 - Challenge18: Passcode Cracking
// November 6, 2017
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Global Variables -----------------------------------------------------------------------------------
struct entry
{
	int first;
	int second;
	int third;
};

vector<entry> v;

// Prototypes -----------------------------------------------------------------------------------------
void Kahn();

// Main Execution -------------------------------------------------------------------------------------
int main()
{
	string n;
	entry e;

	// Read input into edge struct and add to vector
	while(cin >> n)
	{
		e.first = n[0] - '0';
		e.second = n[1] - '0';
		e.third = n[2] - '0';

		v.push_back(e);
	}

	Kahn(); // Implement Kahn's Algorithm

	v.clear();

	return 0;
}

// Functions -------------------------------------------------------------------------------------------
void Kahn()
{
	map<int, int> Degrees;
	vector<int> Results;
	vector<int> Frontier;
	map<int, int>::iterator it;	

	// Initialize Map to zero
	for(int i = 0; i < v.size(); i++)
	{
		Degrees[v[i].first] = 0;
		Degrees[v[i].second] = 0;
		Degrees[v[i].third] = 0;
	}

	// Calculate Initial Degrees
	for(int i = 0; i < v.size(); i++)
	{
		Degrees[v[i].second] += 1;
		Degrees[v[i].third] += 1;
	}

	// Add initial elements to Frontier
	for(it = Degrees.begin(); it != Degrees.end(); it++)
	{
		if(it->second == 0)
			Frontier.push_back(it->first);
	}
	

	while(! Frontier.empty())
	{
		// add first element of Frontier to Results
		Results.push_back(Frontier[0]);

		// Erase element added to Results from Degrees
		it = Degrees.find(Frontier[0]);
		Degrees.erase(it);

		// Update Degrees
		for(int i = 0; i < v.size(); i++)
		{
			if(v[i].first == Frontier[0])
				Degrees[v[i].second] -= 1;
			else if(v[i].second == Frontier[0])
				Degrees[v[i].third] -= 1;
		}

		// Pop Frontier
		if(! Frontier.empty())
			Frontier.pop_back();

		// Add new elements with degree 0 to Frontier
		for(it = Degrees.begin(); it != Degrees.end(); it++)
		{
			if(it->second == 0)
				Frontier.push_back(it->first);
		}
	}

	// Display Solution
	for(int i = 0; i < Results.size(); i++)
	{
		cout << Results[i];
	}
	cout << endl;
}
