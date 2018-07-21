// Andrew Bub CSE30872 - Challenge03: Largest Font Size
// October 13, 2017
#include <iostream>
#include <map>
#include <string>
#include <math.h>

using namespace std;

// Global Variables -----------------------------------------------------------------------
map<char, double> alpha; // map of the letters and their respective sizes

// Prototypes -----------------------------------------------------------------------------
int fit(int, int, string); // returns maximum size the string can fit in given dimensions

// Main Execution -------------------------------------------------------------------------
int main()
{
	char letter;
	double weight; // weight of each individual letter
	int h, w; // height and width of slide
	string text; 
	int size; // largest font size

	for(int i = 0; i < 26; i++) // 26 letters in alphabet
	{
		cin >> letter >> weight;
		alpha[letter] = weight; // fill the map
	}

	while(cin >> h >> w >> text)
	{
		size = fit(h, w, text); // get maximum font size

		cout << size << endl;
	}

	alpha.clear(); // deallocate map

	return 0;
}


// Functions -----------------------------------------------------------------------------
int fit(int h, int w, string text)
{
	bool b = true;

	int size = 1; // font size
	int max = 0; // max font size

	int h_total = size; // height total
	int w_total = 0; // width total

	while(b)
	{
		for(int i = 0; i < text.size(); i++)
		{
			w_total += floor(size * alpha[text[i]]);

			if(w_total > w) // if added letter doesn't fit on the current line
			{
				h_total += size; // account for another line added
				w_total = 0;
				i--;
			}

			if(h_total > h) // if more lines than available height
			{
				b = false;
				size--;
				break;
			}
		}

		if(!b)
		{
			break;
		} else {
			max = size;
			size++;
			h_total = size;
			w_total = 0;
		}
	}
	
	return max;
}
