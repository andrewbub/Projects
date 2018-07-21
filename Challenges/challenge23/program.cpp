// Andrew Bub CSE30872 - Challenge23: Paper Box
// November 20, 2017
#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>

using namespace std;

// Main Execution ----------------------------------------------------------------------------------------------
int main()
{
	double L, W; // Length and Width
	double MIN, MAX;;	

	while(cin >> L >> W)
	{
		// Calculate MAX and MIN
		MAX = (L + W - sqrt( (double)(L*L - L*W + W*W)))/6.0;
		MIN = (min(W,L)) * 0.5;

		// Display Results
		cout << fixed << setprecision(3) << MAX << " ";
		cout  << fixed << setprecision(3) << MIN << endl;
	}

	return 0;
}

