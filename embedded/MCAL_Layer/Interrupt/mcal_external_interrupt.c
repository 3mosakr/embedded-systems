/* 
 * File:   mcal_external_interrupt.c
 * Author: sakr3
 *
 * Created on January 23, 2024, 2:35 PM
 */

#include "mcal_external_interrupt.h"

/* Pointer to function to hold the callback functions for INTx */ 
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

/* Pointer to function to hold the callback functions for RBx */ 
static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW = NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_LOW = NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_LOW = NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_LOW = NULL;

/* ------------- helper functions declarations ----------------- */ 
/* ============ INTx External Interrupt Start ============ */
static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

/* set functions of Pointer to function which hold the callback functions for INTx */ 
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler) (void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler) (void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler) (void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

/* ============ INTx External Interrupt End ============ */

/* ============ PortB External On Change Interrupt Start ============ */
static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);

/* ============ PortB External On Change Interrupt End ============ */

/* ============ INTx External Interrupt ISR Start ============ */
/**
 * External Interrupt INT0 MCAL Helper function 
 */
void INT0_ISR(void) {
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (INT0_InterruptHandler) {
        INT0_InterruptHandler();
    } else {
        /* Nothing */
    }
}

/**
 * External Interrupt INT1 MCAL Helper function 
 */
void INT1_ISR(void) {
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (INT1_InterruptHandler) {
        INT1_InterruptHandler();
    } else {
        /* Nothing */
    }
}

/**
 * External Interrupt INT2 MCAL Helper function 
 */
void INT2_ISR(void) {
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (INT2_InterruptHandler) {
        INT2_InterruptHandler();
    } else {
        /* Nothing */
    }
}

/* ============ INTx External Interrupt ISR End ============ */

/* ============ PortB External On Change Interrupt ISR Start ============ */
/**
 * External Interrupt RB4 MCAL Helper function 
 */
void RB4_ISR(uint8 RB4_source) {
    /* The RB4 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (0 == RB4_source) {
        /* High */
        if (RB4_InterruptHandler_HIGH) {
            RB4_InterruptHandler_HIGH();
        } else { /* Nothing */ }
    } else if (1 == RB4_source) {
        /* Low */
        if (RB4_InterruptHandler_LOW) {
            RB4_InterruptHandler_LOW();
        } else { /* Nothing */ }
    } else {
        /* Nothing */
    }
}

/**
 * External Interrupt RB5 MCAL Helper function 
 */
void RB5_ISR(uint8 RB5_source) {
    /* The RB5 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (0 == RB5_source) {
        /* High */
        if (RB5_InterruptHandler_HIGH) {
            RB5_InterruptHandler_HIGH();
        } else { /* Nothing */ }
    } else if (1 == RB5_source) {
        /* Low */
        if (RB5_InterruptHandler_LOW) {
            RB5_InterruptHandler_LOW();
        } else { /* Nothing */ }
    } else {
        /* Nothing */
    }
}

/**
 * External Interrupt RB6 MCAL Helper function 
 */
void RB6_ISR(uint8 RB6_source) {
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (0 == RB6_source) {
        /* High */
        if (RB6_InterruptHandler_HIGH) {
            RB6_InterruptHandler_HIGH();
        } else { /* Nothing */ }
    } else if (1 == RB6_source) {
        /* Low */
        if (RB6_InterruptHandler_LOW) {
            RB6_InterruptHandler_LOW();
        } else { /* Nothing */ }
    } else {
        /* Nothing */
    }
}

/**
 * External Interrupt RB7 MCAL Helper function 
 */
void RB7_ISR(uint8 RB7_source) {
    /* The RB7 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    /* Application Callback function gets called every time this ISR executes */
    if (0 == RB7_source) {
        /* High */
        if (RB7_InterruptHandler_HIGH) {
            RB7_InterruptHandler_HIGH();
        } else { /* Nothing */ }
    } else if (1 == RB7_source) {
        /* Low */
        if (RB7_InterruptHandler_LOW) {
            RB7_InterruptHandler_LOW();
        } else { /* Nothing */ }
    } else {
        /* Nothing */
    }
}

/* ============ PortB External On Change Interrupt ISR End ============ */

/**
 * @brief Initialize the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Disable the External interrupt */
        ret |= interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edge */
        ret |= Interrupt_INTx_Edge_Init(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Configure External interrupt Priority */
        ret |= Interrupt_INTx_Priority_Init(int_obj);
#endif
        /* Configure External interrupt I/O pin */
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the External interrupt */
        ret |= interrupt_INTx_Enable(int_obj);
    }

    return ret;
}

/**
 * @brief DeInitialize the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        ret = interrupt_INTx_Disable(int_obj);
    }

    return ret;
}



/* ------------- helper functions implementation ----------------- */
/* ============ INTx External Interrupt Start ============ */

/**
 * @brief enable the external interrupt INT0, INT1 and INT2. and set the global interrupts enable
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                /* Enable global high priority interrupt */
                INTERRUPT_GlobalInterruptHighEnable();
#else
                /* Enable global and peripheral interrupts */
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /* Nothing */
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_GlobalInterruptHighEnable();
                } else {
                    /* Nothing */
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                break;
            default: ret = E_NOT_OK;
        }
    }

    return ret;
}

