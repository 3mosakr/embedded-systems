/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: sakr3
 *
 * Created on January 25, 2024, 2:30 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* --------------------- Includes --------------------- */

/* --------------------- Macro Declarations --------------------- */
#define INTERRUPT_FEATURE_ENABLE        1U

//#define INTERRUPT_PRIORITY_LEVELS_ENABLE            INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_ENABLE              INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_ENABLE          INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE


/* --------------------- Macro Functions Declarations --------------------- */

/* --------------------- Data Type Declarations --------------------- */

/* --------------------- Software Interfaces Declarations --------------------- */

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

