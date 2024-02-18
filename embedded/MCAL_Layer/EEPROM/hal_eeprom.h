/* 
 * File:   hal_eeprom.h
 * Author: sakr3
 *
 * Created on February 2, 2024, 12:16 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* --------------------- Includes --------------------- */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* --------------------- Macro Declarations --------------------- */
/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY         1
#define ACCESS_EEPROM_PROGRAM_MEMORY        0
/*  Flash Program/Data EEPROM or Configuration Select bit */
#define ACCESS_CONFIG_REGISTERS             1
#define ACCESS_FLASH_EEPROM_MEMORY          0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM     1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM   0
/* Write Control bit */
#define INITIATE_DATA_EEPROM_WRITE_ERASE    1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED   0
/* Read Control bit */
#define INITIATE_DATA_EEPROM_READ           1

/* --------------------- Macro Functions Declarations --------------------- */

/* --------------------- Data Type Declarations --------------------- */

/* --------------------- Software Interfaces Declarations --------------------- */

/**
 * @Summary Writes a data byte to Data EEPROM
 * @Description This routine writes a data byte to given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location to which data to be written
 * @param bData - Data to be written to Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_WriteByte(0x3FF, 0);
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bByte);

/**
 * @Summary Reads a data byte from Data EEPROM
 * @Description This routine reads a data byte from given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location from which data has to be read
 * @param bData - Data byte read from given Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_ReadByte(0x3FF, &eeprom_read_val);
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bByte);

#endif	/* HAL_EEPROM_H */

