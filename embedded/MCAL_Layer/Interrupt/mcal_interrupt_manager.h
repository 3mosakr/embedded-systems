/* 
 * File:   mcal_interrupt_manager.h
 * Author: sakr3
 *
 * Created on January 23, 2024, 12:11 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* --------------------- Includes --------------------- */
#include "mcal_interrupt_config.h"

/* --------------------- Macro Declarations --------------------- */

/* --------------------- Macro Functions Declarations --------------------- */

/* --------------------- Data Type Declarations --------------------- */

/* --------------------- Software Interfaces Declarations --------------------- */
/* ============ INTx External Interrupt Start ============ */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
/* ============ INTx External Interrupt End ============ */

/* ============ PortB External On Change Interrupt Start ============ */
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);
/* ============ PortB External On Change Interrupt End ============ */

/* ============ Internal Interrupts Start ============ */
void ADC_ISR(void);

/* ============ Internal Interrupts End ============ */

#endif	/* MCAL_INTERRUPT_MANAGER_H */

