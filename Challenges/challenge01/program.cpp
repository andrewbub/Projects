// Andrew Bub CSE30872 Challenge01 - Anagrams
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <algorithm>

using namespace std;

int main()
{

	string skip;
//	string a;
//	string b;

	while(cin)
	{
		string a;
		string	b;
		bool valid = true;		

		// Read in quotes as strings
		getline(getline(cin, skip, '"'), a, '"');
		getline(getline(cin, skip, '"'), b, '"');
		//cin.ignore();


		if(a == "" && b == "")
			break;

		// Make all characters lowercase
		transform(a.begin(), a.end(), a.begin(), ::tolower);
		transform(b.begin(), b.end(), b.begin(), ::tolower);

		// Remove spaces from strings
		a.erase(remove(a.begin(), a.end(), '\t'), a.end());
		b.erase(remove(b.begin(), b.end(), '\t'), b.end());
		a.erase(remove(a.begin(), a.end(), ' '), a.end());
		b.erase(remove(b.begin(), b.end(), ' '), b.end());


		int a_counts[128];
		int b_counts[128];

		for(int i = 0; i < 128; i++)
		{
			a_counts[i] = 0;
			b_counts[i] = 0;
		}

		for(string::iterator it = a.begin(); it != a.end(); it++)
		{
			 a_counts[*it]++;
		}

		for(string::iterator it = b.begin(); it != b.end(); it++)
		{
			 b_counts[*it]++;
		}

		for(int i = 0; i < 128; i++)
		{
			if(a_counts[i] != b_counts[i])
			{
				cout << "Invalid Pattern" << endl;
				valid = false;
				break;
			}
		}

		if(valid)
			cout << "Valid Pattern" << endl;

/*		// use find_first_not_of to determine if strings have a different character
		size_t s = a.find_first_not_of(b);
		//size_t t = b.find_first_not_of(a);

		if(s == string::npos && a.length() == b.length()) // if find_first_not_of does not find a difference
			cout << "Valid Pattern" << endl;
		else				// if find_fist_not_of finds a difference
			cout << "Invalid Pattern" << endl;
*/
	}

	return 0;
}
