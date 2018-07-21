// Andrew Bub CSE30872 - ChallengeIA: Balanced Tags
// November 6, 2017
#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// Global Variables -----------------------------------------------------------------------------------
queue<int> START; // stack of positions of all '<'
queue<int> STOP; // stack of positions of all '>'
stack<string> STACK;

// Prototypes -----------------------------------------------------------------------------------------
bool is_balanced(string);

// Main Execution -------------------------------------------------------------------------------------
int main()
{
	string line;
	bool b = true;

	while(getline(cin, line))
	{
		b = is_balanced(line);

		if(b)
			cout << "Balanced" << endl;
		else
			cout << "Unbalanced" << endl;

		while(!START.empty())
		{
			START.pop(); // reset START for next cycle
		}
		while(!STOP.empty())
		{
			STOP.pop(); // reset STOP for next cycle
		}
		while(!STACK.empty())
		{
			STACK.pop(); // reset STACK for next cycle
		}
	}

	return 0;
}

// Functions ------------------------------------------------------------------------------------------
bool is_balanced(string line)
{
	bool b = true;
	string sub; // substring

	// Find position of "tag"
	size_t tag_start = line.find("tag");
	size_t tag_end = tag_start + 2;

	// Find locations of '<' and '>'
	for(int i = 0; i < line.length(); i++)
	{
		if(line[i] == '<')
			START.push(i);
		else if(line[i] == '>')
			STOP.push(i);
	}

	// if unbalanced '<'s and '>'s
	if(START.size() != STOP.size())
	{
		b = false;
		return b;
	}

	while(!START.empty() && !STOP.empty())
	{
		// get substring between '<' and '>'
		sub = line.substr(START.front() + 1, STOP.front() - START.front() - 1);

		if(sub.find("tag")) // if any version of "tag" found between < >
		{
			tag_start = line.find("tag", STOP.front() + 1);
			tag_end = tag_start + 2;
		}

		if(sub.find('<') != string::npos || sub.find('>') != string::npos) // if '<' or '>' found between < >
		{
			b = false;
			break;
		}

		if(sub[0] != '/') // if opening tag
		{
			if(START.front() < tag_start) // if sub before tag, add to STACK
				STACK.push(sub);
			else {
				b = false;
				break;
			}
		} else { // if closing tag
			if(STOP.front() > tag_end) // if sub after tag
			{
				sub = sub.substr(1, sub.length() - 1);

				if(!STACK.empty())
				{
					if(sub == STACK.top())
					{
						STACK.pop();	
					} else {
						b = false;
						return b;
					}
				} else {
					b = false;
					break;
				}
			} else {
				b = false;
				break;
			}
		}

		START.pop();
		STOP.pop();
	}

	if(!STACK.empty())
		b = false;

	return b;
}
