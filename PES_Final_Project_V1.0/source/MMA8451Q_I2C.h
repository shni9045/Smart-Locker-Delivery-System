/*
 * MMA8451Q_I2C.h - Header file for implementation of I2C functionality for MMA8451Q
 *
 */

#ifndef MMA8451Q_I2C_H_
#define MMA8451Q_I2C_H_

#include "MKL25Z4.h"

/*
 *Initializes & configures I2C functionality
 *
 *Parameters : NONE
 *Returns    : NONE
 */
void MMA8451Q_I2C_Init(void);

/*
 *Reads from specified MMA8451Q register
 *
 *Parameters : slave address,register address
 *Returns    : NONE
 */
unsigned char MMA8451Q_I2C_Read(unsigned char slave, unsigned char reg);

/*
 *Writes to specified MMA8451Q register
 *
 *Parameters : slave address,register address,data to be written
 *Returns    : NONE
 */
void MMA8451Q_I2C_Write(unsigned char slave, unsigned char reg, unsigned char data);


#endif /* MMA8451Q_I2C_H_ */
