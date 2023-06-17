/* 
 * File:   mcal_external_interrupt.c
 * Author: MOUSTAFA
 *
 * Created on February 28, 2023, 5:30 AM
 */

#include "mcal_external_interrupt.h"

static InterruptHandler INT0_InterruptHandler=NULL;
static InterruptHandler INT1_InterruptHandler=NULL;
static InterruptHandler INT2_InterruptHandler=NULL;

static InterruptHandler RB4_interruptHandler_LOW=NULL;
static InterruptHandler RB4_interruptHandler_HIGH=NULL;
static InterruptHandler RB5_interruptHandler_LOW=NULL;
static InterruptHandler RB5_interruptHandler_HIGH=NULL;
static InterruptHandler RB6_interruptHandler_LOW=NULL;
static InterruptHandler RB6_interruptHandler_HIGH=NULL;
static InterruptHandler RB7_interruptHandler_LOW=NULL;
static InterruptHandler RB7_interruptHandler_HIGH=NULL;


static Std_ReturnType interrupt_INtx_enable(const external_interrupt_INx_t *obj_t);
static Std_ReturnType interrupt_INtx_disable(const external_interrupt_INx_t *obj_t);
static Std_ReturnType interrupt_INtx_priority(const external_interrupt_INx_t *obj_t);
static Std_ReturnType interrupt_INtx_edge_init(const external_interrupt_INx_t *obj_t);
static Std_ReturnType interrupt_INtx_pin_init(const external_interrupt_INx_t *obj_t);
static Std_ReturnType interrupt_INtx_clear_flag(const external_interrupt_INx_t *obj_t);

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static Std_ReturnType INTx_SetInterruptHandler(const external_interrupt_INx_t *obj_t);


/**
 * 
 * @brief function that initialize(enable the INx 
 * @param obj_t pointer to external_interrupt_INx_t @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_INTx_Init(const external_interrupt_INx_t *obj_t){
       Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
            /*disable the external INTx */
            ret=interrupt_INtx_disable(obj_t);
            /*clear the flag of the interrupt */
            ret=interrupt_INtx_clear_flag(obj_t);
            /*set the edge triggered  */
            ret=interrupt_INtx_edge_init(obj_t);
#if INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
            /*set the priority levels */
            ret=interrupt_INtx_priority(obj_t);
#endif
            
            /*set the pin of the INTx*/
            ret=interrupt_INtx_pin_init(obj_t);
            /*set interrupt callback pointer*/
           ret=INTx_SetInterruptHandler(obj_t);
            /*enable the external INTx */
            ret=interrupt_INtx_enable(obj_t);
       }
       return ret;
}

