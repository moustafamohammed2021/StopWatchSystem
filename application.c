/* 
 * File:   application.c
 * Author: MOUSTAFA
 * Title:Project of Stop Watch in Simulation using Pic18f4620
 * Created on June 4, 2023, 5:43 AM
 */

#include "appilcation.h"
#include "MCAL_Layer/GPIO/hal_gpio.h"
#include "MCAL_Layer/TIMER1/hal_timer1.h"
#include "ECU_Layer/7segment/ecu_segment.h"
#include "ECU_Layer/button/ecu_button.h"


void Timer1_Interrupt(void);
volatile uint16 TimerOverFlow;
volatile uint8 Seconds=0,Minutes=0,Hours=0;
volatile button_status_t Button1Status=BUTTON_NOT_PRESSED;
volatile button_status_t Button2Status=BUTTON_NOT_PRESSED;
volatile button_status_t Button3Status=BUTTON_NOT_PRESSED;
/*Configuration for Seven Segments*/
segment_t Seg_Obj={.segment_status=SEGMENT_COMMON_ANODE,
                   .segment_pin[SEGMENT_PIN0].port=PORTC_INDEX,
                   .segment_pin[SEGMENT_PIN0].pin=GPIO_PIN0,
                   .segment_pin[SEGMENT_PIN0].direction=GPIO_DIRECTION_OUTPUT,
                   .segment_pin[SEGMENT_PIN1].port=PORTC_INDEX,
                   .segment_pin[SEGMENT_PIN1].pin=GPIO_PIN1,
                   .segment_pin[SEGMENT_PIN1].direction=GPIO_DIRECTION_OUTPUT,
                   .segment_pin[SEGMENT_PIN2].port=PORTC_INDEX,
                   .segment_pin[SEGMENT_PIN2].pin=GPIO_PIN2,
                   .segment_pin[SEGMENT_PIN2].direction=GPIO_DIRECTION_OUTPUT,
                   .segment_pin[SEGMENT_PIN3].port=PORTC_INDEX,
                   .segment_pin[SEGMENT_PIN3].pin=GPIO_PIN3,
                   .segment_pin[SEGMENT_PIN3].direction=GPIO_DIRECTION_OUTPUT};

/*Configuration For Enable Of The Seven Segment*/
pin_config_t Enable1={.port=PORTD_INDEX,.pin=GPIO_PIN0,.direction=GPIO_DIRECTION_OUTPUT};
pin_config_t Enable2={.port=PORTD_INDEX,.pin=GPIO_PIN1,.direction=GPIO_DIRECTION_OUTPUT};
pin_config_t Enable3={.port=PORTD_INDEX,.pin=GPIO_PIN2,.direction=GPIO_DIRECTION_OUTPUT};
pin_config_t Enable4={.port=PORTD_INDEX,.pin=GPIO_PIN3,.direction=GPIO_DIRECTION_OUTPUT};
pin_config_t Enable5={.port=PORTD_INDEX,.pin=GPIO_PIN4,.direction=GPIO_DIRECTION_OUTPUT};
pin_config_t Enable6={.port=PORTD_INDEX,.pin=GPIO_PIN5,.direction=GPIO_DIRECTION_OUTPUT};

/*Configuration for Timer1 To Calculate The Time Perfect*/
timer1_config_t Timer1_Obj={.TIMER1_HandlerInterrupt=Timer1_Interrupt,
                            .preloaded_value=15536,
                            .timer1_mode_timer_or_counter=TIMER1_TIMER_MODE_CFG,
                            .timer1_mode_wr_reg=TIMER1_8BIT_MODE_CFG,
                            .timer1_oscillator_enable=TIMER1_OSCILLATOR_DISABLE_CFG,
                            .timer1_pre_scaler_val=TIMER1_INPUT_CLK_PRESCALER_DIV_4};

