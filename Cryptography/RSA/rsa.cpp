// Andrew Bub CSE 40622
// Project Assignment 01 - RSA
// February 7, 2018

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <gmp.h>

using namespace std;

int main()
{
	string input;
	vector<string> v;

	// Initialize input variables
	mpz_t p, q, e, m;
	mpz_init (p);
	mpz_init (q);
	mpz_init (e);
	mpz_init (m);

	// Read from stdin, separated by commas
	cout << "Enter the numbers: ";
	cin >> input;
	istringstream ss(input);
	string token;

	while(getline(ss, token, ','))
	{
		v.push_back(token);
	}

	mpz_set_str(p, v[0].c_str(), 10);
	mpz_set_str(q, v[1].c_str(), 10);
	mpz_set_str(e, v[2].c_str(), 10);
	mpz_set_str(m, v[3].c_str(), 10);

	// Initialize output variables
	mpz_t n, d, c;
	mpz_init (n);
	mpz_init (d);
	mpz_init (c);
	
	// Calculate n
	mpz_mul(n, q, p); // n = pq

	// Calculate d
	mpz_t tf, one; // totient function and constant one
	mpz_init (tf);
	mpz_init_set_str(one, "1", 10);

	mpz_sub(q, q, one); // q = q-1
	mpz_sub(p, p, one); // p = p-1

	mpz_mul(tf, q, p); // tf = (p-1)(q-1)

	mpz_invert(d, e, tf); // d multiplicative inverse modulo tf

	// Calculate c
	mpz_powm(c, m, e, n); // c = m^e mod n


	// Output Results
	cout  << "n = ";
	mpz_out_str(stdout, 10, n);
	cout << endl << "d = ";
	mpz_out_str(stdout, 10, d);
	cout << endl << "c = ";
	mpz_out_str(stdout, 10, c);
	cout << endl;

	// Clear variables
	mpz_clear (p);
	mpz_clear (q);
	mpz_clear (e);
	mpz_clear (m);
	mpz_clear (n);
	mpz_clear (d);
	mpz_clear (c);
	mpz_clear (tf);
	mpz_clear (one);

	return 0;
}
