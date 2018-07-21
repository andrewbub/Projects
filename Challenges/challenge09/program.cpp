// Andrew Bub CSE30872 Challenge09 - LEGO Bricks
// September 25, 2017

#include <iostream>

using namespace std;

int main()
{
	int one, two, three, four; // variables for the 1-4x1 bricks
	int rows; // variable for the required rows

	while(cin >> one >> two >> three >> four)
	{
		rows = 0; // reset rows

		// FOUR
		rows = four; // greedy algorithm counts four first
		four = 0; // reset four

		// THREE
		rows += three; // count threes

		if((one - three) > 0) // fill in ones to pair with threes
		{
			one -= three; // leftover ones
		} else // no remaining ones
		{
			one = 0;
		}

		three = 0; // reset three

		// TWO
		while(two >= 2) // for every full row made by paird twos
		{
			rows += 1;
			two -= 2;
		}
		if(two) // remaining 1 two make a partial row
		{
			if(one >= 2) // add ones to make full row
			{
				one -= 2;
				rows += 1;
			}
			else // last remaining row
			{
				one = 0;
				rows += 1;
			}
		}

		two = 0; // reset two

		// ONE
		while(one >= 4) // for every full row made of leftover ones
		{
			rows += 1;
			one -= 4;
		}

		if(one)
		{
			rows += 1; // remaining ones make partial row
		}

		one = 0; // reset one

		cout << rows << endl;
	}

	return 0;
}
