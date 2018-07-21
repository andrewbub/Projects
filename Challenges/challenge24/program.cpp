// Andrew Bub CSE30872 - Challenge24: Ant on a Chessboard
// November 20, 2017
#include <iostream>
#include <math.h>

using namespace std;

// Main Execution ------------------------------------------------------------------------------------------------
int main()
{
	int N;
	int r, c; // row, column

	int root, x;

	while(cin >> N)
	{
		root = ceil(sqrt(N)); // Square Root Relationship for Pattern
		x = (root * root) - root + 1; // helper variable for pattern position
		r = c = root;

		if(root % 2 == 0) // if root is even
		{
			if(N > x)
			{
				r -= (N-x);
			} else {
				c -= (x-N);
			} 
		}else { // if root is odd
			if(N > x)
			{
				c -= (N-x);
			} else {
				r -= (x-N);
			}
		}

		cout << N << " = (" << r << ", " << c << ")" << endl;
	}

	return 0;
}

