#include <stdio.h>
#include <gmp.h>


#define VALUE_OF_M "15241383936"   // change this with the value of m you want to test with. I will change this with the "target message" I ask you to encrypt for grading purpose after the deadline.
#define PRIV_KEY "40622201812345" // I'm using this private key to test your outputs. You will get deduction if you don't use this private key since the decryption will fail.


int main(int argc, char *argv[]){

	int score = 100;

	size_t c1size,c2size,psize;
	mpz_t c1,c2,x,p,m,m_original;

	mpz_init(c1);
	mpz_init(c2);
	mpz_init(x);
	mpz_init(p);
	mpz_init(m);
	mpz_init(m_original);

	mpz_init_set_str(m_original, VALUE_OF_M, 10);


	mpz_set_str(x, PRIV_KEY, 10);


	printf("Choose any line for evaluation: ");

	gmp_scanf("%Zd,%Zd,%Zd", c1, c2, p);

	mpz_t q;
	mpz_init(q);

	mpz_sub_ui(q,p,1);
	mpz_fdiv_q_ui(q,q,2);

	if(mpz_probab_prime_p(q, 30) == 0){
		printf("p was chosen randomly.\n");
		score -= 20;
	}

	mpz_clear(q);

	
	puts("");

	mpz_t c1x,c1x_inv;
	mpz_init(c1x);
	mpz_init(c1x_inv);

	mpz_powm(c1x, c1, x, p);
	mpz_invert(c1x_inv,c1x,p);

	mpz_mul(m,c2,c1x_inv);
	mpz_mod(m, m, p);
	
	mpz_clear(c1x);
	mpz_clear(c1x_inv);
	
	
	if(mpz_cmp(m,m_original) != 0){
		printf("Decryption failed.\n");
		score -= 20;
	}

	//gmp_printf("c1x = %Zd\nc2 = %Zd\n",c1x,c2);

	c1size = mpz_sizeinbase(c1,2);
	c2size = mpz_sizeinbase(c2,2);
	psize = mpz_sizeinbase(p,2);

	if(c1size < 900 || c2size < 900 || psize < 1000){
		 printf("The modulus p is too small.\n");
		score -= 20;
	}


	if(mpz_legendre(c1,p) < 1 || mpz_legendre(c2,p) < 1){
		printf("The encryption is vulnerable to QR/QNR attacks.\n");
		score -= 20;
	}

	
	mpz_t p_sample;
	mpz_init(p_sample);
	

	mpz_set_str(p_sample,"279912453517279481142508138295795728925920436966115779210015345910735936817216166665707389976196265414887593280152020846898808343120835996612060701784591441800492689878310846725490684126989523347376168142743375677899762793572386335847677511852930831437616317060105962630618707127813825060571610691715576117299", 10);
	if(mpz_cmp(p,p_sample) == 0){
		printf("Used the same p as in the sample.\n");
		score -= 40;
	}
	

	mpz_clear(p_sample);

	
	puts("");
	puts("Evaluation finished.");

	if(score < 0) score = 0;

	printf("This student's score is: %d\n", score);

	mpz_clear(c1);
	mpz_clear(c2);
	mpz_clear(x);
	mpz_clear(p);
	mpz_clear(m);
	mpz_clear(m_original);
}

