// Andrew Bub CSE 30872 - Challenge12: Russell's Chocolate
// October 5, 2017
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Global Variables --------------------------------------------------------------------------------------
vector<int>  wt, yum; // to store weight and yumminess of individual bars
int TOT_Y; // total yummines
vector< vector<int> > T; // dynamic Table
vector< pair<int, int> > PICKED; // selected bars

// Prototypes --------------------------------------------------------------------------------------------
int fill(int, int); // fill the dynamic Table and calculate max yumminess
void pick(int, int); // pick the individual bars
void display();
int max(int, int);


// Main Execution ----------------------------------------------------------------------------------------
int main()
{
	int weight, num; // max weight and number of possible bars
	int w, y; // individual weight and yumminess
	
	cin >> weight >> num;
	while(!(weight == 0 && num == 0))
	{
		TOT_Y = 0; // reset total yumminess

		// read-in weights and yumminess of all bars
		for(int i = 0; i < num; i++)
		{
			cin >> w >> y;
			wt.push_back(w);
			yum.push_back(y);
		}

		TOT_Y = fill(weight, num);
		sort(PICKED.begin(), PICKED.end()); // bars ordered by increasing weight
		display();

		// deallocate global variables
		PICKED.clear();
		wt.clear();
		yum.clear();
		T.clear();

		cin >> weight >> num; // read in the next max and num
	}

	return 0;
}


// Functions ---------------------------------------------------------------------------------------------
int fill(int w, int n)
{
	T.resize(n+1, vector<int>(w + 1, 0));
	
	// Build table bottom-up
	for(int r = 1; r <= n; r++)
	{
		for(int c = 1; c <= w; c++)
		{
			if(wt[r] > c)
				T[r][c] = T[r-1][c];
			else
				T[r][c] = max(T[r-1][c], yum[r] + T[r-1][c-wt[r]]);
		}
	}

	pick(n, w);

	return T[n][w];
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void pick(int n, int w)
{
	if (n <= 0 || w <= 0) return;

	int k = T[n][w];
	if (k != T[n - 1][w])
	{
		PICKED.push_back(make_pair(wt[n], yum[n])); // pick the bar and add to knapsack
		pick(n - 1, w - wt[n]); // capacity decreases
	} else {
		// move on to next item; capacity no change
		pick(n - 1, w);
	}	
}

void display()
{
	cout << TOT_Y << endl;
	for(int i = 0; i < PICKED.size(); i++)
	{
		cout << PICKED[i].first << " " << PICKED[i].second << endl;
	}
}
