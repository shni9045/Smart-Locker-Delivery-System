/*
 * User_Input.h - Header file for implementation of functionality of getting numerical input from User
 *
 */

#ifndef USER_INPUT_H_
#define USER_INPUT_H_

#include <stdio.h>
#include "UART.h"

/*
 * Receives and stores HEX Seed Input of algorithm from the user over UART
 *
 *Parameters : NONE
 *Returns    : Integer value of Seed Input
 */
int Get_Seed_Value();

#include "UART.h"

/*
 * Receives and stores DECIMAL Password Length from the user over UART
 *
 *Parameters : NONE
 *Returns    : Integer value of Password Length
 */
int Get_Password_Length();

#endif /* USER_INPUT_H_ */
