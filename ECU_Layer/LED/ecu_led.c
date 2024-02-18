/* 
 * File:   ecu_led.c
 * Author: sakr3
 *
 * Created on November 6, 2023, 1:16 PM
 */

/* Section : Includes */
#include "ecu_led.h"

/**
 * @brief Initialize the assigned pin to be output and turn the led off or on
 * @param led pointer to the led module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        
        ret = gpio_pin_initialize(&pin_obj);
    }

    return ret;
}

/**
 * @brief turn the led on
 * @param led pointer to the led module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOGIC_HIGH);
    }

    return ret;
}

/**
 * @brief turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOGIC_LOW);
    }

    return ret;
}

/**
 * @brief toggle the led 
 * @param led pointer to the led module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType led_turn_toggle(const led_t *led) {
    Std_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port_name,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        
        ret = gpio_pin_toggle_logic(&pin_obj);
    }

    return ret;
}
