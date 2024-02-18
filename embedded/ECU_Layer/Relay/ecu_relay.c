/* 
 * File:   ecu_relay.h
 * Author: sakr3
 *
 * Created on December 15, 2023, 10:50 AM
 */

#include "ecu_relay.h"

/**
 * @brief Initialize the assigned pin to be output and turn the relay off or on
 * @param _relay pointer to the relay module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType relay_initialize (const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if (NULL == _relay) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = _relay->relay_port,
            .pin = _relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        
        ret = gpio_pin_initialize(&pin_obj);
    }

    return ret;
}

/**
 * @brief turn the relay on
 * @param _relay pointer to the relay module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType relay_turn_on (const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if (NULL == _relay) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = _relay->relay_port,
            .pin = _relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOGIC_HIGH);
    }

    return ret;
}

/**
 * @brief turn the relay off
 * @param _relay pointer to the relay module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType relay_turn_off (const relay_t *_relay){
    Std_ReturnType ret = E_OK;
    if (NULL == _relay) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin_obj = {
            .port = _relay->relay_port,
            .pin = _relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = _relay->relay_status
        };
        
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOGIC_LOW);
    }

    return ret;
}
