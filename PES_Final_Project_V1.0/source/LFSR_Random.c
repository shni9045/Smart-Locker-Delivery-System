/*
 * LFSR_Random.c -Source file containing implementation of random number generation
 *  through Linear Feedback Shift Register Method(LFSR)
 *
 */

#include "LFSR_Random.h"


#include <stdio.h>
#include <stdint.h>

/*
 * Polynomial mask for the primitive polynomial created by truncating the LSB
 *  for polynomials with degree 3-8 (Since password length is restricted to 4 to 8)
 *
 */
int Poly_Mask[6][2]={{3,0x5},
		             {4,0x9},
					 {5,0x1d},
					 {6,0x36},
					 {7,0x69},
					 {8,0xa6}};

// Array to hold polynomial masks as per user selected password length

int gen_mask[2]={0};

void generate_polymask(int count,int *mask[2]){

    gen_mask[0]=Poly_Mask[count-4][1];
    gen_mask[1]=Poly_Mask[count-3][1];

}

int perform_shift(int *seed,int polynomial_mask){

	int feed;

	feed = *seed & 1;                        //extract right most bit of seed
	*seed >>=1;                              //shift seed by one place

	if (feed ==1)
		*seed ^=polynomial_mask;             //XOR with feedback term to increase randomness
	return *seed;
}



int generate_random_value(int seed1,int seed2,int count){

    int random_value=0;                                               //Variable to store random value

    generate_polymask(count,*Poly_Mask[2]);                           //Generate polynomial mask for upper & lower degree polynomial

	perform_shift(&seed1,gen_mask[1]);                                //Shift upper degree mask

	//Shift upper degree mask once more
	//XOR upper degree mask with lower degree mask
	random_value=perform_shift(&seed1,gen_mask[1]) ^ perform_shift(&seed2,gen_mask[0]);

    //Extract lower 16 bits to generate random number
	random_value= random_value & 0xffff;

	return random_value;

}





