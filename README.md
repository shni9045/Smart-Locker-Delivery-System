

## General Info 
Project contains implementation of "Smart Locker System".This system allows user to generate a random OTP of size 4-8 digits using Linear Feedback Shift Register Method(LFSR) algorithm.This OTP is shared with the delivery agent.Upon entering the correct OTP on keypad the door actuation & ultraviolet package sanitization is carried out.

There is also a feature of tamper detection - if someone tries to tamper or move the locker ,the motion detection interrupt from accelerometer will sound a buzzer.

## Hardware Elements of Project

* keypad
* on board accelerometer MMA8451Q
* buzzer
* Indication LEDS

## Software Elements of Project

* State Machine
* keypad Interface
* Linear Feedback Shift Register Method(LFSR) to generate random numbers
* UART
* I2C for accelerometer
* PWM for Buzzer

## Testing Strategy of Project

* uCUnit framework for automated tests
* Manual testing for some modules


***
## Technologies
-MCUXpressoIDE Version -11.3.0<br/>
-FRDM-KL25Z Development board 
***