void INT0_ISR(void){
    /*clear the flag of the INT0 external interrupt */
    EXTERNAL_INT0_FLAG_INTERRUPT_CLEAR();
    /*code here will be excuted in context switch */
    if (INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
    else {/*NOTHING*/}
}
void INT1_ISR(void){
    /*clear the flag of the INT0 external interrupt */
    EXTERNAL_INT1_FLAG_INTERRUPT_CLEAR();
    /*code here will be excuted in context switch */
    if (INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
    else {/*NOTHING*/}
}

void INT2_ISR(void){
    /*clear the flag of the INT0 external interrupt */
    EXTERNAL_INT2_FLAG_INTERRUPT_CLEAR();
    /*code here will be executed in context switch */
    if (INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
    else {/*NOTHING*/}
}

void RB4_ISR(uint8 RB4_source){
    /*clear the flag of the interrupt RBx*/
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*code will be executed in context switch   */
    if (0==RB4_source){
     if (RB4_interruptHandler_LOW){
        RB4_interruptHandler_LOW();
     }}
    else if (1==RB4_source){
        if (RB4_interruptHandler_HIGH){
        RB4_interruptHandler_HIGH();
     }
    }
    else {/*NOTHING*/}
}
void RB5_ISR(uint8 RB5_source){
    /*clear the flag of the interrupt RBx*/
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*code will be executed in context switch   */
    if (0==RB5_source){
     if (RB5_interruptHandler_LOW){
        RB5_interruptHandler_LOW();
     }}
    else if (1==RB5_source){
        if (RB5_interruptHandler_HIGH){
        RB5_interruptHandler_HIGH();
     }
    }
    else {/*NOTHING*/}
}
void RB6_ISR(uint8 RB6_source){
    /*clear the flag of the interrupt RBx*/
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*code will be executed in context switch   */
    if (0==RB6_source){
     if (RB6_interruptHandler_LOW){
        RB6_interruptHandler_LOW();
     }}
    else if (1==RB6_source){
        if (RB6_interruptHandler_HIGH){
        RB6_interruptHandler_HIGH();
     }
    }
    else {/*NOTHING*/}
}
void RB7_ISR(uint8 RB7_source){
    /*clear the flag of the interrupt RBx*/
    EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
    /*code will be executed in context switch   */
    if (0==RB7_source){
     if (RB7_interruptHandler_LOW){
        RB7_interruptHandler_LOW();
     }}
    else if (1==RB7_source){
        if (RB7_interruptHandler_HIGH){
        RB7_interruptHandler_HIGH();
     }
    }
    
    else {/*NOTHING*/}
}
/**
 * 
 * @brief function that disable the INx 
 * @param obj_t pointer to external_interrupt_INx_t @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_INTx_DeInit(const external_interrupt_INx_t *obj_t){
  Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           ret=interrupt_INtx_disable(obj_t);
       }
       return ret;

}
/**
 * 
 * @brief function that initialize (enable) the RBx 
 * @param obj_t pointer to external_interrupt_RBx_t @ref external_interrupt_RBx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_RBx_Init(const external_interrupt_RBx_t *obj_t){
    Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           /*disable the external OnChange RBx interrupt */
           EXTERNAL_RBx_INTERRUPT_DISABLE();
           /*clear the flag of the interrupt of the RBx */
           EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
           /*initialize the pin of the interrupt of RBx*/
           ret=gpio_Pin_Derction_Intialize(&(obj_t->mcu_pin));
           /*set the priority of the interrupt RBx */
#if INTERRUPT_PRIORITY_LEVELS== INTERRUPT_FREATUERE_ENABLE
           INTERRUPT_PRIORITY_LEVEVLS_ENABLE();
           if (INTERRUPT_LOW_PRIORITY==obj_t->priority){
                 INTERRUPT_PRIORITY_LOW_LEVEVL_ENABLE();  
                 EXTERNAL_RBx_INTERRUPT_LOW_PRIORITY();  
           }
           else if (INTERRUPT_HIGH_PRIORITY==obj_t->priority){
               INTERRUPT_PRIORITY_HIGH_LEVEVL_ENABLE();
                EXTERNAL_RBx_INTERRUPT_HIGHY_PRIORITY();   
           }
           else {/*NOTHING*/}
#else 
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PERiPHERALS_INTERRUPT_ENABLE();
#endif
           /*set the call back function of the RBx interrupt */
            switch (obj_t->mcu_pin.pin){
                case GPIO_PIN4:
                    RB4_interruptHandler_LOW=obj_t->EXT_InterruptHandler_LOW;
                    RB4_interruptHandler_HIGH=obj_t->EXT_InterruptHandler_HIGH;
                    ret=E_OK;
                   break;
                case GPIO_PIN5:
                    RB5_interruptHandler_LOW=obj_t->EXT_InterruptHandler_LOW;
                    RB5_interruptHandler_HIGH=obj_t->EXT_InterruptHandler_HIGH;
                    ret=E_OK;
                   break;
                   case  GPIO_PIN6:
                    RB6_interruptHandler_LOW=obj_t->EXT_InterruptHandler_LOW;
                    RB6_interruptHandler_HIGH=obj_t->EXT_InterruptHandler_HIGH;
                       ret=E_OK;
                   break;
                   case GPIO_PIN7:
                    RB7_interruptHandler_LOW=obj_t->EXT_InterruptHandler_LOW;
                    RB7_interruptHandler_HIGH=obj_t->EXT_InterruptHandler_HIGH;
                       ret=E_OK;
                   break;
                default: ret=E_NOT_OK;
            }
           /*enable the external OnChange RBx interrupt */
            EXTERNAL_RBx_INTERRUPT_ENABLE();
             ret=E_OK;
           
       }
       return ret;

}
/**
 * 
 *  @brief function that  (disable) the INx
 * @param obj_t pointer to external_interrupt_RBx_t @ref external_interrupt_RBx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType external_interrupt_RBx_DeInit(const external_interrupt_RBx_t *obj_t){
    Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
            /*disable the external OnChange RBx interrupt */
           EXTERNAL_RBx_INTERRUPT_DISABLE();
           /*clear the flag of the interrupt of the RBx */
           EXTERNAL_RBx_INTERRUPT_FLAG_CLEAR();
       }
       return ret;

}
/**
 *  
 * enable interrupt INTx source 
 * @param obj_t pointer to structure  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType interrupt_INtx_enable(const external_interrupt_INx_t *obj_t){
    Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           /*switch case enable specified pin  */
           switch(obj_t->source){
               case EXTERNAL_INTERRUPT_INT0:
#if INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
                INTERRUPT_PRIORITY_HIGH_LEVEVL_ENABLE();
 #else  
               INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
               INTERRUPT_PERiPHERALS_INTERRUPT_ENABLE();
#endif
               EXTERNAL_INT0_INTERRUPT_ENABLE();
               ret=E_OK;
                break;
             case EXTERNAL_INTERRUPT_INT1:
#if INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
                 INTERRUPT_PRIORITY_LEVEVLS_ENABLE();
                 if (INTERRUPT_HIGH_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_HIGH_LEVEVL_ENABLE();
                     EXTERNAL_INT1_INTERRUPT_HIGHY_PRIORITY();
                 }
                 else if (INTERRUPT_LOW_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_LOW_LEVEVL_ENABLE();
                     EXTERNAL_INT1_INTERRUPT_LOW_PRIORITY();
                 }
                 else {/* NOTHING */}
 #else  
               INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
               INTERRUPT_PERiPHERALS_INTERRUPT_ENABLE();
#endif
               EXTERNAL_INT1_INTERRUPT_ENABLE();
               ret=E_OK;
                break;
                case EXTERNAL_INTERRUPT_INT2:
#if INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
                 INTERRUPT_PRIORITY_LEVEVLS_ENABLE();
                 if (INTERRUPT_HIGH_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_HIGH_LEVEVL_ENABLE();
                     EXTERNAL_INT2_INTERRUPT_HIGHY_PRIORITY();
                 }
                 else if (INTERRUPT_LOW_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_LOW_LEVEVL_ENABLE();
                     EXTERNAL_INT2_INTERRUPT_LOW_PRIORITY();
                 }
                 else {/* NOTHING */}
 #else  
               INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
               INTERRUPT_PERiPHERALS_INTERRUPT_ENABLE();
#endif
               EXTERNAL_INT2_INTERRUPT_ENABLE();
               ret=E_OK;
                break; 
                
               default:ret=E_NOT_OK;
           }
       }
       return ret;
}
/**
 * 
 * disable interrupt INTx source
 * @param obj_t pointer to structure  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType interrupt_INtx_disable(const external_interrupt_INx_t *obj_t){
    Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           /* switch case that disable the pin of interrupt*/
           switch(obj_t->source){
               case EXTERNAL_INTERRUPT_INT0:
                   EXTERNAL_INT0_INTERRUPT_DISABLE();
                   ret=E_OK;
                   break;
               case EXTERNAL_INTERRUPT_INT1:
                   EXTERNAL_INT1_INTERRUPT_DISABLE();
                   ret=E_OK;
                   break;
                   case EXTERNAL_INTERRUPT_INT2:
                   EXTERNAL_INT2_INTERRUPT_DISABLE();
                   ret=E_OK;
                   break;
                default:ret=E_NOT_OK;
           }
           
       }
       return ret;
}
/**
 * 
 * enable the priority level low or high 
 * @param obj_t pointer to structure  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
#if INTERRUPT_PRIORITY_LEVELS==INTERRUPT_FREATUERE_ENABLE
static Std_ReturnType interrupt_INtx_priority(const external_interrupt_INx_t *obj_t){
Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           /* switch case made the priority of the pins of the interrupt */
            switch(obj_t->source){
             case EXTERNAL_INTERRUPT_INT1:
                 INTERRUPT_PRIORITY_LEVEVLS_ENABLE(); 
                 if (INTERRUPT_HIGH_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_HIGH_LEVEVL_ENABLE();
                     EXTERNAL_INT1_INTERRUPT_HIGHY_PRIORITY();
                 }
                 else if (INTERRUPT_LOW_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_LOW_LEVEVL_ENABLE();
                     EXTERNAL_INT1_INTERRUPT_LOW_PRIORITY();
                 }
                 else {/* NOTHING */}
  
               ret=E_OK;
                break;
                
                case EXTERNAL_INTERRUPT_INT2:
                 INTERRUPT_PRIORITY_LEVEVLS_ENABLE();
                 if (INTERRUPT_HIGH_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_HIGH_LEVEVL_ENABLE();
                     EXTERNAL_INT2_INTERRUPT_HIGHY_PRIORITY();
                 }
                 else if (INTERRUPT_LOW_PRIORITY==obj_t->priority){
                     INTERRUPT_PRIORITY_LOW_LEVEVL_ENABLE();
                     EXTERNAL_INT2_INTERRUPT_LOW_PRIORITY();
                 }
                 else {/* NOTHING */}
                 
               ret=E_OK;
                break;  
                
              default:ret=E_NOT_OK;
           }
       }
       return ret;
}
#endif
/**
 * 
 * made the detect falling edge or rising edge 
 * @param obj_t pointer to structure  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType interrupt_INtx_edge_init(const external_interrupt_INx_t *obj_t){
  Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           /* switch case made the interrupt is  falling edge or rising edge for the three pins */
            switch(obj_t->source){
               case EXTERNAL_INTERRUPT_INT0:
                   if (INTERRUPT_FALLING_EDGE==obj_t->edge){
                       EXTERNAL_INT0_FALLIING_EDGE();
                   }
                   else if (INTERRUPT_RISING_EDGE==obj_t->edge){
                       EXTERNAL_INT0_RISIING_EDGE();
                   }
                   else {/* NOTHING*/}
                   ret=E_OK;
                   break;
               case EXTERNAL_INTERRUPT_INT1:
                   if (INTERRUPT_FALLING_EDGE==obj_t->edge){
                       EXTERNAL_INT1_FALLIING_EDGE();
                   }
                   else if (INTERRUPT_RISING_EDGE==obj_t->edge){
                       EXTERNAL_INT1_RISIING_EDGE();
                   }
                   else {/*NOTHING*/}
                   ret=E_OK;
                   break;
                   case EXTERNAL_INTERRUPT_INT2:
                   if (INTERRUPT_FALLING_EDGE==obj_t->edge){
                       EXTERNAL_INT2_FALLIING_EDGE();
                   }
                   else if (INTERRUPT_RISING_EDGE==obj_t->edge){
                       EXTERNAL_INT2_RISIING_EDGE();
                   }
                   else {/* NOTHING*/}
                   ret=E_OK;
                   break;
                default:ret=E_NOT_OK;
       }
      
       }
   return ret;
}
/**
 * 
 * initialize the pin source  
 * @param obj_t pointer to structure  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType interrupt_INtx_pin_init(const external_interrupt_INx_t *obj_t){
   Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           ret=gpio_Pin_Intialize(&(obj_t->mcu_pin)); /* initialize the pin of the interrupt */
       }
       return ret;
}
/**
 * 
 * clear the flag after the interrupt happened  
 * @param obj_t pointer to structure  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType interrupt_INtx_clear_flag(const external_interrupt_INx_t *obj_t){
Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
           switch(obj_t->source){
               case EXTERNAL_INTERRUPT_INT0:
                   EXTERNAL_INT0_FLAG_INTERRUPT_CLEAR();/* clear the flag of INT0*/
                   ret=E_OK;
                   break;
               case EXTERNAL_INTERRUPT_INT1:
                   EXTERNAL_INT1_FLAG_INTERRUPT_CLEAR();/* clear the flag of INT1*/
                   ret=E_OK;
                   break;
                   case EXTERNAL_INTERRUPT_INT2:
                   EXTERNAL_INT2_FLAG_INTERRUPT_CLEAR();/* clear the flag of INT2*/
                   ret=E_OK;
                   break;
                default:ret=E_NOT_OK;
           }
       }
       return ret;
}
/**
 * 
 * set pointer to function point to pointer of INT0
 * @param InterruptHandler pointer to function 
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret=E_OK;
       if (InterruptHandler==NULL){
           ret=E_NOT_OK;
       }
       else {
           INT0_InterruptHandler=InterruptHandler;
            ret=E_OK;
           
       }
    return ret;
}
/**
 *set pointer to function point to pointer of INT1
 * @param InterruptHandler pointer to function 
 * @return he status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)){
 Std_ReturnType ret=E_OK;
       if (InterruptHandler==NULL){
           ret=E_NOT_OK;
       }
       else {
           INT1_InterruptHandler=InterruptHandler;
            ret=E_OK;
       }
    return ret;
}
/**
 * set pointer to function point to pointer of INT2
 * @param InterruptHandler pointer to function 
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
 Std_ReturnType ret=E_OK;
       if (InterruptHandler==NULL){
           ret=E_NOT_OK;
       }
       else {
           INT2_InterruptHandler=InterruptHandler;
            ret=E_OK;
           
       }
    return ret;
}
/**
 * 
 * detect the interrupt that will happened 
 * @param obj_t pointer  @ref external_interrupt_INx_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
static Std_ReturnType INTx_SetInterruptHandler(const external_interrupt_INx_t *obj_t){
 Std_ReturnType ret=E_OK;
       if (obj_t==NULL){
           ret=E_NOT_OK;
       }
       else {
            switch(obj_t->source){
               case EXTERNAL_INTERRUPT_INT0:
                   ret=INT0_SetInterruptHandler(obj_t->EXT_InterruptHandler);
                   break;
               case EXTERNAL_INTERRUPT_INT1:
                     ret=INT1_SetInterruptHandler(obj_t->EXT_InterruptHandler);
                   break;
                   case EXTERNAL_INTERRUPT_INT2:
                    ret=INT2_SetInterruptHandler(obj_t->EXT_InterruptHandler);
                   break;
                default:ret=E_NOT_OK;
           }
           
       }
    return ret;
}