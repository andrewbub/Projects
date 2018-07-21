// Andrew Bub CSE30872 - Challenge 14: Small Racket (Scheme EBNF Interpreter)
// October 25, 2017
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>

using namespace std;

// Global Variables ---------------------------------------------------------------------------------------------
stack<int> START; // stack of positions of all '('
vector<int> NUMS;

// Prototypes ---------------------------------------------------------------------------------------------------
void solve(string);
void calc(string &);

// Main Execution -----------------------------------------------------------------------------------------------
int main()
{
	string line; // line of input
	
	while(getline(cin, line))
	{
		solve(line);
	}

	return 0;
}

// Functions ----------------------------------------------------------------------------------------------------
void solve(string line)
{
	string part; // substring for each expression
	int stop; // location of first ')'
	int sol = 0; // solution of line
	bool space = false; // true if line containts a space

	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == '(')
			START.push(i);
		else if(line[i] == ')')
		{
			stop = i;
			break;
		}
	}

	// Divide
	if(START.empty()) // if there are no parentheses
		part = line;
	else
		part = line.substr(START.top()+1, stop - START.top()-1);
	
	// Conquer
	calc(part);

	// Merge
	if(!START.empty())
		line.replace(START.top(), stop - START.top()+1, part);

	NUMS.clear(); // clear NUMS vector for next iteration
	while(!START.empty()) // clear START stack for next iteration
	{
		START.pop();
	}

	// if resulting line contains a space, it is not the solution
	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == ' ')
		{
			space = true;
			break;
		}
	}

	if(space)
		solve(line);
	else
	{
		sol = stoi(line);
		cout << sol << endl;
		return;
	}
}

void calc(string &part)
{
	if(part.length() > 1)
	{
		char op; // operation
		int n; // number
	
		stringstream ss(part);
		ss >> op;

		while(ss >> n)
		{
			NUMS.push_back(n);
		}

		int sol = NUMS[0]; // solution

		switch(op)
		{
			case '+':	for(int i = 1; i < NUMS.size(); i++)
					{
						sol += NUMS[i];
					}
					break;
			case '-':	for(int i = 1; i < NUMS.size(); i++)
					{
						sol -= NUMS[i];
					}
					break;
			case '*':	for(int i = 1; i < NUMS.size(); i++)
					{
						sol *= NUMS[i];
					}
					break;
			case '/':	for(int i = 1; i < NUMS.size(); i++)
					{
						sol /= NUMS[i];
					}
					break;
		}
	
		part = to_string(sol);
	}
}
