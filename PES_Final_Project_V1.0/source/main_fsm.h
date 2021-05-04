/*
 * main_fsm.h - Header file for  implementation of Smart Locker state machine
 *
 */

#ifndef MAIN_FSM_H_
#define MAIN_FSM_H_


#include <stdio.h>
#include <stdint.h>
#include "peripherals.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Locker_keypad.h"
#include "sysclock.h"
#include "systick.h"
#include "UART.h"
#include "User_Input.h"
#include "Password_Process.h"
#include "LFSR_Random.h"
#include "Indication_Led.h"
#include "MMA8451Q.h"
#include "MMA8451Q_I2C.h"
#include "Buzzer_Timer.h"
#include "Test_LFSR.h"
#include "Test_Password_Generation.h"
#include "test_cbfifo.h"


//Enumeration for describing various FSM states
typedef enum {
	ENTER_PASSWORD = 0,
	ACTUATE_SOLENOID = 1,
	DOOR_LOCKED =2,
	ACTUATE_UV_LED = 3
}State_t;

extern char User_Input[8];

#endif /* MAIN_FSM_H_ */
