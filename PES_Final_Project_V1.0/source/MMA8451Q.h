/*
 * MMA8451Q.h - Header file for implementation of core MMA8451Q functions
 *
 */

#ifndef MMA8451Q_H_
#define MMA8451Q_H_

#include "MKL25Z4.h"
#include "MMA8451Q_I2C.h"
#include "Buzzer_Timer.h"

/*
 *Initializes & configures MMA8451Q
 *
 *Parameters : NONE
 *Returns    : NONE
 */
void MMA8451Q_Init (void);


/*
 *Enables & configures interrupts for MMA8451Q
 *
 *Parameters : NONE
 *Returns    : NONE
 */
void MMA8451Q_Interrupt_Config();

#endif /* MMA8451Q_H_ */
