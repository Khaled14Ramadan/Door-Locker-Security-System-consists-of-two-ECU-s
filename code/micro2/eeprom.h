/*
 * eeprom.h
 *
 *  Created on: Jul 19, 2019
 *      Author: M e t r o
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include"I2C.h"




#define ERROR 0
#define SUCCESS 1
#define ERROR_PASS 0XFF
#define OPEN_DOOR 0XAA
#define PLEASE_SEND_PASS 0XBB
#define ADDRESS_EEPROM 0X0311

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EEPROM_H_ */
