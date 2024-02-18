/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

void RB4_app_isr_high(void){
    led_turn_on(&led1);
    __delay_ms(250);
}
void RB4_app_isr_low(void){
    led_turn_on(&led2);
    __delay_ms(250);
}

void RB5_app_isr_high(void){
    led_turn_on(&led3);
    __delay_ms(250);
}
void RB5_app_isr_low(void){
    led_turn_on(&led4);
    __delay_ms(250);
}

void RB6_app_isr_high(void){
    led_turn_off(&led1);
    __delay_ms(250);
}
void RB6_app_isr_low(void){
    led_turn_off(&led2);
    __delay_ms(250);
}

void RB7_app_isr_high(void){
    led_turn_off(&led3);
    __delay_ms(250);
}
void RB7_app_isr_low(void){
    led_turn_off(&led4);
    __delay_ms(250);
}


interrupt_RBx_t RB4_interrupt = {
    .EXT_InterruptHandler_HIGH = RB4_app_isr_high,
    .EXT_InterruptHandler_LOW = RB4_app_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB5_interrupt = {
    .EXT_InterruptHandler_HIGH = RB5_app_isr_high,
    .EXT_InterruptHandler_LOW = RB5_app_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB6_interrupt = {
    .EXT_InterruptHandler_HIGH = RB6_app_isr_high,
    .EXT_InterruptHandler_LOW = RB6_app_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN6,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB7_interrupt = {
    .EXT_InterruptHandler_HIGH = RB7_app_isr_high,
    .EXT_InterruptHandler_LOW = RB7_app_isr_low,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN7,
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
    
    ret = Interrupt_RBx_init(&RB4_interrupt);
    ret = Interrupt_RBx_init(&RB5_interrupt);
    ret = Interrupt_RBx_init(&RB6_interrupt);
    ret = Interrupt_RBx_init(&RB7_interrupt);
    
    
    
}