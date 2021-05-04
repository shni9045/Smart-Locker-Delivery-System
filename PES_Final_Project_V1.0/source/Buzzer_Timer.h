/*
 * Buzzer_Timer.h - Header file for implementation of PWM Control of Buzzer
 *
 */

#ifndef BUZZER_TIMER_H_
#define BUZZER_TIMER_H_


#include "MKL25Z4.h"

/*
 * Initializes PWM Pins
 *
 *-Sends the clock to the required GPIO Ports
 *-Sets up port multiplexing for PWM functionality
 *-Loads TPM Module registers to generate required PWM
 *
 *PARAMETRES : Period of the PWM
 *RETURNS    : NONE
 */
void init_Buzzer_PWM(uint16_t period);

/*
 * Starts the TPM Module and subsequently plays the Buzzer connected on this Pin
 *
 *
 *PARAMETRES : NONE
 *RETURNS    : NONE
 */
void Ring_Buzzer(void);



#endif /* BUZZER_TIMER_H_ */
