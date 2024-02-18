#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <gmp.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define CALC_ERROR 1

unsigned int countBits(mpz_t number){
    return mpz_sizeinbase(number, 2);
}
void primeNumberGen(mpz_t result){
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    do{
        mpz_urandomb(result, state, 2048);
    } while(mpz_probab_prime_p(result, 25));
    
    gmp_randclear(state);
}

bool GCD(mpz_t a, mpz_t b){
    mpz_t quoficientTemp, residuosTemp;
    mpz_init(quoficientTemp);
    mpz_init(residuosTemp);

    while(b > 0){
        mpz_cdiv_q(quoficientTemp, a, b);
        mpz_cdiv_r(residuosTemp, a, b);

        a = b;
    }

    return if(a == 1);
}

mpz_t eGen(mpz_t n){
    mpz_t e;
    mpz_init(e);
    mpz_set_ui(e, 65537);

    if(GCD(e, n)){
        return e;
    }

    for(mpz_set_ui(e, n -1); e > 2;e--){
        if(GCD(e, n)){
        return e;
        }
    }

    return CALC_ERROR;
}

int main(){
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);
    primeNumberGen(p);
    primeNumberGen(q);

    mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q);
    unsigned long long int e = eGen(n);

    unsigned int nBits = countBits(n);
    gmp_printf("n = %Zd \ns", n);
    printf("e = %llu \n", e);
    printf("nBits = %u", nBits);
    
    return EXIT_SUCCESS;
}