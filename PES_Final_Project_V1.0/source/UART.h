/*
 * UART.h -Header file for implementation of UART functionality
 *
 */

#ifndef UART_H_
#define UART_H_


#include <stdio.h>
#include <stdint.h>
#include "MKL25Z4.h"
#include "CBFIFO.h"



/*
 * Function to initialize UART0 Module by setting uart parameters
 * PARAMETERS : NONE
 * RETURNS    : NONE
 */
void Init_UART0();

/*
 * Function to read a user input over UART
 * PARAMETERS : s - location to store read string
 * RETURNS    : number of characters inputted
 */
int getstr(char *s);


#endif /* UART_H_ */
