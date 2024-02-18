#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <gmp.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

unsigned int countBits(mpz_t number){
    return mpz_sizeinbase(number, 2);
}

bool isPrime(mpz_t number){
    int result = mpz_probab_prime_p(number, 25);
    return result > 0;
}

void primeNumberGen(mpz_t result){
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    do{
        mpz_urandomb(result, state, 2048);
    } while(isPrime(result) == false);
    gmp_printf("prime? = %Zd \n", result);
    gmp_randclear(state);
}

bool GCD(mpz_t a, mpz_t b){
    mpz_t quoficientTemp, residuosTemp;
    mpz_init(quoficientTemp);
    mpz_init(residuosTemp);

    while(mpz_cmp_ui(b, 0) > 0){
        mpz_cdiv_q(quoficientTemp, a, b);
        mpz_cdiv_r(residuosTemp, a, b);

        mpz_set(a, b);
        mpz_set(b, residuosTemp);
    }

    mpz_clear(quoficientTemp);
    mpz_clear(residuosTemp);
    return mpz_cmp_ui(a, 1) == 0;
}

void eGen(mpz_t n, mpz_t eKey){
    mpz_t e;
    mpz_init(e);
    mpz_set_ui(e, 65537);

    if(GCD(e, n)){
        mpz_set(eKey, e);
        mpz_clear(e);
        return;
    }

    for(mpz_sub_ui(e, n, 1); mpz_cmp_ui(e, 2) > 0;mpz_sub_ui(e, e, 1)){
        if(GCD(e, n)){
            mpz_set(eKey, e);
            mpz_clear(e);
            break;
        }
    }
    mpz_clear(e);
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
    mpz_t eKey;
    mpz_init(eKey);
    eGen(n, eKey);

    unsigned int nBits = countBits(n);
    gmp_printf("n = %Zd \n", n);
    gmp_printf("e = %Zd \n", eKey);
    printf("nBits = %u", nBits);
    
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    return EXIT_SUCCESS;
}