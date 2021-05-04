/*
 * Test_LFSR.c
 *
 */

#include "Test_LFSR.h"

//Generate 5 different seeds using built-in rand() function
int seed[5]={0};

//keep one seed constant
int seed2= 0x234a;

void Generate_Seeds(){

	for (int i=0;i<5;i++){
		srand(i);
		seed[i]=rand();
	}
}


void Test_Randomness_LFSR(){

	Generate_Seeds();

	int number1=generate_random_value(seed[0],seed2,6);
	int number2=generate_random_value(seed[1],seed2,6);
	int number3=generate_random_value(seed[2],seed2,6);
	int number4=generate_random_value(seed[3],seed2,6);
	int number5=generate_random_value(seed[4],seed2,6);


	UCUNIT_Init();

	UCUNIT_TestcaseBegin("Check Randomness of LFSR");

	UCUNIT_CheckIsNotEqual(number2,number1);
	UCUNIT_CheckIsNotEqual(number3,number2);
	UCUNIT_CheckIsNotEqual(number4,number3);
	UCUNIT_CheckIsNotEqual(number5,number4);

	UCUNIT_TestcaseEnd();

	UCUNIT_WriteSummary();



}
