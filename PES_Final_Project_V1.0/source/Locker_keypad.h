/*
 * Locker_keypad.h - Header file for implementation of 4 by 4 Keypad functionality
 *
 */

#ifndef LOCKER_KEYPAD_H_
#define LOCKER_KEYPAD_H_

#include "main_fsm.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "systick.h"

extern uint8_t i;

extern char Entered_Char;

extern uint8_t Start_User_Input;

extern uint8_t Char_Count;

/*
 *Configures & initializes pins connected to rows & columns of keypad
 *
 *Parameters : NONE
 *Returns    : NONE
 */
void Locker_key_Init();


/*
 *Finds the row & column of pressed key
 *
 *Parameters : NONE
 *Returns    : NONE
 */
void Locker_key_Scan();

/*
 *Maps the  row & column of pressed key to character array
 *
 *Parameters : NONE
 *Returns    : NONE
 */
char Locker_Find_Key();

#endif /* LOCKER_KEYPAD_H_ */
