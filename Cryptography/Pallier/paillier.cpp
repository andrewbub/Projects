// Andrew Bub
// CSE 40622 Programming Assignment 03 - paillier.cpp
// April 11, 2018

// "g++ -lgmp paillier.cpp -o  run" to compile
// "./run < input.txt" to execute

#include <iostream>
#include <gmp.h>
#include<string>

using namespace  std;

int main()
{
	// Read in input --------------------------------------------------------------------------------------------
	string c_input, p_input, q_input, m_p_input;
	getline(cin, c_input);
	getline(cin, p_input);
	getline(cin, q_input);
	getline(cin, m_p_input);


	// Initialize GMP variables --------------------------------------------------------------------------------
	mpz_t c, c_p, p, q, m, m_p, n, g, lambda, mu;

	mpz_init(c);
	mpz_init(c_p);
	mpz_init(p);
	mpz_init(q);
	mpz_init(m);
	mpz_init(m_p);
	mpz_init(n);
	mpz_init(g);
	mpz_init(lambda);
	mpz_init(mu);

	// Set c, p, q, m'
	mpz_set_str(c, c_input.c_str(), 10);
	mpz_set_str(p, p_input.c_str(), 10);
	mpz_set_str(q, q_input.c_str(), 10);
	mpz_set_str(m_p, m_p_input.c_str(), 10);

	// n = pq
	mpz_mul(n, p, q);

	// g := 1 + n
	mpz_add_ui(g, n, 1);

	// lambda = phi(n) = (p-1)(q-1)
	mpz_t t1, t2; // temp variables
	mpz_init(t1);
	mpz_init(t2);
	mpz_sub_ui(t1, p, 1);
	mpz_sub_ui(t2, q, 1);
	mpz_mul(lambda, t1, t2);

	mpz_clear(t1);
	mpz_clear(t2);

	// mu = (phi(n))^-1 mod n
	mpz_invert(mu, lambda, n);


	// Decrypt c ----------------------------------------------------------------------------------------------
	// m = (((c^lambda - 1) mod n^2) / n) * mu mod n
	mpz_t n_sq, t;
	mpz_init(n_sq); // n^2
	mpz_pow_ui(n_sq, n, 2);
	mpz_init(t); // temp variable

	// (c^lambda - 1) mod n^2 = ((c^lambda mod n^2) - 1) mod n^2
	mpz_powm(t, c, lambda, n_sq); // c^lambda mod n^2
	mpz_sub_ui(t, t, 1); // (c^lambda mod n^2) - 1
	mpz_mod(t, t, n_sq); // ((c^lambda mod n^2) - 1) mod n^2

	// ((c^lambda - 1) mod n^2) / n
	mpz_cdiv_q(t, t, n);

	// (((c^lambda - 1) mod n^2) / n) * mu
	mpz_mul(t, t, mu);

	// m = (((c^lambda - 1) mod n^2) / n) * mu mod n
	mpz_mod(m, t, n);

	// Output m
	mpz_out_str(stdout, 10, m);
	cout << endl << endl;


	// Encrypt m' ----------------------------------------------------------------------------------------------
	// Calculate random r
	gmp_randstate_t r_state; // random state
	gmp_randinit_default(r_state);
	mpz_t r;
	mpz_init(r);
	mpz_urandomm(r, r_state, n);

	mpz_gcd(t, r, n_sq);
	while(mpz_cmp_ui(t, 1) != 0) // find r such that gcd(r, n^2) = 1
	{
		cout << "in here" << endl;
		mpz_urandomm(r, r_state, n);
		mpz_gcd(t, r, n_sq);
	}

	// c' = (g^m_p * r^n) mod n^2 = ((g^m_p mod n^2) * (r^n mod n^2)) mod n^2
	mpz_t a, b;
	mpz_init(a); // temp variable a = g^m_p mod n^2
	mpz_init(b); // temp variable b = r^n mod n^2

	// a = g^m_p mod n^2
	mpz_powm(a, g, m_p, n_sq);

	// b = r^n mod n^2
	mpz_powm(b, r, n, n_sq);

	// c' = a*b mod n^2
	mpz_mul(t, a, b);
	mpz_mod(c_p, t, n_sq);

	// Output c', p, q
	mpz_out_str(stdout, 10, c_p);
	cout << ",";
	mpz_out_str(stdout, 10, p);
	cout << ",";
	mpz_out_str(stdout, 10, q);
	cout << endl;

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(r);

/*	// Decrypt c' to check  ------------------------------------------------------------------------------------
	// m' = (((c^lambda - 1) mod n^2) / n) * mu mod n
	// (c^lambda - 1) mod n^2 = ((c^lambda mod n^2) - 1) mod n^2
	mpz_powm(t, c_p, lambda, n_sq); // c^lambda mod n^2
	mpz_sub_ui(t, t, 1); // (c^lambda mod n^2) - 1
	mpz_mod(t, t, n_sq); // ((c^lambda mod n^2) - 1) mod n^2

	// ((c^lambda - 1) mod n^2) / n
	mpz_cdiv_q(t, t, n);

	// (((c^lambda - 1) mod n^2) / n) * mu
	mpz_mul(t, t, mu);

	// m = (((c^lambda - 1) mod n^2) / n) * mu mod n
	mpz_mod(m_p, t, n);

	// Output m'
	cout << endl << "the m' given was ";
	mpz_out_str(stdout, 10, m_p);
	cout << endl;
*/
	// Clear GMP variables ------------------------------------------------------------------------------------
	mpz_clear(c);
	mpz_clear(c_p);
	mpz_clear(p);
	mpz_clear(q);
	mpz_clear(m);
	mpz_clear(m_p);
	mpz_clear(n);
	mpz_clear(g);
	mpz_clear(lambda);
	mpz_clear(mu);
	mpz_clear(n_sq);
	mpz_clear(t);

	return 0;
}
