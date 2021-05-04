/*
 * Indication_Led.h - Header file for implementation of various simulation LEDs
 *
 */

#ifndef INDICATION_LED_H_
#define INDICATION_LED_H_

#include "MKL25Z4.h"

/*Enumeration to hold different simulation LEDs*/

typedef enum{
	SOLENOID,DOOR,ULTRAVIOLET
}colour;

/*
 * Initializes LED Pins
 *
 * -Sends the Clock to the required GPIO PORT
 * -Sets up PORT Multiplexing
 * -Sets data direction to output
 *
 * Parameters : NONE
 * Returns    : NONE
 */
void init_led();

/*
 *Turns off LED of Specified Type
 *
 *Parameters : Type of LED which needs to be turned OFF
 *Returns    : NONE
 */
void Turn_OFF_LED(colour x);


/*
 *Turns ON LED of Specified Type
 *
 *Parameters : Type of LED which needs to be turned ON
 *Returns    : NONE
 */
void Turn_ON_LED(colour x);

#endif /* INDICATION_LED_H_ */
