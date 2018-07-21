// Andrew Bub CSE30872 Challenge10 - Wendy's
// September 26, 2017

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

	int n; // n customers
	int t; // time t order was placed
	int d; // order takes d units of time to processs
	int num; // number in line the customer was

	vector< pair<int, int> > v; // vector of pairs to hold time and number in line

	while(cin >> n)
	{
		num = 1; // reset num

		while(n)
		{
			cin >> t >> d;
			
			v.push_back(make_pair((t+d), num)); // pair is total time and order in line
			
			num++; // increment to next customer in line
			n--;
		}

		sort(v.begin(), v.end()); // sort the vector to create the order

		for(int i = 0; i < v.size(); i++) // iterate through sorted vector
		{
			if(i != (v.size() - 1))
			{
				cout << v[i].second << " "; // display order
			
			} else
			{
				cout << v[i].second << endl; // new line instead of space if last in line
			}
		}


		v.clear(); // clear vector
	}

	return 0;
}

