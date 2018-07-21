// Andrew Bub CSE30872 Challenge 00 - I/O

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void N();
void L();
void S();

int main()
{
	char a;

	while(cin >> a)
	{
		if(a == 'N')
		{
			N();
		}
		else if(a == 'L')
		{
			L();
		}
		else if(a == 'S')
		{
			S();
		}
		else {
			cout << "Unknown format: " << a << endl;
		}
	}

	return 0;
}

void N()
{
	int n;
	int x;
	double sum = 0;

	cin >> n;
	vector<int> v;

	for(int i = 0; i < n; i++) // fill vector and create sum
	{
		cin >> x;
		v.push_back(x);
		sum = sum + x;
	}

	// Display
	cout << "The sum of ";
	for(int i = 0; i < n; i++)
	{
		cout << v[i] << " ";
	}

	cout << "is " << sum << endl;
}

void L()
{
	cin.ignore();
	
	string line;
	getline(cin, line);
	
	int x;
	double sum = 0;
	
	stringstream ss(line);
	
	// Loop through line and calculate sum
	while(ss >> x)
	{
		sum = sum + x;
	}

	// Display
	cout << "The sum of " << line << " is " << sum << endl;
}

void S()
{
	int s;
	int x;
	double sum = 0;
	cin >> s;
	
	vector<int> v;
	
	cin >> x;
	while(x != s) // Read in until sentinel
	{
		v.push_back(x);
		sum = sum + x;

		cin >> x;
	}

	// Display
	cout << "The sum of ";
	for(int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	} 
	cout << "is " << sum << endl;
}
