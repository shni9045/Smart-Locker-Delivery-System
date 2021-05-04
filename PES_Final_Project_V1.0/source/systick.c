/*
 * systick.c -Source File Containing Implementation of Systick Timer
 *
 */


#include "systick.h"

ticktime_t current_ticks;                  //To hold number of ticks since startup

uint8_t reset_flag;                        //To indicate if timer has been reseted
ticktime_t reset_ticks;                    //To hold number of ticks since timer reset

void init_systick(){

	SysTick->LOAD =  0x16e35f;             //Assign Load register a value of 14,99,999 to generate interrupt every 62.5 mSec
	NVIC_SetPriority (SysTick_IRQn,3);
	SysTick->VAL=0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk ;
}

void SysTick_Handler(){
	current_ticks++;
	if (reset_flag==1) reset_ticks++;
}

ticktime_t now(){
	return current_ticks;
}

void delay_ticks(ticktime_t duration ){
	ticktime_t time_now= now();

	while (now() < time_now + duration){
		//__asm volatile ("NOP");
	}
}

float now_msec(){

	float temp;
	temp=current_ticks*62.5;   //To convert ticks to milliseconds

	return temp;
}

void reset_timer(){

	reset_flag=1;
	reset_ticks=0;

	SysTick->VAL=0;            //Write to VAL register to clear it

}

ticktime_t get_timer(){
	return reset_ticks;
}


