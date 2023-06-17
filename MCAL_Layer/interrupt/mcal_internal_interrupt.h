/* 
 * File:   mcal_internal_interrupt.h
 * Author: MOUSTAFA
 *
 * Created on February 28, 2023, 5:29 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/* Section: Includes */
#include "mcal_interrupt_config.h"
#include "mcal_interrupt_gen_config.h"

/* Section : Macros Declarations  */


#if TIMER1_INTERRUPT_FEATURE==INTERRUPT_FREATUERE_ENABLE
    /*macro enable the TIMER1_internal interrupt enable*/
#define TIMER1_INTERRUPT_ENABLE()       (PIE1bits.TMR1IE=1)
/*macro enable the TIMER1_internal interrupt enable*/
#define TIMER1_INTERRUPT_DISABLE()      (PIE1bits.TMR1IE=0)
/* macro that clear the TIMER1_internal flag*/
#define TIMER1_FLAG_INTERRUPT_CLEAR()   (PIR1bits.TMR1IF=0)
#if  INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
    /*macro make the TIMER1_internal high priority  */
#define TIMER1_INTERRUPT_HIGHY_PRIORITY()  (IPR1bits.TMR1IP=1)
/*macro make the TIMER1_internal low priority  */
#define TIMER1_INTERRUPT_LOW_PRIORITY()    (IPR1bits.TMR1IP=0)
#endif
#endif 


/* Data types Declarations */

/* Function Declarations*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

