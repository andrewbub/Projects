// Andrew Bub CSE 40622
// Project Assignment 02 - ElGamal init.cpp
// February 28, 2018

#include <iostream>
#include <gmp.h>
#include <string>
#include <vector>

using namespace std;

int main()
{
	// Read in input ---------------------------------------------------------------------------
	int m;
	cout << "Enter a value for m: ";
	cin >> m;

	unsigned long int x = 40622201812345; // hardcode x

	// Initialize GMP variables ----------------------------------------------------------------
	mpz_t q, p, g, h;
	mpz_init(q);
	mpz_init(p);
	mpz_init(g);
	mpz_init(h);
	
	// Set q and p -----------------------------------------------------------------------------
	mpz_ui_pow_ui(q, 2, 1000); // get number of 1000 bites

	while(1)
	{
		mpz_nextprime(q, q); // find next prime

		// p = 2q + 1
		mpz_mul_ui(p, q, 2);
		mpz_add_ui(p, p, 1);
		
		if(mpz_probab_prime_p(p, 50) != 0) // make sure p is prime
			break;
	}
	cout << "p = ";
	mpz_out_str(stdout, 10, p);
	cout << endl;
	cout << "q = ";
	mpz_out_str(stdout, 10, q);
	cout << endl;

	// Calculate generator g ------------------------------------------------------------------
	mpz_t it, t; // iterator and temp variable
	mpz_init(it);
	mpz_init(t);
	
	mpz_set_ui(it, 2); // start at 2 since 1 cannot be a generator

	while(mpz_cmp(it, p) != 0) // Find elements of group G from Zp*
	{
		mpz_gcd(t, p, it);
		if(mpz_cmp_ui(t, 1) == 0) // if coprime to p, then element of G
		{
			// check if element is a generator
			mpz_powm_ui(t, it, 2, p); // set t = it^2 mod p
			if(mpz_cmp_ui(t, 1) == 0) // if t == 1, not generator
			{
				mpz_add_ui(it, it, 1); // iterate
				continue;
			}
			mpz_powm(t, it, q, p); // set t = it^q mod p
			if(mpz_cmp_ui(t, 1) == 0) // if t == 1, not generator
			{
				mpz_add_ui(it, it, 1); // iterate
				continue;
			}

			mpz_set(g, it); // if it^2 mod p != 1 and it^q mod p != 1, it is generator
			break;
		}
	}

	cout << "g = ";
	mpz_out_str(stdout, 10, g);
	cout << endl;

	
	// Calculate h := g^x -----------------------------------------------------------------------
	mpz_powm_ui(h, g, x, p);
	
	cout << "h = ";
	mpz_out_str(stdout, 10, h);
	cout << endl;

	// Clear GMP variables ---------------------------------------------------------------------
	mpz_clear(q);
	mpz_clear(p);
	mpz_clear(g);
	mpz_clear(it);
	mpz_clear(t);
	mpz_clear(h);

	return 0;
}
