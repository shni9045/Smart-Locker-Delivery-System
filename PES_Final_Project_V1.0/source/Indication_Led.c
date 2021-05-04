/*
 * Indication_Led.c - Source file containing implementation of various simulation LEDs
 *
 *
 */


#include "Indication_Led.h"

//Macro definitions for solenoid actuation simulation LED

#define SOLENOID_LED_GPIO_PORT GPIOB
#define SOLENOID_LED_PIN 10
#define SOLENOID_LED_SCGC5_MASK SIM_SCGC5_PORTB_MASK

#define SOLENOID_LED_PIN_CTRL_REG PORTB->PCR[SOLENOID_LED_PIN]

#define SOLENOID_LED_DATA_DIR_REG PTB->PDDR
#define SOLENOID_LED_DATA_DIR_MASK  (1<<SOLENOID_LED_PIN)

#define SOLENOID_LED_SET_REG GPIOB->PCOR
#define SOLENOID_LED_SET_MASK (1<<SOLENOID_LED_PIN)

#define SOLENOID_LED_CLEAR_REG GPIOB->PSOR
#define SOLENOID_LED_CLEAR_MASK (1<<SOLENOID_LED_PIN)

//Macro definitions for Door state simulation LED

#define DOOR_LED_GPIO_PORT GPIOB
#define DOOR_LED_PIN 9
#define DOOR_LED_SCGC5_MASK SIM_SCGC5_PORTB_MASK

#define DOOR_LED_PIN_CTRL_REG PORTB->PCR[DOOR_LED_PIN]

#define DOOR_LED_DATA_DIR_REG PTB->PDDR
#define DOOR_LED_DATA_DIR_MASK  (1<<DOOR_LED_PIN)

#define DOOR_LED_SET_REG GPIOB->PCOR
#define DOOR_LED_SET_MASK (1<<DOOR_LED_PIN)

#define DOOR_LED_CLEAR_REG GPIOB->PSOR
#define DOOR_LED_CLEAR_MASK (1<<DOOR_LED_PIN)


//Macro definitions for  UltraViolet light simulation LED

#define ULTRAVIOLET_LED_GPIO_PORT GPIOB
#define ULTRAVIOLET_LED_PIN 11
#define ULTRAVIOLET_LED_SCGC5_MASK SIM_SCGC5_PORTB_MASK

#define ULTRAVIOLET_LED_PIN_CTRL_REG PORTB->PCR[ULTRAVIOLET_LED_PIN]

#define ULTRAVIOLET_LED_DATA_DIR_REG PTB->PDDR
#define ULTRAVIOLET_LED_DATA_DIR_MASK  (1<<ULTRAVIOLET_LED_PIN)

#define ULTRAVIOLET_LED_SET_REG GPIOB->PCOR
#define ULTRAVIOLET_LED_SET_MASK (1<<ULTRAVIOLET_LED_PIN)

#define ULTRAVIOLET_LED_CLEAR_REG GPIOB->PSOR
#define ULTRAVIOLET_LED_CLEAR_MASK (1<<ULTRAVIOLET_LED_PIN)

void init_led(){

	SIM->SCGC5 |= SOLENOID_LED_SCGC5_MASK;                                    //Provide clock to Port B

	SOLENOID_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;                          //Set pin functionality as GPIO
	SOLENOID_LED_PIN_CTRL_REG |= PORT_PCR_MUX(1);
	SOLENOID_LED_DATA_DIR_REG |= SOLENOID_LED_DATA_DIR_MASK;                  //Set  direction as Output

	DOOR_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;                              //Set pin functionality as GPIO
	DOOR_LED_PIN_CTRL_REG |= PORT_PCR_MUX(1);
	DOOR_LED_DATA_DIR_REG |= DOOR_LED_DATA_DIR_MASK;                          //Set  direction as Output

	ULTRAVIOLET_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;                       //Set pin functionality as GPIO
	ULTRAVIOLET_LED_PIN_CTRL_REG |= PORT_PCR_MUX(1);
	ULTRAVIOLET_LED_DATA_DIR_REG |= ULTRAVIOLET_LED_DATA_DIR_MASK;           //Set  direction as Output


}

void Turn_OFF_LED(colour x){

	if (x==SOLENOID){
		SOLENOID_LED_SET_REG |= SOLENOID_LED_SET_MASK;
	}

	else if (x==DOOR){
		DOOR_LED_SET_REG |= DOOR_LED_SET_MASK;
	}

	else if (x==ULTRAVIOLET){
		ULTRAVIOLET_LED_SET_REG |= ULTRAVIOLET_LED_SET_MASK;
	}


}



void Turn_ON_LED(colour x){

	if (x==SOLENOID){
		SOLENOID_LED_CLEAR_REG |= SOLENOID_LED_CLEAR_MASK;
	}

	else if (x==DOOR){
		DOOR_LED_CLEAR_REG |= DOOR_LED_CLEAR_MASK;
	}

	else if (x==ULTRAVIOLET){
		ULTRAVIOLET_LED_CLEAR_REG |= ULTRAVIOLET_LED_CLEAR_MASK;
	}


}





