/*
 * password.c
 *
 *  Created on: Jul 20, 2019
 *      Author: M e t r o
 */

#include"password.h"




void Get_pass(uint8 *ptr_pass)
{
	LCD_goToRowColumn(1,5);
	for(uint8 i=0;i<5;i++)
	{
		_delay_ms(1000);
		ptr_pass[i]=Key_getPressedKey();
		_delay_ms(1000);




		LCD_displayCharacter('*');
	}
}
/*********************************************************************/

uint8 check_pass(uint8 *ptr_pass,uint8 *ptr_check_pass)
{
	for(uint8 i=0;i<5;i++)
	{
		if(ptr_pass[i] != ptr_check_pass[i])
			return ERROR;
	}
	return SUCCESS;
}

/**************************************************************************/

void send_pass(uint8 *ptr_pass)
{
	for(uint8 i=0;i<5;i++)
	{
		UART_sendByte(ptr_pass[i]);
		_delay_ms(500);/*for write in EEPROM */
	}
}

/*****************************************************************************/

void reciev_pass(uint8 *ptr_pass)
{
	for(uint8 i=0;i<5;i++)
	{
		ptr_pass[i]=UART_recieveByte();
	}
}

