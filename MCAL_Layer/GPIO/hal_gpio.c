/* 
 * File:   hal_gpio.c
 * Author: sakr3
 *
 * Created on November 6, 2023, 11:35 AM
 */

#include "hal_gpio.h"

/* Reference to the data direction control registers */
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to the data latch registers (Read and Write to data latch) */
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* Reference to port status registers */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* port interfaces */
/**
 * @brief initialize direction of specific pin ( use tris registers ) @ref direction_t
 * @param _pin_config pointer to the configurations of pin @ref pin_config_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_MUNBER - 1) || (_pin_config->port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        /* set the direction of the pin inside tris registers */
        switch (_pin_config->direction) {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
        }

    }

    return ret;
}
#endif

/**
 * @brief return direction of specific pin in parameter ( use tris registers ) @ref direction_t 
 * @param _pin_config pointer to the configurations of pin @ref pin_config_t
 * @param direction pointer to return direction of specific pin
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _pin_config) || (NULL == direction) || (_pin_config->pin > PORT_PIN_MAX_MUNBER - 1) || (_pin_config->port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        *direction = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }

    return ret;
}
#endif

/**
 * @brief set logic of specific pin ( use lat registers ) @ref logic_t
 * @param _pin_config pointer to the configurations of pin @ref pin_config_t
 * @param logic the logic that will set on the pin @ref logic_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic) {
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || (_pin_config->pin > PORT_PIN_MAX_MUNBER - 1) || (_pin_config->port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        /* set the direction of the pin inside lat registers */
        switch (logic) {
            case GPIO_LOGIC_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_LOGIC_HIGH:
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}
#endif

/**
 * @brief return logic of specific pin in parameter ( use port registers ) @ref logic_t
 * @param _pin_config pointer to the configurations of pin @ref pin_config_t
 * @param logic pointer to return logic of specific pin
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _pin_config) || (NULL == logic) || (_pin_config->pin > PORT_PIN_MAX_MUNBER - 1) || (_pin_config->port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }

    return ret;
}
#endif

/**
 * @brief toggle logic of specific pin ( use lat registers ) @ref logic_t
 * @param _pin_config pointer to the configurations of pin @ref pin_config_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_MUNBER - 1) || (_pin_config->port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }

    return ret;
}
#endif

/**
 * @brief initialize direction of specific pin and write the logic of pin @ref direction_t, logic_t
 * @param _pin_config pointer to the configurations of pin @ref pin_config_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_MUNBER - 1) || (_pin_config->port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_direction_initialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }

    return ret;
}
#endif

/* port interfaces */
/**
 * @brief initialize direction of specific port ( use tris registers ) @ref direction_t
 * @param port the port index that will initialized @ref port_index_t
 * @param direction the direction of port which will write in tris register of port 
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction) {
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *tris_registers[port] = direction;
    }

    return ret;
}
#endif

/**
 * @brief return direction of specific port in parameter ( use tris registers ) @ref direction_t
 * @param port the port index @ref port_index_t
 * @param direction pointer to return direction of specific port
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status) {
    Std_ReturnType ret = E_OK;
    if ((NULL == direction_status) || (port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        *direction_status = *tris_registers[port];
    }

    return ret;
}
#endif

/**
 * @brief set logic of specific port ( use lat registers ) @ref logic_t
 * @param port the port index @ref port_index_t
 * @param logic the logic that will set on the port @ref logic_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic) {
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_registers[port] = logic;
    }

    return ret;
}
#endif

/**
 * @brief return logic of specific port in parameter ( use port registers ) @ref logic_t
 * @param port the port index @ref port_index_t
 * @param logic pointer to return logic of specific port
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic) {
    Std_ReturnType ret = E_OK;
    if ((NULL == logic) || (port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } else {
        *logic = *port_registers[port];
    }

    return ret;
}
#endif

/**
 * @brief toggle logic of specific port ( use lat registers ) @ref logic_t
 * @param port the port index @ref port_index_t
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE

Std_ReturnType gpio_port_toggle_logic(port_index_t port) {
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_registers[port] ^= 0xFF;
    }
    return ret;
}
#endif
