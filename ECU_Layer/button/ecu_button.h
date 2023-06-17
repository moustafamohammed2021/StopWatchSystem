/* 
 * File:   ecu_button.h
 * Author: MOUSTAFA
 *
 * Created on February 20, 2023, 10:30 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/* Section : Includes  */
#include "ecu_button_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section : Macros Declarations  */

/* Section : macros Function Declarations */

/* Data types Declarations */
typedef enum{
    BUTTON_PRESSED=0,
    BUTTON_NOT_PRESSED        
}button_status_t;

typedef enum {
    BUTTON_ACTIVE_HIGH=0,
    BUTTON_ACTIVE_LOW
}button_connection_t;

typedef struct {
    pin_config_t button_pin;
    button_connection_t button_connection;
    button_status_t  button_status;        
}button_t;
/* Function Declarations*/
Std_ReturnType button_inialize(const button_t *btn);
Std_ReturnType button_read_status(const button_t *btn,button_status_t *btn_status);

#endif	/* ECU_BUTTON_H */

