
/*
 * Compute the n'th digit of pi using BBP-formula and GMP
 * Written by Peter Postmann on 17.01.2020
 *
 * This is free and unencumbered software released into the public domain.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "gmp.h"

/* pi = sum_(k=0)^oo [1/(16k)(4/(8k+1)-2/(8k+4)-1/(8k+5)-1/(8k+6))] */


void s_t(mpq_t res, const mpz_t k, const mpz_t j, mpz_t tmp1, mpz_t tmp2, mpq_t tmp3, unsigned int t)
{
    /* tmp2 = 8 * k + 1; */
    mpz_set(tmp2, k);
    mpz_mul_ui(tmp2, k, 8);
    mpz_add_ui(tmp2, tmp2, t);

    /* tmp1 = t * 16^j (mod tmp2) */
    mpz_set_ui(tmp1, 16);
    mpz_powm(tmp1, tmp1, j, tmp2);

    /* res += tmp1 / tmp2 */
    mpq_set_num(tmp3, tmp1);
    mpq_set_den(tmp3, tmp2);
    mpq_add(res, res, tmp3);
}

int pi(char *numDigit)
{
    unsigned int digit;    
    
    mpz_t n, k, j, t1, t2;
    mpq_t s1, s2, s3, s4, t3;
    
    if ((mpz_init_set_str(n, numDigit, 10) != 0) || (mpz_cmp_ui(n, 0) < 0))
    {
        mpz_clear(n);
        return -1;
    }    
    
    mpz_inits(k, j, t1, t2, NULL);
    mpq_inits(s1, s2, s3, s4, t3, NULL);
    
    /* for(k = 0; k <= n; k++) */
    for (mpz_set_ui(k, 0); mpz_cmp(n, k) >= 0; mpz_add_ui(k, k, 1)) 
    {
        /* j = n - k */
        mpz_sub(j, n, k);
        
        /* sum_(k=0)^n s_n=(16^(n-k) (mod 8k+t) */
        s_t(s1, k, j, t1, t2, t3, 1);
        s_t(s2, k, j, t1, t2, t3, 4);
        s_t(s3, k, j, t1, t2, t3, 5);
        s_t(s4, k, j, t1, t2, t3, 6);
    }

    /* res = 4s1 - 2s2 - s3 - s4 */
    mpq_set_ui(t3, 4, 1);
    mpq_mul(s1, s1, t3);
    mpq_set_ui(t3, 2, 1);
    mpq_mul(s2, s2, t3);
    mpq_sub(t3, s1, s2);
    mpq_sub(t3, t3, s3);
    mpq_sub(t3, t3, s4);
        
    /* res = 16 * res (mod 16) */
    mpq_get_num(t1, t3);
    mpq_get_den(t2, t3);
    mpz_mul_ui(t1, t1, 16);
    mpz_div(t1, t1, t2);
    mpz_mod_ui(t1, t1, 16);
    
    digit = mpz_get_ui(t1);
    
    mpz_clears(n, k, j, t1, t2, NULL);
    mpq_clears(s1, s2, s3, s4, t3, NULL);
    
    return digit;
}

int main(int argc, char* argv[])
{
    FILE* outputFile = NULL;
    int digit;
    char *numDigit;

    if (argc < 2)
    {
        printf("usage: %s [nth digit] [file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    numDigit = argv[1];

    if (argc >= 3)
    {
        outputFile = fopen(argv[2], "a");

        if (outputFile == NULL)
        {
            fprintf(stderr, "error: invalid output file (%s)\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }
   
    /* compute */
    digit = pi(numDigit);
    
    if(digit < 0)
    {
        fprintf(stderr, "error: invalid digit index\n");
        if(outputFile) fclose(outputFile);
        return EXIT_FAILURE;
    }
    
    if(outputFile)
    {        
        int numBytesWritten = fprintf(outputFile, "%X", digit);
        fclose(outputFile); 
        outputFile = NULL;
        
        if(numBytesWritten < 0) return EXIT_FAILURE;
    }
    else
    {
        printf("%X\n", digit);
    }
    

    return EXIT_SUCCESS;
}
