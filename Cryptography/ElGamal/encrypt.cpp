// Andrew Bub CSE 40622
// Project Assignment 02 - ElGamal encrypt.cpp
// February 28, 2018

#include <iostream>
#include <gmp.h>
#include <string>
#include <vector>

using namespace std;

int main()
{
	// Read in input ---------------------------------------------------------------------------
	unsigned long int m;
	cout << "Enter a value for m: ";
	cin >> m;

	unsigned long int x = 40622201812345; // hardcode x
	string h_p = "21430172143725346418968500981200036211228096234110672148875007767407021022498722449863967576313917162551893458351062936503742905713846280871969155149397149607869135549648461970842149210124742283755908364306092949967163882534797535118331087892154125829142392955373084335320859663305248773674411336326903"; // hardcode p
	string h_q = "10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668163451"; // hardcode q
	string h_h = "15526791460172599953568511524860204916349969527841729078648425635594967381521592136127911920722151161613758347045999045368121909270881703199891313405825763394072835609318872105690859465835509836083929766792189423508267215660126006177821607396983653498274431543080127744553606889918034622683814787556834"; // hardcode h

	// Initialize GMP variables ----------------------------------------------------------------
	mpz_t q, p, g, h, r, c1, c2, t;
	mpz_init(q);
	mpz_init(p);
	mpz_init(g);
	mpz_init(h);
	mpz_init(r);
	mpz_init(c1);
	mpz_init(c2);
	mpz_init(t); // temp variable
	gmp_randstate_t r_state; // random state
	gmp_randinit_default(r_state);
	
	// Set q
	mpz_set_str(q, h_q.c_str(), 10);	

	// Set modulus p
	mpz_set_str(p, h_p.c_str(), 10);

	// Set generator g
	mpz_set_ui(g, 5);

	// Set h 
	mpz_set_str(h, h_h.c_str(), 10);

	// Encrypt m 5 times ------------------------------------------------------------------------
	for(int i = 0; i < 6; i++)
	{
		// Calculate random r
		mpz_urandomm(r, r_state, q); // get random r

		mpz_gcd(t, r, q);
		while(mpz_cmp_ui(t, 1) != 0) // find r that is coprime, therefore in Zq*
		{
			mpz_urandomm(r, r_state, q);
			mpz_gcd(t, r, q);
		}
		
		if(i == 4)
			continue;

		// Calculate c1 := g^r
		mpz_powm(c1, g, r, p);

		// Calculate c2 := m * h^r
		mpz_powm(c2, h, r, p);
		mpz_mul_ui(c2, c2, m);

		// Output results c1, c2, p
		mpz_out_str(stdout, 10, c1);
		cout << ", ";
		mpz_out_str(stdout, 10, c2);
		cout << ", ";
		mpz_out_str(stdout, 10, p);
		if(i < 4)
			cout << endl << endl;
		else
			cout << endl;
	}

	// Clear GMP variables
	mpz_clear(q);
	mpz_clear(p);
	mpz_clear(g);
	mpz_clear(h);
	mpz_clear(r);
	mpz_clear(c1);
	mpz_clear(c2);

	return 0;
}