/**
 * @brief Disable the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0: 
                EXT_INT0_InterruptDisable(); /* Disable the INT0 external interrupt */
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                EXT_INT1_InterruptDisable(); /* Disable the INT1 external interrupt */
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                EXT_INT2_InterruptDisable(); /* Disable the INT2 external interrupt */
                break;
            default: ret = E_NOT_OK;
        }
    }

    return ret;
}


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/**
 * @brief Set the priority of the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
                /* INTERRUPT_EXTERNAL_INT0 always high priority can't change */
            case INTERRUPT_EXTERNAL_INT1:
                if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    EXT_INT1_HighPrioritySet();
                } else if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    EXT_INT1_LowPrioritySet();
                } else {
                    /* Nothing */
                }
                break;

            case INTERRUPT_EXTERNAL_INT2:
                if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    EXT_INT2_HighPrioritySet();
                } else if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    EXT_INT2_LowPrioritySet();
                } else {
                    /* Nothing */
                }
                break;

            default: ret = E_NOT_OK;
        }
    }

    return ret;
}
#endif

/**
 * @brief Set the state of the external interrupt INT0, INT1 and INT2 change that make the interrupt
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                if (INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT0_FallingEdgeSet();
                } else if (INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT0_RisingEdgeSet();
                } else {
                    /* Nothing */
                }
                break;

            case INTERRUPT_EXTERNAL_INT1:
                if (INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT1_FallingEdgeSet();
                } else if (INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT1_RisingEdgeSet();
                } else {
                    /* Nothing */
                }
                break;

            case INTERRUPT_EXTERNAL_INT2:
                if (INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT2_FallingEdgeSet();
                } else if (INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT2_RisingEdgeSet();
                } else {
                    /* Nothing */
                }
                break;

            default: ret = E_NOT_OK;
        }
    }

    return ret;
}

/**
 * @brief Initialize the MCU Pin for INTx with the needed configurations
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Initialize the MCU Pin for INTx with the needed configurations */
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }

    return ret;
}

/**
 * @brief Clear the Flag of the external interrupt INT0, INT1 and INT2
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0: EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1: EXT_INT1_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT2: EXT_INT2_InterruptFlagClear();
                break;
            default: ret = E_NOT_OK;
        }
    }

    return ret;
}

/**
 * @brief set functions of Pointer to function which hold the callback functions for INTx declaration
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0: 
                /* Set Default Interrupt Handler for INT0 External Interrupt : Application ISR */
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                /* Set Default Interrupt Handler for INT1 External Interrupt : Application ISR */
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                /* Set Default Interrupt Handler for INT2 External Interrupt : Application ISR */
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}

/* set functions of Pointer to function which hold the callback functions for INTx declaration */
/**
 * @brief  Set Default Interrupt Handler for INT0 External Interrupt : Application ISR
 * @param InterruptHandler pointer to interrupt function : Application ISR
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler) (void)) {
    Std_ReturnType ret = E_OK;
    if (NULL == InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        /* Set Default Interrupt Handler for INT0 External Interrupt : Application ISR */
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * @brief  Set Default Interrupt Handler for INT1 External Interrupt : Application ISR
 * @param InterruptHandler pointer to interrupt function : Application ISR
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler) (void)) {
    Std_ReturnType ret = E_OK;
    if (NULL == InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        /* Set Default Interrupt Handler for INT1 External Interrupt : Application ISR */
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/**
 * @brief  Set Default Interrupt Handler for INT2 External Interrupt : Application ISR
 * @param InterruptHandler pointer to interrupt function : Application ISR
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler) (void)) {
    Std_ReturnType ret = E_OK;
    if (NULL == InterruptHandler) {
        ret = E_NOT_OK;
    } else {
        /* Set Default Interrupt Handler for INT2 External Interrupt : Application ISR */
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

/* ============ INTx External Interrupt End ============ */

/* ============ PortB External On Change Interrupt Start ============ */

/**
 * @brief Initialize the external interrupt RBx
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_init(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* This routine clears the interrupt disable for the external interrupt, RBx */
        EXT_RBx_InterruptDisable();
        /* This routine clears the interrupt flag for the external interrupt, RBx */
        EXT_RBx_InterruptFlagClear();
        /* Configure External interrupt Priority */
        ret |= Interrupt_RBx_Priority_Init(int_obj);
        /* Configure External interrupt I/O pin */
        ret |= Interrupt_RBx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret |= Interrupt_RBx_SetInterruptHandler(int_obj);
        /* This routine sets the interrupt enable for the external interrupt, RBx */
        EXT_RBx_InterruptEnable();
    }
    return ret;
}

/**
 * @brief Disable the external interrupt RBx
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* This routine clears the interrupt disable for the external interrupt, RBx */
        EXT_RBx_InterruptDisable();
        /* This routine clears the interrupt flag for the external interrupt, RBx */
        EXT_RBx_InterruptFlagClear();
    }

    return ret;
}

/**
 * @brief Set the priority of the external interrupt RBx. and Enable the global interrupts
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Enable the priority levels interrupts */
        INTERRUPT_PriorityLevelsEnable();
        /* Configure External interrupt Priority */
        if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
            /* This macro will enable high priority global interrupts. */
            INTERRUPT_GlobalInterruptHighEnable();
            /* This routine set the RBx External Interrupt Priority to be High priority */
            EXT_RBx_Priority_High();
        } else if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
            /* This macro will enable low priority global interrupts. */
            INTERRUPT_GlobalInterruptLowEnable();
            /* This routine set the RBx External Interrupt Priority to be Low priority */
            EXT_RBx_Priority_Low();
        } else {
            /* NOTHING */
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
    }

    return ret;
}

/**
 * @brief Initialize the MCU Pin for RBx with the needed configurations
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        /* Initialize the RBx pin to be input */
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }
    return ret;
}

/**
 * @brief set functions of Pointer to function which hold the callback functions for RBx declaration
 * @param int_obj Pointer to the Interrupt configuration object
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj) {
        ret = E_NOT_OK;
    } else {
        switch (int_obj->mcu_pin.pin) {
            case GPIO_PIN4:
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default: ret = E_NOT_OK;
        }
    }

    return ret;
}

/* ============ PortB External On Change Interrupt End ============ */
