// Andrew Bub CSE30872 - Challenge20: Maximum Bandwith
// November 14, 2017
// Finds Max Flow using Edmonds-Karp Algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

// Global Variables -------------------------------------------------------------------------------------
int N, S, T, C; // number of nodes, source, target, number of connections
int flow, MB; // flow and Maximum Bandwith
int network[101][101]; // matrix representing network graph
vector<int> path; // store connection taken to get to each node

// Prototypes -------------------------------------------------------------------------------------------
void get_flow(int, int);

// Main Execution ---------------------------------------------------------------------------------------
int main()
{
	int s, t, w; // individual source, target, and weight
	int net = 1; // Network Number

	while(cin >> N)
	{
		if(N == 0) // input ends when N == 0
			break;

		// Initialize MB and network matrix to 0
		MB = 0;
		memset(network, 0, sizeof(network));

		cin >> S >> T >> C;
		S--;
		T--;

		for(int i = 0; i < C; i++) // fill matrix with network info
		{
			cin >> s >> t >> w;
			s--;
			t--;

			// since multiple connections between nodes possible, sum weights
			network[s][t] += w;
			network[t][s] += w; // since connection bi-directional
		}

		while(1) // BFS to find the shortest S-T path
		{
			flow = 0;
			vector<int> dist(N, INT_MAX);
			dist[S] = 0; // distance from source is 0
			queue<int> q;
			q.push(S);
			path.assign(N, -1); // reset all connections in path to -1

			while(!q.empty())
			{
				int u = q.front();
				q.pop();
				if(u == T)
					break;
				for(int i = 0; i < N; i++)
				{
					if(network[u][i] > 0 && dist[i] == INT_MAX)
					{
						dist[i] = dist[u] + 1;
						q.push(i);
						path[i] = u;
					}
				}
			}

			get_flow(T, INT_MAX);

			if(flow == 0) // when no more paths with flow to add
				break;

			MB += flow;
		}
		cout << "Network " << net << ": Bandwidth is " << MB << "." << endl;
		net++;
	}

	return 0;
}

// Functions --------------------------------------------------------------------------------------------
void get_flow(int n, int min_flow)
{
	if(n == S) // if current node is the Source
	{
		flow = min_flow; // flow for path is min of all weights
		return;
	} else if(path[n] != -1) {
		get_flow(path[n], min(min_flow, network[path[n]][n])); // recurse
		network[path[n]][n] -= flow; // update path connection weight
		network[n][path[n]] += flow; // update reverse connection weight
	}
}
