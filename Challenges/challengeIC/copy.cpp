// Andrew Bub CSE30872 - ChallengeIC: Permutation Swap
// November 11, 2017
#include <iostream>
#include <vector>

using namespace std;

// Global Variables -------------------------------------------------------------------------------
vector<int> NUMS;

// Prototypes -------------------------------------------------------------------------------------
void swap(int, int);
void display();

// Main Execution ---------------------------------------------------------------------------------
int main()
{
	int N, K;
	int n;

	while(cin >> N >> K)
	{
		for(int i = 0; i < N; i++)
		{
			cin >> n;
			NUMS.push_back(n);
		}

		swap(N, K);
		display();

		NUMS.clear();
	}

	return 0;
}

// Functions ---------------------------------------------------------------------------------------
void swap(int N, int K)
{
	int pos = 0; // starting position
	int pG; // position of Greatest num
	int G; // greatest number
	int S; // num to be swapped
	int loop = 0; // number of times through loop

	while(K > 0)
	{
		loop++;

		G = NUMS[pos];
		pG = pos;
		S = NUMS[pos];

		for(int i = pos; i < N; i++)
		{
			if(NUMS[i] > G) // find greatest number and its position
			{
				G = NUMS[i];
				pG = i;
			}
		}

		if(S == G) // if Greatest is already at starting position
		{
			pos++;

			if(loop > N)
			{
				break;
			} else {
				continue;
			}
		}

		NUMS[pos] = G;
		NUMS[pG] = S;

		pos++;
		K--;
	}
}

void display()
{
	for(int i = 0; i < NUMS.size(); i++)
	{
		if(i != NUMS.size() -1)
			cout << NUMS[i] << " ";
		else
			cout << NUMS[i];
	}
	cout << endl;
}
