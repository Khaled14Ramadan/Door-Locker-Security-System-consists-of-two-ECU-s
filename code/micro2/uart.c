/*
 * uart.c
 *
 *  Created on: Apr 30, 2019
 *      Author: Metro
 */
#include"uart.h"

void UART_init(UART_config *config_ptr)
{
	UCSRA = (1<<U2X);/*for Double the USART Transmission Speed */

	/* RXEN = 1  Receiver Enable
	 * TXEN = 1  Transmitter Enable
	 */
	UCSRB = (1<<RXEN)|(1<<TXEN);

	UCSRC = (1<<URSEL);/*URSEL = 1  Register Select*/
	UCSRC = (UCSRC & 0xBF) | ((config_ptr->mode)<<UMSEL);/*to specify UART_mode*/
	UCSRC = (UCSRC & 0xCF) | ((config_ptr->p_mode)<<UPM0);/*to specify parity mode and shift 4bits**/
	UCSRC = (UCSRC & 0xF7) | ((config_ptr->stop)<<USBS);/*to specify stop bit select */
	UCSRC = (UCSRC & 0xFC) | ((config_ptr->d_size)<<UCSZ0);/*to specify char_size*/


	UBRRH =(BAUD_PRESCALE>>8);
	UBRRL = BAUD_PRESCALE;
}
/***************************************************************************************************/

void UART_sendByte(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR=data;
}
/**************************************************************************************/

uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	return UDR;
}
/**********************************************************************************/

void UART_sendString(const uint8 *str)
{
	uint8 i=0;

	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;

	}
}
/*********************************************************************************************/

void UART_recieveString(uint8 *str)
{
	uint8 i=0;
	str[i]=UART_recieveByte();
	while(str[i] !='#')
	{
		i++;
		str[i] = UART_recieveByte();

	}
	str[i]='\0';

}
