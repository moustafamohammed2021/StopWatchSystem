/* 
 * File:   ecu_button.c
 * Author: MOUSTAFA
 *
 * Created on February 20, 2023, 10:30 PM
 */
#include "ecu_button.h"
/**
 * @brief  function that initialize the direction of the pin input direction 
 * @param btn pointer to struct @ref button_t
 * @return  the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType button_inialize(const button_t *btn){
      Std_ReturnType ret=E_OK;
      if (NULL==btn){
          ret=E_NOT_OK;
      }
      else {
          ret=gpio_Pin_Derction_Intialize(&(btn->button_pin));
          
      }
      return ret;
}
/**
 * function return the status of the pin 
 * @param btn pointer to structure @ref button_t
 * @param btn_status pointer to status of the pin high or low @ref button_status_t
 * @return  the status of the function 
 *          (E_OK) the function done successfully
 *           (E_NOT_OK) the function don't done successfully
 */
Std_ReturnType button_read_status(const button_t *btn,button_status_t *btn_status){
 Std_ReturnType ret=E_OK;
 logic_t button_logic=GPIO_LOW;
      if (NULL==btn || NULL==btn_status){
         ret=E_NOT_OK;
      }
      else {
          gpio_Pin_Read_Logic(&(btn->button_pin),&button_logic);
          if (BUTTON_ACTIVE_HIGH==btn->button_connection){
              if (GPIO_HIGH==button_logic){
                  *btn_status=BUTTON_PRESSED;
              }
              else  {
                  *btn_status=BUTTON_NOT_PRESSED;
              }
          }
          else if (BUTTON_ACTIVE_LOW==btn->button_connection){
              if (GPIO_LOW==button_logic){
                  *btn_status=BUTTON_PRESSED;
              }
              else  {
                  *btn_status=BUTTON_NOT_PRESSED;
              }
          }
          else {/*do nothing*/}
      }
      return ret;
}