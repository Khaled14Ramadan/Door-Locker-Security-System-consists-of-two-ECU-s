/*
 * ex1.c
 *
 *  Created on: Apr 2, 2019
 *      Author: Metro
 */


#include"eeprom.h"
#include"uart.h"
#include"timer1.h"


int main(){

	uint8 i=0 ,data;
	uint8 num[5]={0};
	uint8 ptr_pass[5]={0};


	/* initialize UART */
	UART_config *uart_config;
	uart_config->mode=ASYNCHRONOUS;
	uart_config->p_mode=DISABLE;
	uart_config->stop=BIT_1;
	uart_config->d_size=BIT_8;

	UART_init(uart_config);
	/********************************************/

	/* Init EEPROM */
	EEPROM_init();

	/*******************************************************/

	/* initialize tiimer 1 */
	timer1_oco();
	/******************************************/


	/*this pin to buzzer */
	DDRB |=(1<<PB0);
	PORTB &=~(1<<PB0);

	/*this two pins to motor*/
	DDRC |=(1<<PC4)|(1<<PC5);
	PORTC &=~(1<<PC4);
	PORTC &=~(1<<PC5);

	while(1){

		data=UART_recieveByte();
		if(data == ERROR_PASS)
		{
			/*this code for buzzer = 1 minute */
			PORTB |= (1 << PB0);
			check=0;//this to restart timer
			while( check < 60);
			//SREG &=~(1<<7);//to stop interrupt

			PORTB &= ~(1 << PB0);

			i=0;//to any time to change password
		}
		else if(data == OPEN_DOOR)
		{
			/*this code to motor*/
			PORTC |=(1<<PC4);
			PORTC &=~(1<<PC5);
			check=0;//this to restart timer
			while( check <= 15);
			//check=0;//this to restart timer

			PORTC &=~(1<<PC4);
			PORTC |=(1<<PC5);
			//timer1_oco();
			while( check <= 30);
			//SREG &=~(1<<7);//to stop interrupt


			PORTC &=~(1<<PC4);
			PORTC &=~(1<<PC5);

			i=0;//to any time to change password

		}
		else if(data == PLEASE_SEND_PASS)
		{
			/* to compare with password from user*/

			for(uint8 x=0;x<5;x++)
			{
				//UART_sendByte(num[i]);
				EEPROM_readByte( ADDRESS_EEPROM+x , ptr_pass+x);
				UART_sendByte(ptr_pass[x]);
			}

			i=0;//to any time to change password


		}

		else /* to recieve new pass*/
		{
			num[i]=data;

			EEPROM_writeByte(ADDRESS_EEPROM+i,num[i]);
			i++;
			_delay_ms(500);
		}


	}
}
