// Andrew Bub CSE30872 - ChallengeIF: Rubles
// November 11, 2017
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Global Variables -------------------------------------------------------------------------------------------------
vector<unsigned long> money;

// Prototypes -------------------------------------------------------------------------------------------------------
int ways(unsigned long); // dynamic programming to cache partial solutions

// Main Execution ----------------------------------------------------------------------------------------------------
int main()
{
	float n; // amount of money
	unsigned long N;
	unsigned long w; // number of different ways to form amount

	// Fill vector with the different money values
	money.push_back(10000);
	money.push_back(5000);
	money.push_back(1000);
	money.push_back(500);
	money.push_back(200);
	money.push_back(100);
	money.push_back(50);
	money.push_back(10);
	money.push_back(5);
	
	while(cin >> n)
	{
		N = n*100; // multiply by 100 to get rid of decimal
		w = ways(N);
		cout << setw(6) << fixed <<  setprecision(2) << n << setw(16) << w << endl;
	}
	return 0;
}

// Functions ---------------------------------------------------------------------------------------------------------
int ways(unsigned long N)
{
	unsigned long matrix[money.size() + 1][N+1];

	// For amounts of 0.00, there is only 1 way to make 0.00
	for(unsigned long i = 0; i <= money.size(); i++)
	{
		matrix[i][0] = 1;
	}

	// For no coins, there are no ways
	for(unsigned long i = 1; i <= N; i++)
	{
		matrix[0][i] = 0;
	}

	// For all other combinations
	for(unsigned long i = 1; i <= money.size(); i++)
	{
		for(unsigned long j = 1; j <= N; j++)
		{
			if(money[i-1] <= j) // if money amount is less than amount
			{
				matrix[i][j] = matrix[i-1][j] + matrix[i][j - money[i-1]]; // update minus money amount
			} else {
				matrix[i][j] = matrix[i-1][j]; // same amount as previous 
			}
		}
	}

	return matrix[money.size()][N];
}
