/* 
 * File:   application.h
 * Author: sakr3
 *
 * Created on November 6, 2023, 1:16 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */

#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"

/* Section : Macros Declarations */


/* Section : Macros Function Declarations */

/* Section : Data Type Declarations */

extern led_t led1;
extern led_t led2;
extern led_t led3;
//extern chr_lcd_4bit_t lcd1;

/* Section : Functions Declarations */

/**
 * 
 * @brief function to collect the initialization of functions' call (setup part) 
 * @param void
 * @return void
 */
void application_initialize (void);

#endif	/* APPLICATION_H */

