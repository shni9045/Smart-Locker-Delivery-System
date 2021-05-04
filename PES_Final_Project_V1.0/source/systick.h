/*
 * systick.h - Header File for Implementation of Systick Timer
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdio.h>
#include <stdint.h>
#include "MKL25Z4.h"

typedef uint32_t ticktime_t;

/*
 * Initializes SysTick Timer
 * - Enables the module,provides clock
 * - Enables interrupt & sets priority
 * - Loads counter value
 * PARAMETERS : NONE
 * RETURNS    : NONE
 *
 */

void init_systick();

/*
 * Gives time since startup
 * PARAMETRS : NONE
 * RETURNS   : time in number of ticks
 */

ticktime_t now();

/*  Function to generate delay in number of ticks
 *
 *  PARAMETERS : Ticks for which delay is to be generated
 *  RETURNS    : NONE
 *
 */
void delay_ticks(ticktime_t duration );

/*
 * Gives time since startup
 * PARAMETERS : NONE
 * RETURNS    : time in milliseconds
 */

float now_msec();

/*
 * Resets SysTick timer to 0
 * PARAMETERS : NONE
 * RETURN     : NONE
 *
 */

void reset_timer();

/*
 * Give time since last Systick timer reset
 * PARAMETERS : NONE
 * RETURNS    : time in number of ticks
 *
 */

ticktime_t get_timer();



#endif /* SYSTICK_H_ */
