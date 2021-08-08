/*
 * I2C.h
 *
 *  Created on: Jul 19, 2019
 *      Author: M e t r o
 */

#ifndef I2C_H_
#define I2C_H_

#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8 data);
uint8 TWI_Read_With_ACK(void);
uint8 TWI_Read_With_NACK(void);
uint8 TWI_Get_Status(void);


#endif /* I2C_H_ */
