// Andrew Bub CSE30872 - Challenge02: RPN Calculator
// October 5, 2017
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;

// Global Variables ---------------------------------------------------------
queue<string> INPUT; // stack for all input
//stack<char> OPS; // stack for operations
stack<long int> NUMS; // stack for numbers
stack<long int> DIGITS; // stack of digits for output
vector<long int> OUTPUT; 

// Prototypes ---------------------------------------------------------------
int calc();
void display(int);
int count_digits(int);

// Main Execution -----------------------------------------------------------
int main()
{
	string line;
	string  n;
	int sol; // solution

	while(getline(cin, line)) // read in line
	{
		stringstream ss(line);
		ss.str(line);

		while(ss >> n) // read in individual entries from line
		{
			INPUT.push(n);
		}
		
		sol = calc(); // calculate solution
		display(sol); // display solution with LED numbers
	}

	return 0;
}

// Functions -----------------------------------------------------------------
int calc()
{
	int a, b;
	int sol;

	while(! INPUT.empty()) // go through queue while calculating
	{
		if(INPUT.front() == "+")
		{
			if(! NUMS.empty())
			{
				b = NUMS.top();
				NUMS.pop();
				a = NUMS.top();
				NUMS.pop();

				NUMS.push(a+b);
			}
			INPUT.pop();
		} else if(INPUT.front() == "-")
		{
			if(! NUMS.empty())
			{
				b = NUMS.top();
				NUMS.pop();
				a = NUMS.top();
				NUMS.pop();

				NUMS.push(a-b);
			}
			INPUT.pop();
		} else if(INPUT.front() == "*")
		{
			if(! NUMS.empty())
			{
				b = NUMS.top();
				NUMS.pop();
				a = NUMS.top();
				NUMS.pop();

				NUMS.push(a*b);
			}
			INPUT.pop();
		} else if(INPUT.front() == "/")
		{
			if(! NUMS.empty())
			{
				b = NUMS.top();
				NUMS.pop();
				a = NUMS.top();
				NUMS.pop();

				NUMS.push(a/b);
			}
			INPUT.pop();
		} else if(INPUT.front() == "^")
		{
			if(! NUMS.empty())
			{
				b = NUMS.top();
				NUMS.pop();
				a = NUMS.top();
				NUMS.pop();

				NUMS.push(pow(a,b));
			}
			INPUT.pop();
		} else {
			NUMS.push(stoi(INPUT.front()));
			INPUT.pop();
		}
	}

	sol = NUMS.top(); // last entry in NUMS will be solution
	if(!NUMS.empty())
		NUMS.pop(); // clear NUMS stack

	return sol;
}

void display(int sol)
{
	bool neg = false; // if negative solution
	if(sol < 0)
	{
		neg = true;
		sol = -sol;
	}

	int count = count_digits(sol);

	int digit;

	for(int i = 0; i < count; i++)
	{
		digit = sol % 10;
		sol = sol / 10;
		DIGITS.push(digit);
	}

	if(neg)
		DIGITS.push('-');

	while(! DIGITS.empty())
	{
		OUTPUT.push_back(DIGITS.top());
		DIGITS.pop();
	}

	// Top line of output
	if(neg)
		cout << "   ";

	for(int i = 0; i < OUTPUT.size(); i++)
	{
		switch(OUTPUT[i])
		{
			case 0:	cout << " _ ";
				break;
			case 1: cout << "   ";
				break;
			case 2:	cout << " _ ";
				break;
			case 3:	cout << " _ ";
				break;
			case 4:	cout << "   ";
				break;
			case 5:	cout << " _ ";
				break;
			case 6:	cout << " _ ";
				break;
			case 7:	cout << " _ ";
				break;
			case 8:	cout << " _ ";
				break;
			case 9:	cout << " _ ";
				break;
		}
	}
	cout << endl;

	// Middle line of output
	if(neg)
		cout << " _ ";

	for(int i = 0; i < OUTPUT.size(); i++)
	{
		switch(OUTPUT[i])
		{
			case 0:	cout << "| |";
				break;
			case 1:	cout << "  |";
				break;
			case 2:	cout << " _|";
				break;
			case 3:	cout << " _|";
				break;
			case 4:	cout << "|_|";
				break;
			case 5:	cout << "|_ ";
				break;
			case 6:	cout << "|_ ";
				break;
			case 7:	cout << "  |";
				break;
			case 8:	cout << "|_|";
				break;
			case 9:	cout << "|_|";
				break;
		}
	}
	cout << endl;

	// Bottom line of output
	if(neg)
		cout << "   ";

	for(int i = 0; i < OUTPUT.size(); i++)
	{
		switch(OUTPUT[i])
		{
			case 0:	cout << "|_|";
				break;
			case 1:	cout << "  |";
				break;
			case 2:	cout << "|_ ";
				break;
			case 3:	cout << " _|";
				break;
			case 4:	cout << "  |";
				break;
			case 5:	cout << " _|";
				break;
			case 6:	cout << "|_|";
				break;
			case 7:	cout << "  |";
				break;
			case 8:	cout << "|_|";
				break;
			case 9:	cout << " _|";
				break;
		}
	}
	cout << endl;

	OUTPUT.clear();
}

int count_digits(int sol) // returns the number of digits in given number
{
	int count = 0;
	
	if(sol == 0)
	{
		count = 1;
	}

	while(sol > 0)
	{
		count++;
		sol = sol/10;
	}

	return count;
}
