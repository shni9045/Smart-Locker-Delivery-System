/*
 * uart.c - Source file containing implementation of UART functionality
 *
 */

#include <UART.h>

//Transmit & Receive Buffer Instantation

cbfifo tx_buffer={.write=0,.read=0};
cbfifo rx_buffer={.write=0,.read=0};

/*Macro Definition for UART 0 Baud rate */
#define baud_rate 38400

/*Macro Definition for UART 0 Data Size
 * Assign 8 for 8-Bit data mode,9 for 9-bit data mode */
#define data_size 8

/*Macro Definition to enable/disable UART 0 Parity
 * Assign 0 to disable,1 to enable */
#define parity 0

/*Macro Definition for UART 0 Stop bit number
 * Assign 1 for 1 stop bit,2 for 2 stop bit */
#define stop_bits 2


#define BUS_CLOCK (24e6)                              //Macro definition for UART Clock
#define UART_OVERSAMPLE_RATE (16)                     //Macro definition for UART Sampling Rate


void Init_UART0() {

	    uint16_t sbr;

		// Enable clock gating for UART0 and Port A
		SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

		// Set UART clock to 48 MHz clock
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

		// Set pins to UART0 Rx and Tx
		PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
		PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

		// Set baud rate and oversampling ratio
		sbr = (uint16_t)((BUS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
		UART0->BDH &= ~UART0_BDH_SBR_MASK;
		UART0->BDH |= UART0_BDH_SBR(sbr>>8);
		UART0->BDL = UART0_BDL_SBR(sbr);
		UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

		// Disable interrupts for RX active edge and LIN break detect, select  stop bits
		UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(stop_bits-1) | UART0_BDH_LBKDIE(0);

		// Don't enable loopback mode, use 8 data bit mode, don't use parity
		UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(data_size-8) | UART0_C1_PE(parity);
		// Don't invert transmit data, don't enable interrupts for errors
		UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
				| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

		// Clear error flags
		UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
										UART0_S1_FE_MASK | UART0_S1_PF_MASK;

		// Send LSB first, do not invert received data
		UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

		// Enable UART receiver and transmitter
		UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);
		NVIC_EnableIRQ(UART0_IRQn);

		// Enable receive interrupts
		UART0->C2 |= UART_C2_RIE(1);
		UART0->C2 |= UART_C2_TIE(1);

}



/*
 * Returns one character from stdin
 * Returns -1 on error or if no data is available
 *
 */

int __sys_readc(void)
{
	uint8_t deq[5];

	if (!buf_isempty(&rx_buffer)){            //Check if receive buffer is not empty

		cbfifo_dequeue(&rx_buffer,deq,1);     //Dequeue next element from receive buffer
		return deq[0];

	}
	return -1;
}

/*
 * Writes Specified bytes to stdout or stderr
 * Returns -1 on error or 0 on success
 *
 */
int __sys_write(int handle,char *buf,int siz){

	int count=0;


	while((255-cbfifo_length(&tx_buffer)<siz));         // wait for space to open up

	count=cbfifo_enqueue(&tx_buffer,buf,siz);           //Enqueue character to be transmitted in transmit buffer

	UART0->C2 |=UART0_C2_TIE_MASK;                      //Enable transmit interrupt

	if (count==-1){                                     //Check if enqueue operation returns error
		return -1;
	}

	return 0;
}

//Uart 0 Interrupt Handler

void UART0_IRQHandler(void) {

	uint8_t byte;

	const uint8_t error_flags= UART_S1_OR_MASK | UART_S1_NF_MASK| UART_S1_FE_MASK | UART_S1_PF_MASK;

	//Check for UART0 error flags

	if (UART0->S1 & error_flags){
		UART0->S1 |=error_flags;
		byte = UART0->D;
	}

	//If a character is received

	if (UART0->S1 & UART0_S1_RDRF_MASK) {

		char ch[5];
		ch[0] = UART0->D;                                 //Store received character

		if (!buf_isfull(&rx_buffer)) {                    //Check if receive buffer has space

			if (ch[0]!='\b' || ch[0]!=127){

			cbfifo_enqueue(&rx_buffer, ch,1);             //Enqueue received character in receive buffer

			cbfifo_enqueue(&tx_buffer, ch,1);             //Enqueue received character in transmit buffer to echo it
			}
		}

	}

	if (  (UART0->S1 & UART0_S1_TDRE_MASK) ) {   // tx buffer empty

		// Dequeue & send another character

		uint8_t deq[5];
		if (!buf_isempty(&tx_buffer)) {                  //Check if transmit buffer has characters to transmit
			 cbfifo_dequeue(&tx_buffer,deq,1);           //Dequeue next element from transmit buffer
			 UART0->D =deq[0];                           //Transmit the dequeued element
		}

		else {
			UART0->C2 &=~UART0_C2_TIE_MASK;             // since queue is empty disable transmit interrupt
		}
	}
}

int getstr(char *s){

	int i=0;

	char *copy=s;

	while(buf_isempty(&rx_buffer));
	*copy=getchar();

	while(*copy!='\r' )                                // run loop until user presses enter
	{
		copy++;
		i++;
		while(buf_isempty(&rx_buffer));
		*copy=getchar();
	}

	return i;
}





