/*
 * uart.h
 *
 *  Created on: Apr 30, 2019
 *      Author: Metro
 */

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

typedef enum
{
	ASYNCHRONOUS,SYNCHRONOUS
}mode_select;
typedef enum
{
	DISABLE,RESERVED,EVEN,ODD
}parity_mode;

typedef enum
{
	BIT_1,BIT_2
}stop_bit;
typedef enum
{
	BIT_5,BIT_6,BIT_7,BIT_8
}char_size;

typedef struct
{
	mode_select mode;
	parity_mode p_mode;
	stop_bit stop;
	char_size d_size;
}UART_config;




/* prototype functions */

void UART_init(UART_config *config_ptr);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *str);
void UART_recieveString(uint8 *str);








#endif /* UART_H_ */
