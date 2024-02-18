/* 
 * File:   ecu_button.h
 * Author: sakr3
 *
 * Created on December 13, 2023, 9:56 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macros Declarations */

/* Section : Macros Function Declarations */

/* Section : Data Type Declarations */
typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED
} button_state_t;

typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
} button_active_t;

typedef struct {
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
} button_t;

/* Section : Functions Declarations */


Std_ReturnType button_initialize(const button_t *btn);

/**
 * @brief read the state of the button
 * @param btn pointer to the button configuration
 * @param btn_state button state @ref button_state_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

