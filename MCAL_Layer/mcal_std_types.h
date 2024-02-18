/* 
 * File:   mcal_std_types.h
 * Author: sakr3
 *
 * Created on November 6, 2023, 12:21 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include "compiler.h"
#include "std_libraries.h"


/* Section : Macros Function Declarations */

/* Section : Data Type Declarations */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed int      sint32;

typedef uint8 Std_ReturnType;

/* Section : Macros Declarations */
// AutoSAR Specification of Standard Types
#define STD_HIGH        0X01
#define STD_LOW         0X00

#define STD_ON          0X01
#define STD_OFF         0X00

#define STD_ACTIVE      0X01
#define STD_IDLE        0X00

#define CONFIG_ENABLE   0X01
#define CONFIG_DISABLE  0X00

#define E_OK            (Std_ReturnType)0x00
#define E_NOT_OK        (Std_ReturnType)0x01

#define ZERO_INIT       0X00


#define _XTAL_FREQ 8000000UL /* refare to the frequance of the mictocontroller  */

/* Section : Functions Declarations */

#endif	/* MCAL_STD_TYPES_H */

