/*
 * MMA8451Q_I2C.c - Source file containing implementation of I2C functionality for MMA8451Q
 *
 */

#include "MMA8451Q_I2C.h"


void MMA8451Q_I2C_Init(void)
{

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;		  //Enable clock  I2C0 module
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;		  //Enable clock  Port E module

	//Select I2C functionality for pins
	PORTE->PCR[24] = PORT_PCR_MUX(5);
	PORTE->PCR[25] = PORT_PCR_MUX(5);

	I2C0->F  = 0x14;
	I2C0->C1 = I2C_C1_IICEN_MASK;    		  // Enable module


}


unsigned char MMA8451Q_I2C_Read(unsigned char slave, unsigned char reg)
{
	unsigned char read_value;
	unsigned int j,k;

	I2C0->C1 |= I2C_C1_TX_MASK;										//Enable  transmitter mode
	I2C0->C1 |= I2C_C1_MST_MASK;								    //Transmit START condition

	I2C0->D = slave;										        //Transmit I2C device address & write bit
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}						// Wait until transmission
	I2C0->S |= I2C_S_IICIF_MASK;								    //Clear IICIF flag

	I2C0->D = reg;										            //Transmit register address
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}						// Wait until transmission
	I2C0->S |= I2C_S_IICIF_MASK;									//Clear IICIF flag

	I2C0->C1 |= I2C_C1_RSTA_MASK;									//Transmit repeated START condition

	I2C0->D = slave | 0x01;									        //Transmit I2C device address & read bit
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}						// Wait until transmission
	I2C0->S |= I2C_S_IICIF_MASK;								    //Clear IICIF flag

	I2C0->C1 &= (~I2C_C1_TX_MASK);									//Enable receiver mode

	I2C0->C1 |= I2C_C1_TXAK_MASK;

	read_value = I2C0->D ;
	for (j=0; j<5000; j++){};
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}
	I2C0->S |= I2C_S_IICIF_MASK;

	I2C0->C1 &= ~I2C_C1_MST_MASK;									//Transmit STOP condition
	I2C0->C1  &= ~I2C_C1_TX_MASK;									//Enable receiver mode
	read_value = I2C0->D ;

	for(k=0;k<50;k++);

	return read_value;
}


void MMA8451Q_I2C_Write(unsigned char slave, unsigned char reg, unsigned char data)
{
	unsigned int k;

	I2C0->C1 |= I2C_C1_TX_MASK;										//Enable transmitter mode
	I2C0->C1 |= I2C_C1_MST_MASK;									//Transmit START condition

	I2C0->D = slave;										        //Transmit I2C device address & write bit
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}						// Wait until transmission
	I2C0->S |= I2C_S_IICIF_MASK;									//Clear IICIF flag

	I2C0->D = reg;										            //Transmit register address
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}						// Wait until transmission
	I2C0->S |= I2C_S_IICIF_MASK;									//Clear IICIF flag

	I2C0->D = data;												    //Transmit data
	while((I2C0->S & I2C_S_IICIF_MASK)==0) {}						//Wait until transmission
	I2C0->S |= I2C_S_IICIF_MASK;								    //Clear IICIF flag

	I2C0->C1  &= ~I2C_C1_MST_MASK;									//Transmit STOP condition
	I2C0->C1  &= ~I2C_C1_TX_MASK;									//Enable receiver mode

	for(k=0;k<50;k++);
}