button_t Btn1={.button_connection=BUTTON_ACTIVE_HIGH,
              .button_status=BUTTON_NOT_PRESSED,
              .button_pin.port=PORTA_INDEX,.button_pin.pin=GPIO_PIN0,
              .button_pin.direction=GPIO_DIRECTION_INPUT,.button_pin.logic=GPIO_LOW};
button_t Btn2={.button_connection=BUTTON_ACTIVE_HIGH,
              .button_status=BUTTON_NOT_PRESSED,
              .button_pin.port=PORTA_INDEX,.button_pin.pin=GPIO_PIN1,
              .button_pin.direction=GPIO_DIRECTION_INPUT,.button_pin.logic=GPIO_LOW};
button_t Btn3={.button_connection=BUTTON_ACTIVE_HIGH,
              .button_status=BUTTON_NOT_PRESSED,
              .button_pin.port=PORTA_INDEX,.button_pin.pin=GPIO_PIN2,
              .button_pin.direction=GPIO_DIRECTION_INPUT,.button_pin.logic=GPIO_LOW};
/*
 *
 */
int main(void) {
    seven_segment_initialize(&Seg_Obj);
    Timer1_Init(&Timer1_Obj);
    gpio_Pin_Intialize(&Enable1);
    gpio_Pin_Intialize(&Enable2);
    gpio_Pin_Intialize(&Enable3);
    gpio_Pin_Intialize(&Enable4);
    gpio_Pin_Intialize(&Enable5);
    gpio_Pin_Intialize(&Enable6);
    button_inialize(&Btn1);
    button_inialize(&Btn2);
    button_inialize(&Btn3);
    ADCON1bits.PCFG=0x0F;
    CMCONbits.CM=111;
    while(1){
        button_read_status(&Btn1,&Button1Status);
        button_read_status(&Btn2,&Button2Status);
        button_read_status(&Btn3,&Button3Status);
        
        if(BUTTON_PRESSED==Button1Status){
            Timer1_DeInit(&Timer1_Obj);
            
        }
        if(BUTTON_PRESSED==Button2Status){
            Timer1_Init(&Timer1_Obj);
        }
        if(BUTTON_PRESSED==Button3Status){
            TimerOverFlow=0;
            Seconds=0;
            Minutes=0;
            Hours=0;
        }
        /* Configuration For Seconds Segments to Show it*/
        gpio_Port_Write_Logic(PORTD_INDEX,0b00000001);
        seven_segment_write_number(&Seg_Obj,(Hours/10));
        __delay_us(7500);
        gpio_Port_Write_Logic(PORTD_INDEX,0b00000010);
        seven_segment_write_number(&Seg_Obj,(Hours%10));
        __delay_us(7500);
        /* Configuration For Minutes Segments to Show it*/
        gpio_Port_Write_Logic(PORTD_INDEX,0b00000100);
        seven_segment_write_number(&Seg_Obj,(Minutes/10));
        __delay_us(7500);
        gpio_Port_Write_Logic(PORTD_INDEX,0b00001000);
        seven_segment_write_number(&Seg_Obj,(Minutes%10));
        __delay_us(7500);
        /* Configuration For Hours Segments to Show it */
        gpio_Port_Write_Logic(PORTD_INDEX,0b00010000);
        seven_segment_write_number(&Seg_Obj,(Seconds/10));
        __delay_us(7500);
        gpio_Port_Write_Logic(PORTD_INDEX,0b00100000);
        seven_segment_write_number(&Seg_Obj,(Seconds%10));
        __delay_us(7500); 
   }
    return (0);
}

void Timer1_Interrupt(void){
    TimerOverFlow++;
        if(TimerOverFlow==10){
            Seconds++;
            TimerOverFlow=0;
          }
        if(Seconds==60){
            Minutes++;
            Seconds=0;
        }
        if(Minutes==60){
            Hours++;
            Minutes=0;
        }
        if(Hours==24){
            Hours=0;
       }
}