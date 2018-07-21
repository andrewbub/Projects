// Andrew Bub CSE30872 - Challenge21: Carmichael Numbers
// November 19, 2017
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

// Global Variables ---------------------------------------------------------------------------------------------
const int MAXN = 65001;
bool prime[MAXN];

// Prototypes ---------------------------------------------------------------------------------------------------
void primes(); // determines primes for all values up to 65,000
bool carmichael(int); // determines if n is a carmichael number
long long int modpow(int, int, int); // calculates mod of powers

// Main Execution -----------------------------------------------------------------------------------------------
int main()
{
	int n;
	primes();

	while(cin >> n) // read in n until EOF
	{
		if(carmichael(n)) // if n is a Carmichael number
		{
			cout << "The number " << n << " is a Carmichael number." << endl;
		} else {
			cout << n << " is normal." << endl;
		}
	}
	return 0;
}

// Functions -----------------------------------------------------------------------------------------------------
void primes()
{
	memset(prime, true, sizeof(prime)); // set all of prime to true

	for(int i = 2; i <= (int)sqrt(MAXN * 1.0); ++i)
	{
		if(prime[i])
		{
			for(int j = i * i; j < MAXN; j += i)
			{
				prime[j] = false; // set all composite numbers to false
			}
		}
	}
}

bool carmichael(int n)
{
	if(prime[n]) // if n is prime, then not a Carmichael number
		return false;

	for(int i = 2; i < n; ++i) // check if all numbers (a) from 2 to n-1 are Carmichael numbers
	{
		if(modpow(i, n, n) != i) // if a^n mod n != a
			return false;
	}

	return true;
}

long long int modpow(int a, int n, int m)
{
	if(n == 1) return a%m;

	long long int u = modpow(a, n >> 1, m);
	u = (u*u)%m;

	if(n%2) // odd numbers
	{
		return (a*u) % m;
	} else { // even numbers
		return u;
	}
}
