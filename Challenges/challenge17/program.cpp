// Andrew Bub CSE30872 - Challenge17: Sim City
// November 5, 2017
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

// Global Variables ----------------------------------------------------------------------------------------------
vector< pair<double, double> > LOCS; // locations of buildings

struct edge {
	double weight; // road distance
	pair<double, double> source;
	pair<double, double> target;

	bool operator<(const edge &e) const // overload less than operator to make MIN priority_queue
	{
		return (weight > e.weight);
	}
};

// Prototypes ----------------------------------------------------------------------------------------------------
double Prims(); // Implements Prim's Algorithm for Minimum Spanning Tree
double dist(pair<double, double>, pair<double, double>); // calculates euclidean distance between 2 points

// Main Execution ------------------------------------------------------------------------------------------------
int main()
{
	int N; // number of buildings
	double x, y; // x and y coordinates of location
	double total;

	while(cin >> N)
	{
		if(N == 0)
			break;

		// Read in input
		for(int i = 0; i < N; i++)
		{
			cin >> x >> y;
			LOCS.push_back(make_pair(x, y)); // add building location to LOCS
		}

		total = Prims(); // get MST total road distance

		cout << setprecision(2) << fixed << total << endl; // display with 2 decimal places

		LOCS.clear(); // reset LOCS for next cycle
	}

	return 0;
}

// Functions ----------------------------------------------------------------------------------------------------
double Prims()
{
	priority_queue<edge> frontier;
	map< pair<double, double>, pair<double, double> > marked;

	double total = 0;
	edge v;
	edge u;

	v.weight = 0;
	v.source = LOCS[0];
	v.target = LOCS[0];

	frontier.push(v);

	while(! frontier.empty())
	{
		v = frontier.top();
		frontier.pop();

		if(marked.find(v.target) != marked.end()) // if v.target in marked
			continue;

		marked[v.target] = v.source;
		total += v.weight;
	
		for(int i = 0; i < LOCS.size(); i++)
		{
			if(dist(v.target, LOCS[i])) // if source and target are not the same location
			{
				u.weight = dist(v.target, LOCS[i]);
				u.source = v.target;
				u.target = LOCS[i];
				frontier.push(u); // add possible paths to all other buildings to frontier
			}
		}	
	}

	return total;
}

double dist(pair<double, double> source, pair<double, double> target)
{
	double a = source.first - target.first;
	double b = source.second - target.second;

	// a^2 + b^2 = c^2
	double c = pow(a, 2) + pow(b, 2);
	c = sqrt(c);

	return c;
}
