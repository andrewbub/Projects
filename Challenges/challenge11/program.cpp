// Andrew Bub CSE30872 - Challenge11: Kakamora
// October 3, 2017

#include <iostream>
#include <stack>
#include <string.h>

using namespace std;

// Parameters -----------------------------------------------------------
void compute(int); // Compute Kakamore table
int minimum(int, int, int); // find minimum for path
void fill(int); // fill stack of path
void display(int);


// Global Variables ------------------------------------------------------
int G[101][101]; // Grid
int K[101][101]; // Kakamora Table
stack<int> PATH; // Recorded path taken


// Main Execution --------------------------------------------------------
int main()
{
	int N;
	int entry;

	cin >> N;

	while(N != 0)
	{
		memset(G, 0, sizeof(G)); // reset grid to 0's

		for(int r = 1; r <= N; r++)
		{
			for(int c = 1; c <= N; c++)
			{
				cin >> entry;
				G[r][c] = entry; // fill in grid with entries
			}
		}

		compute(N);
		fill(N);
		display(N);

		cin >> N; // read in the next N
	}

	return 0;
}


// Functions -------------------------------------------------------------
void compute(int N)
{
	int r, c;

	memset(K, 0, sizeof(K)); // reset Kakamora table to 0's

	for(r = 1; r <= N; r++)
	{
		for(c = 1; c <= N; c++)
		{
			if(r == 1 && c == 1) // NorthWest corner
			{
				K[r][c] = G[r][c];
				continue;
			}
			else if(r == 1) // Nothern most row
			{
				K[r][c] = minimum(K[r][c-1], K[r][c-1], K[r][c-1]) + G[r][c];
				continue;
			}
			else if(c == 1) // Western most column
			{
				K[r][c] = minimum(K[r-1][c], K[r-1][c], K[r-1][c]) + G[r][c];
				continue;
			}
			else
				K[r][c] = minimum(K[r-1][c], K[r][c-1], K[r-1][c-1]) + G[r][c];
		}
	}
}

int minimum(int S, int E, int SE) // read in as South, East, and Southeast
{
	int least = 0;

	if(E <= S)
		least = E;
	else
		least = S;

	if(least > SE)
		least = SE;

	return least;
}

void fill(int N)
{
	int r = N;
	int c = N;

	PATH.push(G[N][N]); // add SouthEast corner to stack

	while(!(r == 1 && c == 1)) // trace the path backwards into the stack
	{
		if(K[r][c-1] == (K[r][c] - G[r][c])) // if path goes horizontal
		{
			PATH.push(G[r][c-1]);
			c -= 1;
			continue;
		}

		if(K[r-1][c] == (K[r][c] - G[r][c])) // if path goes verticle
		{
			PATH.push(G[r-1][c]);
			r -= 1;
			continue;
		}

		if(K[r-1][c-1] == (K[r][c] - G[r][c])) // if path goes diagonal
		{
			PATH.push(G[r-1][c-1]);
			r -= 1;
			c -= 1;
			continue;
		}
	}
}

void display(int N)
{
	cout << K[N][N] << endl; // display number of Kakamora
	while(PATH.size() > 1)
	{
		cout << PATH.top() << " "; // display path with space between each step
		PATH.pop();
	}
	cout << PATH.top() << endl; // display last step with new line after
	PATH.pop();
}
