/*
 * lcd.h
 *
 *  Created on: Apr 24, 2019
 *      Author: Metro
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */


/* LCD HW Pins */
#define CONTROLL_PORT_DIR DDRD
#define CONTROLL_PORT_OUT PORTD
#define RS PD4
#define RW PD5
#define E PD6
#define DATA_PORT_DIR DDRC
#define DATA_PORT_out PORTC

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80


void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const uint8 *str);
void LCD_goToRowColumn(uint8 row , uint8 col);
void LCD_displayStringRowColumn(uint8 row , uint8 col , const uint8 *str);
void LCD_clearScreen(void);
void LCD_intgerToString(int data);

#endif /* LCD_H_ */
