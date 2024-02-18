/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

void int0_app_isr(void){
    led_turn_toggle(&led1);
    __delay_ms(250);
}
void int1_app_isr(void){
    led_turn_toggle(&led2);
    __delay_ms(250);
}
void int2_app_isr(void){
    led_turn_toggle(&led3);
    __delay_ms(250);
}

interrupt_INTx_t int0_interrupt = {
    .EXT_InterruptHandler = int0_app_isr,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_INTx_t int1_interrupt = {
    .EXT_InterruptHandler = int1_app_isr,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_LOW_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN1,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_INTx_t int2_interrupt = {
    .EXT_InterruptHandler = int2_app_isr,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT2,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN2,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};


Std_ReturnType ret = E_OK;

int main() {

    application_initialize();
    
    
    while (1) {
        
        
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();
    
    ret = Interrupt_INTx_init(&int0_interrupt);
    ret = Interrupt_INTx_init(&int1_interrupt);
    ret = Interrupt_INTx_init(&int2_interrupt);
    
    
}