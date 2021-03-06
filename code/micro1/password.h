/*
 * password.h
 *
 *  Created on: Jul 20, 2019
 *      Author: M e t r o
 */

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include "std_types.h"
#include"lcd.h"
#include"keypad.h"
#include"util/delay.h"
#include"uart.h"


#define ERROR 0
#define SUCCESS 1
#define ERROR_PASS 0XFF
#define OPEN_DOOR 0XAA
#define PLEASE_SEND_PASS 0XBB

void Get_pass(uint8 *ptr_pass);


uint8 check_pass(uint8 *ptr_pass,uint8 *ptr_check_pass);

void send_pass(uint8 *ptr_pass);

void reciev_pass(uint8 *ptr_pass);

#endif /* PASSWORD_H_ */
