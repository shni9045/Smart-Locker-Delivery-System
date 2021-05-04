/*
 * main_fsm.c - Source file containing implementation of Smart Locker state machine
 *
 */

#include "main_fsm.h"

//Macro definition for time limit(ticks) under which delivery agent has to input password
#define OTP_INPUT_TIMEOUT    (160)

char Password[8]={'0','0','0','0','0','0','0','0'};                       //Array to store generated password
char User_Input[8]={0};                                                   //Array to store keypad input

State_t Current_State = ENTER_PASSWORD;


/*
 * Application entry point.
 */
int main(void) {

	sysclock_init();                               //Initialize & Configure system clock

	Init_UART0();                                  //Initialize & Configure UART module

	init_systick();                               //Initialize & Configure systick timer

	Locker_key_Init();                            //Initialize keypad module

	init_led();                                   //Initialize LED module

	Turn_ON_LED(DOOR);

	printf("\n\r---------------------------------------- TESTING CBFIFO -------------------------\n\r");
	test_cbfifo();
	printf("\n\r---------------------------------------------------------------------------------\n\r");

	//Test randomness of LFSR method implementation
	Test_Randomness_LFSR();

	//Test range of generated random OTP
	Test_OTP();

	MMA8451Q_I2C_Init();							// MMA8451Q I2C initialization
	MMA8451Q_Interrupt_Config();                    // Enable & configure for MMA8451Q interrupts
	MMA8451Q_Init();				                // MMA8451Q initialization

	init_Buzzer_PWM(24000);                         // Initialize & Configure  PWM module for buzzer

	uint8_t End_User_Input=0;                       // Flag to end current user input read

	int seed1=0,seed2=0;

	int password_length=0;

	int decimal_password=0;

	printf("\n\r---------------------------------------------------------------------------------\n\r");
	printf("\n\r                     Welcome To Smart Locker Interface                           \n\r");
	printf("\n\r---------------------------------------------------------------------------------\n\r");

	printf("\n\rGenerate OTP For Delivery Agent using LFSR(Linear Feedback Shift register) Method\n\r");
	printf("\n\rEnter Password Length\n\r");
	password_length=Get_Password_Length();

	//Error check if user is inputting out of bound password length
	while(password_length <4 || password_length>8){
		printf("Please Re-Enter password_length as between 4 & 8 digits\n\r");
		password_length=Get_Password_Length();
	}

	printf("\n\rEnter Seed1 Value\n\r");
	seed1=Get_Seed_Value();

	printf("\n\rEnter Seed2 Value\n\r");
	seed2=Get_Seed_Value();

	//Generate random password using LFSR(Linear Feedback Shift Register method)
	decimal_password=generate_random_value(seed1,seed2,password_length);

	fragment_password(Password,decimal_password,password_length);

	display_password(Password,password_length);

    while(1) {

    	switch (Current_State){

    	case ENTER_PASSWORD:{

    		Turn_ON_LED(DOOR);
    		delay_ticks(10);

    		while (!End_User_Input){                         //Continue loop until END_USER_INPUT flag is set

    			while (!Start_User_Input);                   //Wait until Delivery agent presses first key


    			//Read keypad until timeout OTP_INPUT_TIMEOUT Occurs
    			//Read keypad until key presses equal to password length has occurred

    			ticktime_t time_now = now();
    			while ((now() < time_now + OTP_INPUT_TIMEOUT) && Char_Count<(password_length+1) ){


    			}

    			if (Check_User_Input(User_Input,Password,password_length)==1){
    				End_User_Input=1;                        //Set flag to exit this state
    			}
    			else {
    				printf("\n\rDelivery Agent Has Entered Wrong Password\n\r");
    			}
    			memset(User_Input,0,8);
    			i=0;
    		    Start_User_Input=0;
    		    Char_Count=0;
    		}


    		Current_State = ACTUATE_SOLENOID;
    		break;
    	}

    	case ACTUATE_SOLENOID:{

    		End_User_Input=0;
    		printf("\n\rDoor Is Opened\n\r");

    		Turn_OFF_LED(ULTRAVIOLET);
    		Turn_OFF_LED(DOOR);
    		delay_ticks(10);

    		Turn_ON_LED(SOLENOID);
    		delay_ticks(48);

    		Turn_OFF_LED(SOLENOID);
    		delay_ticks(48);

    		Current_State=DOOR_LOCKED;
    		break;
    	}

    	case DOOR_LOCKED:{

    		Turn_ON_LED(DOOR);
    		delay_ticks(10);

    		printf("\n\rDoor Is Locked\n\r");

    		Current_State=ACTUATE_UV_LED;
    		break;
    	}

    	case ACTUATE_UV_LED:{

    		printf("\n\rPackage Is Being Sanitized\n\r");

    		Turn_ON_LED(ULTRAVIOLET);
    		delay_ticks(10);

    		Current_State = ENTER_PASSWORD;
    		break;
    	}

    	}

    }
    return 0 ;
}







