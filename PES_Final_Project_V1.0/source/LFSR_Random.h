/*
 * LFSR_Random.h - Header file for implementation of random number generation
 *  through Linear Feedback Shift Register Method(LFSR)
 *
 */

#ifndef LFSR_RANDOM_H_
#define LFSR_RANDOM_H_

#include <stdio.h>
#include <stdint.h>

/*
 *Creates polynomial mask for upper & lower degree polynomial
 *
 *Parameters : count - required length of the password
 *Parameters   mask[][] - Polynomial mask array
 *Returns    : NONE
 */
void generate_polymask(int count,int *mask[2]);

/*
 *Shifts the polynomial mask with seed value
 *
 *Parameters : seed - seed value for the LFSR method
 *             mask - Polynomial mask for that degree polynomial
 *Returns    : NONE
 */
int perform_shift(int *seed,int polynomial_mask);

/*
 *Generate random number
 *
 *Parameters : seed1,seed2 - seed values for the LFSR method
 *             count - required length of the password
 *Returns    : NONE
 */
int generate_random_value(int seed1,int seed2,int count);


#endif /* LFSR_RANDOM_H_ */
