/* 
 * File:   ecu_relay.h
 * Author: sakr3
 *
 * Created on December 15, 2023, 10:50 AM
 */

#ifndef ECU__RELAY_H
#define	ECU__RELAY_H

/* --------------------- Includes --------------------- */
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* --------------------- Macro Declarations --------------------- */
#define RELAY_ON_STATUS  0x01U
#define RELAY_OFF_STATUS 0x00U

/* --------------------- Macro Functions Declarations --------------------- */

/* --------------------- Data Type Declarations --------------------- */
typedef struct {
    uint8 relay_port      :4; /* 3 for port and 1 external to make the size of struct 8 bits*/
    uint8 relay_pin       :3;
    uint8 relay_status    :1;
}relay_t;

/* --------------------- Software Interfaces Declarations --------------------- */
Std_ReturnType relay_initialize (const relay_t *_relay);
Std_ReturnType relay_turn_on (const relay_t *_relay);
Std_ReturnType relay_turn_off (const relay_t *_relay);

#endif	/* ECU__RELAY_H */

