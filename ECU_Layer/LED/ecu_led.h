/* 
 * File:   ecu_led.h
 * Author: sakr3
 *
 * Created on November 6, 2023, 1:11 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Section : Macros Declarations */

/* Section : Macros Function Declarations */

/* Section : Data Type Declarations */

typedef enum {
    LED_OFF,
    LED_ON
}led_status;

typedef struct {
    uint8 port_name     :4; /* 3 bits for port and 1 reserved for future use */
    uint8 pin           :3;
    uint8 led_status    :1;
}led_t;

/* Section : Functions Declarations */

Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

