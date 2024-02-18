/* 
 * File:   mcal_interrupt_manager.c
 * Author: sakr3
 *
 * Created on January 23, 2024, 12:11 PM
 */

#include "mcal_interrupt_manager.h"
#include "mcal_external_interrupt.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptMangerHigh(void) {
    /* check int0 interrupt enabled and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }else { /* Nothing */ }
    /* check int2 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }else { /* Nothing */ }
/* ============ PortB External On Change Interrupt Start ============ */
    /* check RB4 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB4) && (1 == RB4_Flag)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB4 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB4) && (0 == RB4_Flag)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }else { /* Nothing */ }
    
    /* check RB5 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB5) && (1 == RB5_Flag)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB5 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB5) && (0 == RB5_Flag)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }else { /* Nothing */ }
    
    /* check RB6 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB6) && (1 == RB6_Flag)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB6 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB6) && (0 == RB6_Flag)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }else { /* Nothing */ }
    
    /* check RB7 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB7) && (1 == RB7_Flag)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB7 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB7) && (0 == RB7_Flag)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }else { /* Nothing */ }
    
/* ============ PortB External On Change Interrupt End ============ */
}

void __interrupt(low_priority) InterruptMangerLow(void) {
    /* check int1 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }else { /* Nothing */ }
}
#else
/* priority off */
void __interrupt() InterruptManger(void) {
    /* ============ INTx External On Change Interrupt Start ============ */
    /* check int0 interrupt enabled and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }else { /* Nothing */ }
    /* check int1 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }else { /* Nothing */ }
    /* check int2 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }else { /* Nothing */ }
    /* ============ INTx External Interrupt End ============ */
    
    /* ============ PortB External On Change Interrupt Start ============ */
    /* check RB4 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB4) && (1 == RB4_Flag)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB4 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB4) && (0 == RB4_Flag)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }else { /* Nothing */ }
    
    /* check RB5 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB5) && (1 == RB5_Flag)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB5 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB5) && (0 == RB5_Flag)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }else { /* Nothing */ }
    
    /* check RB6 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB6) && (1 == RB6_Flag)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB6 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB6) && (0 == RB6_Flag)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }else { /* Nothing */ }
    
    /* check RB7 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_HIGH == PORTBbits.RB7) && (1 == RB7_Flag)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }else { /* Nothing */ }
    
    /* check RB7 interrupt enable and is occur  */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (GPIO_LOGIC_LOW == PORTBbits.RB7) && (0 == RB7_Flag)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }else { /* Nothing */ }
    
    /* ============ PortB External On Change Interrupt End ============ */
    
    /* ============ Internal Interrupts Start ============ */
    /* ==== ADC Module Interrupt ==== */
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }else { /* Nothing */ }
    
    /* ============ Internal Interrupts End ============ */
}

#endif
