/*
 * Password_Process.h - Header file for implementation of password processing functionality
 *
 */

#ifndef PASSWORD_PROCESS_H_
#define PASSWORD_PROCESS_H_

#include <stdio.h>
#include <stdint.h>
#include "fsl_debug_console.h"


/*
 * Stores the received numerical password from user as characters into an array
 *
 * Parameters : 'Password' - Array into which character password is to be stored
 *              'decimal_password' - The generated password from LFSR method
 *              'length' - length of the password
 * Returns    :  NONE
 */
void fragment_password(char *Password,int decimal_password,int length);

/*
 * Compares keypad entered password and generated password
 *
 * Parameters : 'entered_array' - keypad entered password
 *              'expected_array' - The generated password from LFSR method
 *              'length' - length of the password
 * Returns    :  1 - if password is correct
 *               0 - if password is incorrect
 */
int Check_User_Input(char *entered_array,char *expected_array,int length);

/*
 * Displays password generated from LFSR method
 *
 *Parameters : 'Password' : Generated password to be displayed
 *             'length' - length of the password
 *Returns    : NONE
 */
void display_password(char *Password,int length);


#endif /* PASSWORD_PROCESS_H_ */
