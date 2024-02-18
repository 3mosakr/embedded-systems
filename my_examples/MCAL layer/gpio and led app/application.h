/* 
 * File:   application.h
 * Author: sakr3
 *
 * Created on November 6, 2023, 1:16 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/button/ecu_button.h"
#include <builtins.h>


/* Section : Macros Declarations */
#define _XTAL_FREQ 4000000

/* Section : Macros Function Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */

/**
 * 
 * @brief function to collect the initialization of functions' call (setup part) 
 * @param void
 * @return void
 */
void application_initialize (void);

#endif	/* APPLICATION_H */

