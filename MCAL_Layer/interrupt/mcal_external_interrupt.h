/* 
 * File:   mcal_external_interrupt.h
 * Author: MOUSTAFA
 *
 * Created on February 28, 2023, 5:30 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section: Includes */
#include "mcal_interrupt_config.h"


/* Section : Macros Declarations  */

/* Section : macros Function Declarations */
#if EXTERNAL_INERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FREATUERE_ENABLE
/*macro enable the external INT0 interrupt enable*/
#define EXTERNAL_INT0_INTERRUPT_ENABLE()   (INTCONbits.INT0E=1)
/*macro enable the external INT0 interrupt enable*/
#define EXTERNAL_INT0_INTERRUPT_DISABLE()   (INTCONbits.INT0E=0)
/* macro that clear the INT0 flag*/
#define EXTERNAL_INT0_FLAG_INTERRUPT_CLEAR()   (INTCONbits.INT0IF=0)
/*macro set the external interrupt INT0 detect at negative edge */
#define EXTERNAL_INT0_FALLIING_EDGE()  (INTCON2bits.INTEDG0=0)
/*macro set the external interrupt INT0 detect at positive edge */
#define EXTERNAL_INT0_RISIING_EDGE()   (INTCON2bits.INTEDG0=1)

/*macro enable the external INT1 interrupt enable*/
#define EXTERNAL_INT1_INTERRUPT_ENABLE()  (INTCON3bits.INT1E=1)
/*macro enable the external INT1 interrupt enable*/
#define EXTERNAL_INT1_INTERRUPT_DISABLE()  (INTCON3bits.INT1E=0)
/* macro that clear the INT1 flag*/
#define EXTERNAL_INT1_FLAG_INTERRUPT_CLEAR()  (INTCON3bits.INT1F=0)
/*macro set the external interrupt INT1 detect at negative edge */
#define EXTERNAL_INT1_FALLIING_EDGE()  (INTCON2bits.INTEDG1=0)
/*macro set the external interrupt INT1 detect at positive edge */
#define EXTERNAL_INT1_RISIING_EDGE()  (INTCON2bits.INTEDG1=1)


/*macro enable the external INT2 interrupt enable*/
#define EXTERNAL_INT2_INTERRUPT_ENABLE()  (INTCON3bits.INT2E=1)
/*macro enable the external INT2 interrupt enable*/
#define EXTERNAL_INT2_INTERRUPT_DISABLE()  (INTCON3bits.INT2E=0)
/* macro that clear the INT2 flag*/
#define EXTERNAL_INT2_FLAG_INTERRUPT_CLEAR() (INTCON3bits.INT2F=0)
/*macro set the external interrupt INT2 detect at negative edge */
#define EXTERNAL_INT2_FALLIING_EDGE()  (INTCON2bits.INTEDG2=0)
/*macro set the external interrupt INT1 detect at positive edge */
#define EXTERNAL_INT2_RISIING_EDGE()  (INTCON2bits.INTEDG2=1)

#if  INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
/*macro make the INT1 high priority  */
#define EXTERNAL_INT1_INTERRUPT_HIGHY_PRIORITY()  (INTCON3bits.INT1P=1)
/*macro make the INT1 low priority  */
#define EXTERNAL_INT1_INTERRUPT_LOW_PRIORITY()  (INTCON3bits.INT1P=0)

/*macro make the INT2 high priority  */
#define EXTERNAL_INT2_INTERRUPT_HIGHY_PRIORITY()  (INTCON3bits.INT2IP=1)
/*macro make the INT2 low priority  */
#define EXTERNAL_INT2_INTERRUPT_LOW_PRIORITY()  (INTCON3bits.INT2IP=0)
#endif
#endif


#if EXTERNAL_INERRUPT_ONChange_FEATURE_ENABLE==INTERRUPT_FREATUERE_ENABLE
/* macro enable RBx on_change INTERRUPT */
#define EXTERNAL_RBx_INTERRUPT_ENABLE()  (INTCONbits.RBIE=1)
/* macro enable RBx on_change INTERRUPT */
#define EXTERNAL_RBx_INTERRUPT_DISABLE()  (INTCONbits.RBIE=0)
/*macro that clear the flag of the onChange interrupt*/
#define EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR()  (INTCONbits.RBIF=0)

#if  INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
/*macro make RBx external interrupt  low priority */
#define EXTERNAL_RBx_INTERRUPT_HIGHY_PRIORITY() (INTCON2bits.RBIP=1)
/*macro make RBx external interrupt  low priority */
#define EXTERNAL_RBx_INTERRUPT_LOW_PRIORITY() (INTCON2bits.RBIP=0)

#endif

#endif

/* Data types Declarations */
typedef void(*InterruptHandler)(void);

typedef enum {
    INTERRUPT_FALLING_EDGE=0,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge_t;

typedef enum {
    EXTERNAL_INTERRUPT_INT0=0,
    EXTERNAL_INTERRUPT_INT1,
    EXTERNAL_INTERRUPT_INT2,        
}interrupt_INx_src;

typedef struct {
    void (*EXT_InterruptHandler)(void);
    interrupt_INx_src source;
    interrupt_INTx_edge_t edge;
    interrupt_priority_t priority;
    pin_config_t mcu_pin;            
}external_interrupt_INx_t;

typedef struct {
  void (*EXT_InterruptHandler_LOW)(void);
  void (*EXT_InterruptHandler_HIGH)(void);
  pin_config_t mcu_pin; 
  interrupt_priority_t priority;
}external_interrupt_RBx_t;
/* Function Declarations*/
/**
 * 
 * @param obj_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_INTx_Init(const external_interrupt_INx_t *obj_t);
/**
 * 
 * @param obj_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_INTx_DeInit(const external_interrupt_INx_t *obj_t);
/**
 * 
 * @param obj_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_RBx_Init(const external_interrupt_RBx_t *obj_t);
/**
 * 
 * @param obj_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_RBx_DeInit(const external_interrupt_RBx_t *obj_t);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

