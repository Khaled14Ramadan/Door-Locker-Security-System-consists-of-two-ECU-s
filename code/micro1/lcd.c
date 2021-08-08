/*
 * lcd.c
 *
 *  Created on: Apr 23, 2019
 *      Author: Metro
 */

#include"lcd.h"

/*this function initialize all ports to LCD */
void LCD_init(void)
{
	CONTROLL_PORT_DIR |=(1<<RS)|(1<<RW)|(1<<E);

#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
	DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
#else
	DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
#endif     //end if for #IFDEF
	LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
#elif (DATA_BITS_MODE == 8)
	DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}
/*********************************************************************************************/

/*this function to send command to LCD*/
void LCD_sendCommand(uint8 command)
{
	/*this part must found in code */
	CLEAR_BIT(CONTROLL_PORT_OUT,RS);
	CLEAR_BIT(CONTROLL_PORT_OUT,RW);
	_delay_ms(1);
	SET_BIT(CONTROLL_PORT_OUT,E);/* Enable LCD E=1 */
	_delay_ms(1);

	/*this part if work 4-bits mode */
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS    /*work the last 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0x0F) |  ( command & 0xF0);/* move most 4_bit in command */
#else            /*work the first 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0xF0) | ( ( command & 0xF0) >>4) ;/* move most 4_bit in command */
#endif
	_delay_ms(1);
	CLEAR_BIT(CONTROLL_PORT_OUT,E);/* disable LCD E=0 to save most 4_bits*/
	_delay_ms(1);
	SET_BIT(CONTROLL_PORT_OUT,E);/* Enable LCD E=1 */
	_delay_ms(1);

#ifdef UPPER_PORT_PINS   /*work the last 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0x0F) | ( ( command & 0x0F) << 4) ;/* move least 4_bit in command */
#else           /*work the first 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0xF0) |  ( command & 0x0F);/* move least 4_bit in command */
#endif

	/*this part if work 8-bits mode */
#elif (DATA_BITS_MODE == 8)
	DATA_PORT_out = command;
#endif

	/*this part must found in code */
	_delay_ms(1);
	CLEAR_BIT(CONTROLL_PORT_OUT,E);/* disable LCD E=0 to save least 4_bits*/
	_delay_ms(1);

}
/****************************************************************************************/

/* this function to send characters to print on screen*/
void LCD_displayCharacter(uint8 data)
{

	/*this part must found in code */
	SET_BIT(CONTROLL_PORT_OUT,RS);
	CLEAR_BIT(CONTROLL_PORT_OUT,RW);
	_delay_ms(1);
	SET_BIT(CONTROLL_PORT_OUT,E);/* Enable LCD E=1 */
	_delay_ms(1);

	/*this part if work 4-bits mode */
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS    /*work the last 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0x0F) | ( data & 0xF0) ;/* move most 4_bit in data */
#else            /*work the first 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0xF0) | ( ( data & 0xF0) >>4) ;/* move most 4_bit in data */
#endif
	_delay_ms(1);
	CLEAR_BIT(CONTROLL_PORT_OUT,E);/* disable LCD E=0 to save most 4_bits*/
	_delay_ms(1);
	SET_BIT(CONTROLL_PORT_OUT,E);/* Enable LCD E=1 */
	_delay_ms(1);

#ifdef UPPER_PORT_PINS   /*work the last 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0x0F) | ( ( data & 0x0F) << 4) ;/* move least 4_bit in data */
#else           /*work the first 4_bit port*/
	DATA_PORT_out = (DATA_PORT_out & 0xF0) | ( data & 0x0F) ;/* move least 4_bit in data */
#endif

	/*this part if work 8-bits mode */
#elif (DATA_BITS_MODE == 8)
	DATA_PORT_out = data;
#endif

	/*this part must found in code */
	_delay_ms(1);
	CLEAR_BIT(CONTROLL_PORT_OUT,E);/* disable LCD E=0 to save least 4_bits*/
	_delay_ms(1);
}
/*****************************************************************************************/

/*this function to print string on screen */
void LCD_displayString(const uint8 *str)
{
	uint8 i=0;

	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}
/*******************************************************************************************/

/*this to function to move cursor to the specific position*/
void LCD_goToRowColumn(uint8 row , uint8 col)
{
	uint8 address;

	switch(row)
	{
	case 0:
		address=col;
		break;

	case 1:
		address = 0x40+col;
		break;

	case 2:
		address= 0x10 + col;
		break;

	case 3:
		address= 0x50 + col;
		break;
	}

	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}
/***********************************************************************************************/

/*this to print string on screen in the specific position*/
void LCD_displayStringRowColumn(uint8 row , uint8 col , const uint8 *str)
{
	LCD_goToRowColumn(row , col);
	LCD_displayString(str);
}
/***********************************************************************************/

/*this function to clear screen*/
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}
/*******************************************************************************/

/*this function to convert interg to string*/
void LCD_intgerToString(int data)
{
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_displayString(buff);
}
