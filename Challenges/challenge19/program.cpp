// Andrew Bub CSE30872 - Challenge19: Hamiltonian Cycle
// November 12, 2017
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Global Variables ----------------------------------------------------------------------------------------
map< int, set<int> > EDGES; // maps node to the set of all nodes it shares an edge with

// Prototypes ----------------------------------------------------------------------------------------------
bool dfs(int, vector<int> &, set<int> &); // DFS to traverse graph, finding cycle

// Main Execution ------------------------------------------------------------------------------------------
int main()
{
	unsigned int n; // n vertices
	int x, y; // edge exists between nodes a and b
	char c;

	vector<int> marked; // nodes in path of current cycle
	set<int> frontier; // unvisited nodes
	bool b;

	while(cin >> n)
	{
		while(cin >> x >> y)
		{
			EDGES[x].insert(y);
			EDGES[y].insert(x); // since undirected graph
		}

		cin.clear();
		cin >> c; // capture the % terminating the graph

		for(int i = 1; i <= n; i++)
		{
			frontier.insert(i); // add all nodes to frontier
		}

		// Push starting node onto marked and remove from frontier
		marked.push_back(1);
		frontier.erase(1);

		b = dfs(n, marked, frontier);

		if(b) // if Hamiltonian Cycle Exists
		{
			for(int i = 0; i < marked.size(); i++)
			{
				if(i != marked.size() - 1)
				{
					cout << marked[i] << " ";
				} else {
					cout << marked[i] << endl;
				}
			}
		} else { // if no Hamiltonian Cycle Exists
			cout << "None" << endl;
		}

		// Reset for next cycle
		EDGES.clear();
		marked.clear();
		frontier.clear();
	}

	return 0;
}

// Functions -------------------------------------------------------------------------------------------------
bool dfs(int n, vector<int> &marked, set<int> &frontier)
{
	if(frontier.empty()) // if all nodes have been visited
	{
		if(EDGES[marked.back()].find(1) != EDGES[marked.back()].end()) // if starting node is last node
		{
			marked.push_back(1);
			return true;
		} else {
			return false;
		}
	} else { // find path to all other unvisited nodes
		set<int> buffer = frontier;
		for(set<int>::iterator it = frontier.begin(); it != frontier.end(); it++)
		{
			if(EDGES[marked.back()].find(*it) != EDGES[marked.back()].end()) // if node in marked
			{
				buffer.erase(*it); // remove from new frontier
				marked.push_back(*it); // add node to marked
				if(dfs(n, marked, buffer)) // recurse
					return true;

				marked.pop_back();
				buffer.insert(*it);
			}
		}
		return false;
	}
} 
