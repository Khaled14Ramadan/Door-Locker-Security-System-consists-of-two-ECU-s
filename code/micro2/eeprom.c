/*
 * eeprom.c
 *
 *  Created on: Jul 19, 2019
 *      Author: M e t r o
 */

#include"eeprom.h"

void EEPROM_init(void)
{
	TWI_Init();
}


uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	/* Send the Start Bit */
	TWI_Start();
	if(TWI_Get_Status() != TW_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_Write((uint8)((( u16addr & 0X700 ) >> 7 ) | 0XA0));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return ERROR;


	/* Send the required memory location address */
	TWI_Write((uint8)u16addr);
	if(TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	/* write byte to eeprom */
	TWI_Write(u8data);
	if(TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_Stop();

	return SUCCESS;

}


uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	/* Send the Start Bit */
	TWI_Start();
	if(TWI_Get_Status() != TW_START)
		return ERROR;


	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_Write((uint8)((( u16addr & 0X700 ) >> 7 ) | 0XA0 ));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return ERROR;


	/* Send the required memory location address */
	TWI_Write((uint8)u16addr);
	if(TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	/* Send the reStart Bit */
	TWI_Start();
	if(TWI_Get_Status() != TW_REP_START)
		return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
	TWI_Write((uint8)(((u16addr & 0X700)>>7)| 0XA0 | 1));
	if(TWI_Get_Status() != TW_MT_SLA_R_ACK)
		return ERROR;

	/* Read Byte from Memory without send ACK */
	*u8data = TWI_Read_With_NACK();
	if(TWI_Get_Status() != TW_MR_DATA_NACK)
		return ERROR;


	/* Send the Stop Bit */
	TWI_Stop();

	return SUCCESS;
}





