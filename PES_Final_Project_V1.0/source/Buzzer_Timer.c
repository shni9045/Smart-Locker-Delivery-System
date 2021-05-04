/*
 * Buzzer_Timer.c - Source file containing implementation of PWM Control of Buzzer
 *
 */

#include "Buzzer_Timer.h"

void init_Buzzer_PWM(uint16_t period){


	// Blue FTM0_CH1, Mux Alt 4
	// Set pin to FTMs
	PORTE->PCR[20] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[20] |= PORT_PCR_MUX(3);


	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1));


	TPM1->MOD = period-1;                 //load the counter and mod

	TPM1->SC =  TPM_SC_PS(1);             //set TPM count direction to up with a divide by 2 prescaler

	TPM1->CONF |= TPM_CONF_DBGMODE(3);   // Continue operation in debug mode

	// Set channel 1 to edge-aligned low-true PWM
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	TPM1->CONTROLS[0].CnV = 200;           // Set initial duty cycle

}

void Ring_Buzzer(void){

	TPM1->SC |= TPM_SC_CMOD(1);          // Start TPM

}
