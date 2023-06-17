/* 
 * File:   ecu_segment.c
 * Author: MOUSTAFA
 *
 * Created on February 22, 2023, 10:52 PM
 */

#include "ecu_segment.h"

/**
 * 
 * @brief function that initialize the pins of the segment output_direction
 * @param seg pointer to seg @ref  segment_t
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg){
        Std_ReturnType ret=E_OK;
      if (NULL==seg){
          ret=E_NOT_OK;
      }
      else {
          ret=gpio_Pin_Intialize(&(seg->segment_pin[SEGMENT_PIN0]));
          ret=gpio_Pin_Intialize(&(seg->segment_pin[SEGMENT_PIN1]));
          ret=gpio_Pin_Intialize(&(seg->segment_pin[SEGMENT_PIN2]));
          ret=gpio_Pin_Intialize(&(seg->segment_pin[SEGMENT_PIN3]));
      }
      return ret;
}
/**
 * 
 * @brief function that write number in pin of the seven segment 
 * @param seg seg pointer to seg @ref  segment_t
 * @param number the number that you want to write 
 * @return the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg,uint8 number){
      Std_ReturnType ret=E_OK;
      if ((NULL==seg) || (number > 9)){
          ret=E_NOT_OK;
      }
      else {
          ret=gpio_Pin_Write_Logic(&(seg->segment_pin[SEGMENT_PIN0]), (number)&  MASK_OF_PIN);
          ret=gpio_Pin_Write_Logic(&(seg->segment_pin[SEGMENT_PIN1]), (number>>1)&  MASK_OF_PIN);
          ret=gpio_Pin_Write_Logic(&(seg->segment_pin[SEGMENT_PIN2]), (number>>2)&  MASK_OF_PIN);
          ret=gpio_Pin_Write_Logic(&(seg->segment_pin[SEGMENT_PIN3]), (number>>3)&  MASK_OF_PIN);
          
      }
      return ret;
    
}
