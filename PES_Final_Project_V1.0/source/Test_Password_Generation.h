/*
 * Test_Password_Generation.h
 *
 */

#ifndef TEST_PASSWORD_GENERATION_H_
#define TEST_PASSWORD_GENERATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "uCUnit.h"
#include "LFSR_Random.h"

/*
 * Function to generate random seeds using builtin rand() function
 * PARAMETRS : NONE
 * RETURNS   : NONE
 */
void Create_Seeds();


/*
 * Function to test range of generated password
 * PARAMETRS : NONE
 * RETURNS   : NONE
 */
void Test_OTP();

#endif /* TEST_PASSWORD_GENERATION_H_ */
