// Andrew Bub, RJ Stempak, Nick Ribera
// CSE30872 - ChallengeIIC: Matrix
// December 4, 2017
#include <iostream>

using namespace std;

// Global Variables -------------------------------------------------------------------------------------------------
int rows, cols; // rows, columns
bool traveled[100][10]; // graph showing which edges have been traveled 
int G[100][10]; // graph
int Cost[100][10]; // graph with costs
int Total[100][10]; // memoization for total costs

// Prototypes -------------------------------------------------------------------------------------------------------
int getCost(int, int); // recursively calculates and returns minimum cost of path

// Main Execution ---------------------------------------------------------------------------------------------------
int main()
{
	int v; // value of individual element of matrix

	while(cin >> rows >> cols)
	{
		// Fill Matrix
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
			{
				cin >> v;
				G[c][r] = v;
				traveled[c][r] = false; // initialize graph to all untraveled
			}
		}

		int Cost = 1e9, Start;

		for(int i = 0; i < rows; i++)
		{
			int cost = getCost(0, i);
			if(cost < Cost)
			{
				Start = i;
				Cost = cost;
			}
		}

		// Display results
		int current = Start;
		cout << Cost << endl;
		cout << current + 1;
		current = Total[0][current];
		int c = 1;
		while(c < cols)
		{
			cout << ' ' << (current + 1);
			current = Total[c][current];
			++c;
		}
		cout << endl;

	}

	return 0;
}

// Functions --------------------------------------------------------------------------------------------------------
int getCost(int c, int r)
{
	if(c == cols) // if location is furthest left column
		return 0;

	int &cost = Cost[c][r];

	if(!traveled[c][r]) // travel onto untraveled edges
	{
		traveled[c][r] = true;
		int &total = Total[c][r];
		total = (r - 1 + rows) % rows;
		cost = getCost(c + 1, total);

		int newCost = getCost(c + 1, r);
		if(newCost < cost || (newCost == cost && r < total))
		{
			cost = newCost;
			total = r;
		}

		int newR = (r+1) % rows;
		newCost = getCost(c + 1, newR);
		if(newCost < cost || (newCost == cost && newR < total))
		{
			cost = newCost;
			total = newR;
		}

		cost += G[c][r]; // update total cost on path
	}
	return cost;
}
