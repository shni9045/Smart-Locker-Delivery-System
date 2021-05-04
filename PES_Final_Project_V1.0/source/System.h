/*
 * System.h
 *
 *  Created on: 03-May-2021
 *      Author: Shrikant
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/* function prototypes */
void System_Init(void);
void System_Shutdown(void);
void System_exit(int val);
void System_Safestate(void);
void System_Recover(void);
void System_WriteString(char * msg);
void System_WriteInt(int n);


#endif /* SYSTEM_H_ */
