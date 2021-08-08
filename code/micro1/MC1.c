/*
 * khaled.c
 *
 *  Created on: Jun 22, 2019
 *      Author: M e t r o
 */

/*
 * calculator.c
 *
 *  Created on: May 8, 2019
 *      Author: Metro
 */
#include"lcd.h"
#include"keypad.h"
#include"uart.h"
#include"password.h"
#include"timer1.h"





/*********************************************************************/
int main(void)
{
	/* initialize UART */
	UART_config *uart_config;
	uart_config->mode=ASYNCHRONOUS;
	uart_config->p_mode=DISABLE;
	uart_config->stop=BIT_1;
	uart_config->d_size=BIT_8;

	UART_init(uart_config);
	/********************************************/

	/* initialize LCD */
	LCD_init();
	/****************************************/

	/* initialize tiimer 1 */
	timer1_oco();
	/******************************************/

	/* variables */

	uint8 pass1[5]={0}, pass2[5]={1};
	uint8 start=0 , choose=0 ,count_error=0;
	/* start : to add the new password */
	/* choose : to choose change password or open door */
	/* count_error : to count the number of error */


	/**************************************************/





	for(;;)
	{
		/* step 1 */
		if(start == 0)
		{

			LCD_displayString("enter new pass: ");
			Get_pass(pass1);

			while(Key_getPressedKey()!= 13);
			_delay_ms(500);

			LCD_clearScreen();
			LCD_displayString("re_enter pass : ");
			Get_pass(pass2);

			while(Key_getPressedKey()!= 13);
			_delay_ms(500);

		}

		/* two password are match*/
		if(check_pass(pass1,pass2)==SUCCESS)
		{
			start=1;
			LCD_clearScreen();
			LCD_displayString("SUCCESS");

			/* this function to send password to save in EEPROM */
			send_pass(pass1);
			/*********************************/

			/* step 2 */

			LCD_clearScreen();
			LCD_displayString("+ : change pass");
			LCD_goToRowColumn(1,0);
			LCD_displayString("- : open door");

			do
			{
				choose=Key_getPressedKey();
			}

			while(choose != '+' && choose != '-');


			/*this to order from MC2 to send password from EEPROM*/
			UART_sendByte(PLEASE_SEND_PASS);

			/*this part in two choose so write here */
			reciev_pass(pass1);

			pass2[0]=14;/* 14 can not write from user*/
			while( ( check_pass(pass1,pass2) == ERROR ) )
			{
				/* this check to buzzer */
				if(count_error == 3)
				{
					LCD_clearScreen();
					LCD_goToRowColumn(0,5);
					LCD_displayString("ERROR!!");

					count_error=-1;
					UART_sendByte(ERROR_PASS);
					/* this is time to work buzzer = 1 minute */

					check=0;//this to restart timer
					while( check < 60);
					//SREG &=~(1<<7);//to stop interrupt

				}
				/*******************************************************/



				LCD_clearScreen();
				LCD_displayString("enter the pass: ");
				Get_pass(pass2);

				while(Key_getPressedKey()!= 13);
				_delay_ms(500);
				count_error++;


			}

			/******************************************/

			if(choose =='-')
			{
				/* code to open door  */
				LCD_clearScreen();
				LCD_displayString("DOOR is open");
				UART_sendByte(OPEN_DOOR);
				/* this is time to motor clock wise */
				check=0;//this to restart timer
				while( check < 15);
				//check=0;//this to restart timer

				/* code to close door  */
				LCD_clearScreen();
				LCD_displayString("DOOR is close");
				//UART_sendByte(ANTI_CLOCK_WISE);
				/* this is time to motor ANTI_clock wise */
				//timer1_oco();
				while( check < 30);
				//SREG &=~(1<<7);//to stop interrupt

			}
			/* if to change that is repeat program from start */
			else
			{
				LCD_clearScreen();
				start = 0;

			}




		}

		else     /* two password not match*/
		{
			LCD_clearScreen();
			LCD_displayString("not match return write");
			_delay_ms(2500);
			LCD_clearScreen();
		}


	}
}
