/* 
 * File:   mcal_external_interrupt.h
 * Author: sakr3
 *
 * Created on January 23, 2024, 2:35 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* --------------------- Includes --------------------- */
#include "mcal_interrupt_config.h"

/* --------------------- Macro Declarations --------------------- */

/* --------------------- Macro Functions Declarations --------------------- */
/* INTx interrupt */
#if EXTERNAL_INTERRUPT_INTx_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptDisable()         (INTCONbits.INT0IE = 0)
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptEnable()          (INTCONbits.INT0IE = 1)
/* This routine clears the interrupt flag for the external interrupt, INT0 */
#define EXT_INT0_InterruptFlagClear()       (INTCONbits.INT0IF = 0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT0_RisingEdgeSet()            (INTCON2bits.INTEDG0 = 1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT0_FallingEdgeSet()           (INTCON2bits.INTEDG0 = 0)

/* This routine clears the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptDisable()         (INTCON3bits.INT1IE = 0)
/* This routine sets the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptEnable()          (INTCON3bits.INT1IE = 1)
/* This routine clears the interrupt flag for the external interrupt, INT1 */
#define EXT_INT1_InterruptFlagClear()       (INTCON3bits.INT1IF = 0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT1_RisingEdgeSet()            (INTCON2bits.INTEDG1 = 1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT1_FallingEdgeSet()           (INTCON2bits.INTEDG1 = 0)

/* This routine clears the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptDisable()         (INTCON3bits.INT2IE = 0)
/* This routine sets the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptEnable()          (INTCON3bits.INT2IE = 1)
/* This routine clears the interrupt flag for the external interrupt, INT2 */
#define EXT_INT2_InterruptFlagClear()       (INTCON3bits.INT2IF = 0)
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT2_RisingEdgeSet()            (INTCON2bits.INTEDG2 = 1)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT2_FallingEdgeSet()           (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* priority */
/* This routine set the INT1 External Interrupt Priority to be High priority */
#define EXT_INT1_HighPrioritySet()           (INTCON3bits.INT1IP = 1)
/* This routine set the INT1 External Interrupt Priority to be Low priority */
#define EXT_INT1_LowPrioritySet()            (INTCON3bits.INT1IP = 0)
/* This routine set the INT2 External Interrupt Priority to be High priority */
#define EXT_INT2_HighPrioritySet()           (INTCON3bits.INT2IP = 1)
/* This routine set the INT2 External Interrupt Priority to be Low priority */
#define EXT_INT2_LowPrioritySet()            (INTCON3bits.INT2IP = 0)

#endif

#endif

/* on change interrupt */
#if EXTERNAL_INTERRUPT_OnChange_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine clears the interrupt disable for the external interrupt, RBx */
#define EXT_RBx_InterruptDisable()         (INTCONbits.RBIE = 0)
/* This routine sets the interrupt enable for the external interrupt, RBx */
#define EXT_RBx_InterruptEnable()          (INTCONbits.RBIE = 1)
/* This routine clears the interrupt flag for the external interrupt, RBx */
#define EXT_RBx_InterruptFlagClear()       (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* priority */
/* This routine set the RBx External Interrupt Priority to be High priority */
#define EXT_RBx_Priority_High()            (INTCON2bits.RBIP = 1)
/* This routine set the RBx External Interrupt Priority to be Low priority */
#define EXT_RBx_Priority_Low()             (INTCON2bits.RBIP = 0)
#endif

#endif

/* --------------------- Data Type Declarations --------------------- */
/* pointer to function type */
typedef void (*InterruptHandler) (void);

typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_src;

typedef enum {
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef struct {
    void (* EXT_InterruptHandler)(void); /* pointer to call back function */
    pin_config_t mcu_pin;               /* @ref pin_config_t */
    interrupt_INTx_edge edge;           /* @ref interrupt_INTx_edge */
    interrupt_INTx_src source;          /* @ref interrupt_INTx_src */
    interrupt_priority_cfg priority;    /* @ref interrupt_priority_cfg */
}interrupt_INTx_t;

typedef struct {
    void (*EXT_InterruptHandler_HIGH) (void); /* pointer to call back function when to high change volt */
    void (*EXT_InterruptHandler_LOW) (void); /* pointer to call back function when to low change volt */
    pin_config_t mcu_pin;               /* @ref pin_config_t */
    interrupt_priority_cfg priority;    /* @ref interrupt_priority_cfg */
}interrupt_RBx_t;

/* --------------------- Software Interfaces Declarations --------------------- */
/* ============ INTx External Interrupt Start ============ */

/**
 * @brief Initialize the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_init(const interrupt_INTx_t *int_obj);

/**
 * @brief DeInitialize the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj);

/* ============ INTx External Interrupt End ============ */

/* ============ PortB External On Change Interrupt Start ============ */

/**
 * @brief Initialize the external interrupt RBx
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_init(const interrupt_RBx_t *int_obj);

/**
 * @brief Disable the external interrupt RBx
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj);
/* ============ PortB External On Change Interrupt End ============ */

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

