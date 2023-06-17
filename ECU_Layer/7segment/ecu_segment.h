/* 
 * File:   ecu_segment.h
 * Author: MOUSTAFA
 *
 * Created on February 22, 2023, 10:52 PM
 */

#ifndef ECU_SEGMENT_H
#define	ECU_SEGMENT_H

/* Section : Includes  */
#include "ecu_segment_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macros Declarations  */
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3
#define NUMBER_OF_PINS_OF_SEGMENT 4
#define MASK_OF_PIN 0x01
/* Section : macros Function Declarations */

/* Data types Declarations */
typedef enum {
    SEGMENT_COMMON_CATHODE=0,
    SEGMENT_COMMON_ANODE,        
}segment_config_t;

typedef struct {
    pin_config_t segment_pin[NUMBER_OF_PINS_OF_SEGMENT];
    segment_config_t segment_status;
}segment_t;
/* Function Declarations*/
/**
 * 
 * @brief function that initialize the pins of the segment output_direction
 * @param seg pointer to seg @ref  segment_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg);

/**
 * 
 * @brief function that write number in pin of the seven segment 
 * @param seg seg pointer to seg @ref  segment_t
 * @param number the number that you want to write 
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg,uint8 number);

#endif	/* ECU_SEGMENT_H */

