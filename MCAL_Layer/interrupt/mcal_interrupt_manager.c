
/* 
 * File:   mcal_interrupt_manager.c
 * Author: MOUSTAFA
 *
 * Created on February 28, 2023, 5:30 AM
 */
#include "mcal_interrupt_manager.h"
#if INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
void __interrupt() interruptManagerHigh(void){
    
}

void __interrupt(low_priority) interruptManagerlow(void){
    
}
#else
void __interrupt() interruptManager(void){
#if TIMER1_INTERRUPT_FEATURE==INTERRUPT_FREATUERE_ENABLE 
    if ((INTERRUPT_ENABLE==PIE1bits.TMR1IE) && (INTERRPT_OCCURE==PIR1bits.TMR1IF)){
        TIMER1_ISR();
    }
 #endif       
}

#endif