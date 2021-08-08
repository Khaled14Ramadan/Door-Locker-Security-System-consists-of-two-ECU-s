/*
 * keypad.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Metro
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


#define N_COL 4
#define N_ROW 4

#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_OUT PORTA //for second 3 or 4 bit for columns
#define KEYPAD_PORT_IN PINA  //for first 4_bit for rows

uint8 Key_getPressedKey(void);



#endif
