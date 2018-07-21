// Andrew Bub, RJ Stempak, Nick Ribera
// CSE30872 - ChallengeIIC: Matching Permutations
// December 4, 2017

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string A, B; // input strings
	vector<char> S; // solution string

	while(cin >> A >> B)
	{
		// alphabetize input string chars
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());

		if(A.size() < B.size()) // want smaller string on outer for loop
		{
			for(int i = 0; i < A.size(); i++)
			{
				for(int j = 0; j < B.size(); j++)
				{
					if(A[i] == B[j])
					{
						S.push_back(A[i]);
						break;
					}
				}
			}
		} else {
			for(int i = 0; i < B.size(); i++)
			{
				for(int j = 0; j < A.size(); j++)
				{
					if(B[i] == A[j])
					{
						S.push_back(B[i]);
						break;
					}
				}
			}
		}

		// output
		for(int i = 0; i < S.size(); i++)
		{
			cout << S[i];
		}
		cout << endl;

		S.clear(); // clear vector for next cycle
	}

	return 0;
}
