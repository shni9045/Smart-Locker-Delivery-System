/*
 * Test_Password_Generation.c
 *
 */


#include "Test_Password_generation.h"

//Generate 5 different seeds using built-in rand() function
int seed0[5]={0};

//keep one seed constant
int seed1= 0x5454;

void Create_Seeds(){

	for (int i=0;i<5;i++){
		srand(i);
		seed0[i]=rand();
	}
}

void Test_OTP(){

	Create_Seeds();

	int number1=generate_random_value(seed0[0],seed1,4);
	int number2=generate_random_value(seed0[1],seed1,5);
	int number3=generate_random_value(seed0[2],seed1,6);
	int number4=generate_random_value(seed0[3],seed1,7);
	int number5=generate_random_value(seed0[4],seed1,8);


	UCUNIT_TestcaseBegin("Check Range of Generated Password");

	UCUNIT_CheckIsInRange(number1,0,65536);
	UCUNIT_CheckIsInRange(number2,0,65536);
	UCUNIT_CheckIsInRange(number3,0,65536);
	UCUNIT_CheckIsInRange(number4,0,65536);
	UCUNIT_CheckIsInRange(number5,0,65536);

	UCUNIT_TestcaseEnd();

	UCUNIT_WriteSummary();

}
