/* 
 * File:   mcal_interrupt_config.h
 * Author: sakr3
 *
 * Created on January 23, 2024, 12:05 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* --------------------- Includes --------------------- */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"


/* --------------------- Macro Declarations --------------------- */

/* The status of interrupt, priority and flags */
#define INTERRUPT_DISABLE               0
#define INTERRUPT_ENABLE                1

#define INTERRUPT_NOT_OCCUR             0
#define INTERRUPT_OCCUR                 1

#define INTERRUPT_PRIORITY_DISABLE      0
#define INTERRUPT_PRIORITY_ENABLE       1


/* --------------------- Macro Functions Declarations --------------------- */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* priority levels mode */
/* This macro will disable priority levels interrupts. */
#define INTERRUPT_PriorityLevelsDisable()       (RCONbits.IPEN = 0)
/* This macro will enable priority levels interrupts. */
#define INTERRUPT_PriorityLevelsEnable()        (RCONbits.IPEN = 1)

/* This macro will disable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH = 0)
/* This macro will enable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighEnable()   (INTCONbits.GIEH = 1)

/* This macro will disable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowDisable()   (INTCONbits.GIEL = 0)
/* This macro will enable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowEnable()    (INTCONbits.GIEL = 1)

#else

#endif
/* compatibility mode (default mode) */
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

/* This macro will disable peripherals interrupts. */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
/* This macro will enable peripherals interrupts. */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)


/* --------------------- Data Type Declarations --------------------- */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

/* --------------------- Software Interfaces Declarations --------------------- */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

