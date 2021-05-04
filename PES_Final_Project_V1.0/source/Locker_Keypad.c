/*
 * Locker_Keypad.c - Source file containing implementation of 4 by 4 Keypad functionality
 *
 */

#include "Locker_Keypad.h"

#define FOUR_PIN_MASK 0xF                  //Mask to operate on 4 pins

char Entered_Char;                         //Variable to hold character pressed on keypad

uint8_t Start_User_Input=0;                //Variable to indicate user has started using keypad

uint8_t Char_Count=0;                      //Variable to hold number of keys pressed


//Array to hold characters corresponding to key press
const char Keypad_Character_Array[] = {
		'1', '2', '3', 'A',
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D'
};

unsigned char r = 0;                       //Variable to hold row number
unsigned char c = 0;                       //Variable to hold column number
unsigned char c_mask = 0;
unsigned char r_mask = 0;

uint32_t masking_state;

uint8_t i=0;

void Locker_key_Init() {

	//Enable clock to port C & D
	SIM->SCGC5 |=SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK;

	//Set GPIO functionality of pins & enable pull-up
	for(int i = 0; i <= 3; ++i) {
		PORTC->PCR[i] =PORT_PCR_MUX(1) | PORT_PCR_PE(1) ;

		PORTD->PCR[i] &= ~0xF0000;
		PORTD->PCR[i] = PORT_PCR_MUX(1) | PORT_PCR_PE(1) | 0xA0000;
	}

	//Set direction of PORTC(rows) as output & PORTD(columns) as input
	PTC->PDDR |= FOUR_PIN_MASK;
	PTD->PDDR &= ~(FOUR_PIN_MASK);

	//Clear all rows
	PTC->PCOR = FOUR_PIN_MASK;

	//Enable interrupt on PORTD
	NVIC_EnableIRQ(PORTD_IRQn);
	NVIC_SetPriority(PORTD_IRQn, 3);

	//Clear interrupt flag
	PORTD->ISFR = FOUR_PIN_MASK;
}


void Locker_key_Scan() {
	c = 0;
	for(r = 0; r <= 3; ++r) {
		r_mask = 1 << r;
		PTC->PDOR = ~r_mask & FOUR_PIN_MASK;                   //Clear one row at a time & set other rows high
		                                                       // i.e 1110,1101,1011 etc.

		 for(int k = 0 ; k< 25; k++)                           //add delay for debounce
		    	for(int j = 0; j < 5; j++);

		c_mask = ~PTD->PDIR & (FOUR_PIN_MASK);                 //Read Input on column pins & see which column is low & take complement
		if (c_mask) {
			unsigned char temp_mask = c_mask;

			//Map column mask value to column number

			switch(temp_mask){

			 case 1:c=0;break;
			 case 2:c=1;break;
			 case 4:c=2;break;
			 case 8:c=3;break;
			}
			break;
		}
	}
	PTC->PCOR = FOUR_PIN_MASK;                                //Clear all rows
}

char Locker_Find_Key() {


	unsigned char temp_index=0;
	char value;
	Locker_key_Scan();

	if (c_mask == 0)
	{
		return 0;
	}

	temp_index = r*4 + c;                                   //Calculate index into the keypad character array

	value = Keypad_Character_Array[temp_index];

	printf("%c ", value);

	return  value;                                         //Return pressed character



}

void PORTD_IRQHandler() {

	masking_state=__get_PRIMASK();                        //Enable critical section
    __disable_irq();

	Start_User_Input =1;                                  //Indicate user has started pressing keypad

    User_Input[i]=Locker_Find_Key();                      //Read pressed key
    i=(i+1)&7;

    Char_Count++;                                        //Increment input character count

	PORTD->ISFR = 0xF;                                   //Clear interrupt flag

	__set_PRIMASK(masking_state);
}





