// Andrew Bub CSE30872 - Challenge15: The Longest Road
// October 29, 2017
#include <iostream>
#include <string.h>

using namespace std;

// Global Variables ------------------------------------------------------------------------------------
int n; // number of nodes
int m; // number of edges
int longest; // solution for the longest path
int adj[25][25]; // adjacency matrix for graph


// Prototypes ------------------------------------------------------------------------------------------
void find_longest(int, int); // find longest path by walking graph in DFS


// Main Execution -------------------------------------------------------------------------------------
int main()
{
	int source, destin;

	cin >> n >> m;

	while(n != 0 && m != 0)
	{
		memset(adj, 0, sizeof(adj)); // initialize all adj elements to 0

		for(int i = 0; i < m; i++)
		{
			cin >> source >> destin;
			adj[source][destin] = 1;
			adj[destin][source] = 1; // because graph is undirected
		}

		longest = 0;

		for(int i = 0; i < n; i++)
		{
			find_longest(i, 0); // search for longest path from each node
		}

		cout << longest << endl;

		cin >> n >> m; // read in n and m for next cycle
	}

	return 0;
}

// Functions -----------------------------------------------------------------------------------------
void find_longest(int node, int length)
{
	if(length > longest)
		longest = length; // update longest
	
	for(int i = 0; i < n; i++)
	{
		if(adj[node][i])
		{
			adj[node][i] = 0;
			adj [i][node] = 0;
			
			find_longest(i, length + 1); // search for next node in path; length increases by 1

			adj[node][i] = 1;
			adj[i][node] = 1;
		}
	}
}
