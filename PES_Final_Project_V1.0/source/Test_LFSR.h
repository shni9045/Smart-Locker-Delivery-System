/*
 * Test_LFSR.h
 *
 */

#ifndef TEST_LFSR_H_
#define TEST_LFSR_H_

#include <stdio.h>
#include <stdlib.h>
#include "uCUnit.h"
#include "LFSR_Random.h"

/*
 * Function to generate random seeds using builtin rand() function
 * PARAMETRS : NONE
 * RETURNS   : NONE
 */
void Generate_Seeds();

/*
 * Function to test range of generated password
 * PARAMETRS : NONE
 * RETURNS   : NONE
 */
void Test_Randomness_LFSR();


#endif /* TEST_LFSR_H_ */
