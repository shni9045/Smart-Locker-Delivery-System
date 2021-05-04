/*
 * MMA84541Q.c - Source file containing implementation of core MMA8451Q functions
 *
 */


#include "MMA8451Q.h"



#define MMA8451Q_I2C_ADDRESS   0x3A		// Macro definition for MMA8451Q 8-bit I2C address


// Macro definition for MMA8451Q Registers

#define STATUS_REG            0x00		// STATUS Register

#define SYSMOD_REG            0x0B    	// SYSMOD System Mode Register
#define INT_SOURCE_REG        0x0C    	// INT_SOURCE System Interrupt Status Register
#define WHO_AM_I_REG          0x0D    	// WHO_AM_I Device ID Register
#define XYZ_DATA_CFG_REG      0x0E    	// XYZ_DATA_CFG Sensor Data Configuration Register


#define FF_MT_CFG_REG         0x15    	// FF_MT_CFG Freefall and Motion Configuration Register
#define FF_MT_SRC_REG         0x16    	// FF_MT_SRC Freefall and Motion Source Register
#define FT_MT_THS_REG         0x17    	// FF_MT_THS Freefall and Motion Threshold Register
#define FF_MT_COUNT_REG       0x18    	// FF_MT_COUNT Freefall Motion Count Register


#define CTRL_REG1             0x2A    	// CTRL_REG1 System Control 1 Register
#define CTRL_REG2             0x2B    	// CTRL_REG2 System Control 2 Register
#define CTRL_REG3             0x2C    	// CTRL_REG3 Interrupt Control Register
#define CTRL_REG4             0x2D    	// CTRL_REG4 Interrupt Enable Register
#define CTRL_REG5             0x2E    	// CTRL_REG5 Interrupt Configuration Register




void MMA8451Q_Init (void)
{
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, CTRL_REG1, 0x00);				// Standby mode
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, XYZ_DATA_CFG_REG, 0x00);			// +/-2g range -> 1g = 16384/4 = 4096 counts
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, FF_MT_CFG_REG, 0xD8);			// Motion flag latched, X axis enabled for motion detection
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, FT_MT_THS_REG , 0x08);			// Motion threshold = 0.5g (0.5g / 0.063g/count = ~8counts)
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, FF_MT_COUNT_REG , 0x0A);			// Debounce counter set to 100ms (100ms / 10ms = 10counts) */
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, CTRL_REG3, 0x00);				// Push-pull, active low interrupts */
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, CTRL_REG4, 0x04);				// Enable Motion interrupt */
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, CTRL_REG5, 0x04);				// Motion interrupt routed to INT1 - PTA14 */
	MMA8451Q_I2C_Write(MMA8451Q_I2C_ADDRESS, CTRL_REG1, 0x19);				// ODR = 100Hz, Active mode */
}

void MMA8451Q_Interrupt_Config(){

	//Enable clock to PortA
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[14] |= (0|PORT_PCR_ISF_MASK|
						  PORT_PCR_MUX(0x1)|	// Select GPIO functionality
						  PORT_PCR_IRQC(0xA));	// Enable falling edge interrupts

	// Enable PORTA interrupt on NVIC
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_SetPriority(PORTA_IRQn, 3);
}


void PORTA_IRQHandler()
{
	PORTA->PCR[14] |= PORT_PCR_ISF_MASK;		// Clear the interrupt flag

	Ring_Buzzer();                              // Actuate buzzer

}




