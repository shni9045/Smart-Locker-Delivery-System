/*
 * Password_Process.c - Source file containing implementation of password processing functionality
 *
 */

#include "Password_Process.h"

void fragment_password(char *Password,int decimal_password,int length){

	int i=0;
	while (decimal_password!=0){
		Password[length-i-1]=(decimal_password % 10) + '0';
		decimal_password/=10;
		i++;
	}
}


int Check_User_Input(char *entered_array,char *expected_array,int length){

	uint8_t correct_chars=0;
	for (int i=0;i<length;i++){
		if (entered_array[i] == expected_array[i]){
			correct_chars++;
		}
	}

	if (correct_chars == length){
		return 1;
	}else return 0;

}



void display_password(char *Password,int length){

	printf("\n\rOTP For The Delivery Agent : ");
	for (int i=0;i<length;i++){
		printf("%c ",Password[i]);
	}
	printf("\n\r");
}

