/* 
 * File:   ecu_button.c
 * Author: sakr3
 *
 * Created on December 13, 2023, 9:56 PM
 */

#include "ecu_button.h"

/**
 * @brief initialize the assigned pin to be input
 * @param btn pointer to the button configuration
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t *btn) {
    Std_ReturnType ret = E_OK;
    if (NULL == btn) {
        ret = E_NOT_OK;
    } else {

        ret = gpio_pin_direction_initialize(&(btn->button_pin));
    }

    return ret;
}

/**
 * @brief read the state of the button
 * @param btn pointer to the button configuration
 * @param btn_state button state @ref button_state_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state) {
    Std_ReturnType ret = E_OK;
    if ((NULL == btn) || (NULL == btn_state)) {
        ret = E_NOT_OK;
    } else {
        logic_t btn_status = GPIO_LOGIC_LOW;
        
        gpio_pin_read_logic(&(btn->button_pin), &btn_status);

        if (BUTTON_ACTIVE_HIGH == btn->button_connection) {
            if (btn_status == GPIO_LOGIC_HIGH) {
                *btn_state = BUTTON_PRESSED;
            } else {
                *btn_state = BUTTON_RELEASED;
            }
        } else if (BUTTON_ACTIVE_LOW == btn->button_connection) {
            if (btn_status == GPIO_LOGIC_HIGH) {
                *btn_state = BUTTON_RELEASED;
            } else {
                *btn_state = BUTTON_PRESSED;
            }
        } else {
            /* NOTHING */
        }
    }

    return ret;
}


