/*
 * I2C.c
 *
 *  Created on: Jul 19, 2019
 *      Author: M e t r o
 */

#include"I2C.h"




void TWI_Init(void)
{
	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	TWBR = 0x02;
	TWSR = 0x00;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	       General Call Recognition: Off */
	TWAR = 0b00000010; // my address = 0x01 :)

	TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_Start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN)|( 1 << TWSTA);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

}



void TWI_Stop(void)
{

	TWCR = (1 << TWINT) |(1<<TWEN)|(1<<TWSTO);


}

void TWI_Write(uint8 data)
{
	TWDR = data;

	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) |(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_Read_With_ACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR =(1 << TWINT) |(1<<TWEA)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;

}

uint8 TWI_Read_With_NACK(void)
{
	TWCR =(1 << TWINT) |(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_Get_Status(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}







