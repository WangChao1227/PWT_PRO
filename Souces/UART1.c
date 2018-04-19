
/*
 * UART.c
 *
 *  Created on: Dec 18, 2013
 *      Author: B46911
 */
#include "UART.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/
pt2FuncU8 Uart_Callback;//void(*Uart_Callback)(UINT8);


/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/
void UART1_IRQHandler (void);

/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/


/**********************************************************************************************
* Global functions
**********************************************************************************************/


/***********************************************************************************************
*
* @brief    Uart_Init - Initalizes the Uart2 to run at 9600 bauds assuming bus clock of 20Mhz
* @param    none
* @return   none
*
************************************************************************************************/  
void UART_Init()
{
	SIM_SCGC |=  SIM_SCGC_UART1_MASK;		/* Enable bus clock in UART1*/
	UART1_BDH = 0;							/* One stop bit*/
	UART1_BDL = 128;						/* Baud rate at 9600*/
	UART1_C1  = 0;							/* No parity enable,8 bit format*/
	UART1_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	UART1_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	UART1_C2 |= UART_C2_RIE_MASK;			/* Enable Receiver interrupts*/
	

}

/***********************************************************************************************
*
* @brief    Uart_SetCallback - Set a callback function to execute when a byte is received on the Uart2
* @param    pointer to function with an UINT8 argument
* @return   none
*
************************************************************************************************/  
void Uart_SetCallback(pt2FuncU8 ptr)
{
	Uart_Callback = ptr;//Uart_Callback == 	void(*ptr)(UINT8) wc
}


/***********************************************************************************************
*
* @brief    Uart_SendChar - Send a single byte on Uart2 
* @param    byte to send
* @return   none
*
************************************************************************************************/  
void Uart_SendChar(UINT8 send)
{
	while((UART1_S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/
	(void)UART1_S1;								/* Read UART2_S1 register*/
	UART1_D=send;								/* Send data*/
}

/***********************************************************************************************
*
* @brief    Uart_GetChar - Retrieve the received char from the Uart2 buffer (should be called from Interrupt) 
* @param    none
* @return   received byte
*
************************************************************************************************/  
UINT8 Uart_GetChar()
{
	
  UINT8 recieve;
  while(( UART1_S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/
  (void) UART1_S1;								/* Read UART2_S1 register*/
  recieve= UART1_D;								/* Read received data*/
  return recieve;

} 

/***********************************************************************************************
*
* @brief    UART2_IRQHandler - Uart2 reception interrupt, calls the user defined callback function 
* @param    none
* @return   none
*
************************************************************************************************/
void UART1_IRQHandler()
{

	(void)UART1_S1;		/* Clear reception flag mechanism*/
	Uart_Callback(Uart_GetChar());

}
