// Andrew Bub CSE30872 - Challenge16: Path Finding
// November 1, 2017
#include <iostream>
#include <utility>
#include <map>
#include <stack>
#include <queue>

using namespace std;

// Global Variables ----------------------------------------------------------------------------------------------------------------------
struct edge {
	int cost; // weight
	pair<int, int>  name; // coordinate
	pair<int, int> prev; // previous coordinate

	bool operator<(const edge &e) const // overload less than operator to make MIN priority_queue
	{
		return (cost > e.cost);
	}
};

map<char, int> CODE; // Use to decode given map from letters to number weights
stack< pair<int, int> > PATH; // path of edges traveled


// Main Execution -------------------------------------------------------------------------------------------------------------------------
int main()
{
	int tiles; // number of different tiles
	char tile_name; // individual tile names
	int tile_cost; // individual tile costs
	int rows, cols; // number of rows and columns in the graph
	char t; // individual tile
	int start_row, start_col; // starting row and column coordinates
	int end_row, end_col; // ending row and column coordinates
	pair<int, int> start; // starting coordinate
	pair<int, int> end; // ending coordinate

	while(cin >> tiles)
	{
		// Read in and Format Input -----------------------------------------------------------------------------------------------
		for(int i = 0; i < tiles; i++)
		{
			cin >> tile_name >> tile_cost;
			CODE[tile_name] = tile_cost; // add tile names and costs to CODE map
		}

		cin >> rows >> cols;

		int G[rows][cols]; // construct matrix of Graph
	
		// fill in matrix
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
			{
				cin >> t;
				G[r][c] = CODE[t];
				//cout << G[r][c] << " ";
			}
			//cout << endl;
		}
		//cout << endl;

		cin >> start_row >> start_col >> end_row >> end_col;

		start = make_pair(start_row, start_col);
		end = make_pair(end_row, end_col);


		// Implement Dijkastra's Algorithm ---------------------------------------------------------------------------------------
		priority_queue<edge> frontier;
		map< pair<int, int>, pair<int, int> > marked;

		edge v;
		edge u;

		v.cost = G[start.first][start.second];
		v.name = start;
		v.prev = start;

		frontier.push(v);

		while(! frontier.empty())
		{
			v = frontier.top();
			frontier.pop();

			if(marked.find(v.name) != marked.end()) // if v.name in marked
				continue;

			marked[v.name] = v.prev;

			if(v.name == end) // break cycle if at destination
				break;

			if(v.name.second + 1 < cols) // if theres a edge to the East
			{
				u.cost = v.cost + G[v.name.first][v.name.second + 1];
				u.name = make_pair(v.name.first, v.name.second + 1);
				u.prev = v.name;
				frontier.push(u);
			}

			if(v.name.first - 1 >= 0) // if theres a edge to the South
			{
				u.cost = v.cost + G[v.name.first - 1][v.name.second];
				u.name = make_pair(v.name.first - 1, v.name.second);
				u.prev = v.name;
				frontier.push(u);
			}

			if(v.name.second - 1 >= 0) // if theres a edge to the West
			{
				u.cost = v.cost + G[v.name.first][v.name.second - 1];
				u.name = make_pair(v.name.first, v.name.second - 1);
				u.prev = v.name;
				frontier.push(u);
			}

			if(v.name.first + 1 < rows) // if theres a edge to the North
			{
				u.cost = v.cost + G[v.name.first + 1][v.name.second];
				u.name = make_pair(v.name.first + 1, v.name.second);
				u.prev = v.name;
				frontier.push(u);
			}
		}


		// Display Total and Path -------------------------------------------------------------------------------------------------
		pair<int, int> curr = end;
		int total = 0; // total cost of path

		while(curr != start) // add edge to path's stack from end to start
		{
			PATH.push(curr);
			curr = marked[curr];
			total += G[curr.first][curr.second]; // add cost to total
		}

		PATH.push(curr); // add starting edge to path

		cout << total << endl;
		while(! PATH.empty())
		{
			cout << PATH.top().first << " " << PATH.top().second << endl;
			PATH.pop();
		}


		// Reset for next cycle ---------------------------------------------------------------------------------------------------
		marked.clear();
		CODE.clear(); // clear CODE map for next cycle
	}

	return 0;
}
