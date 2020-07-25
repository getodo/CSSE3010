/**
******************************************************************************
* @file    stages/stage1/main.c
* @author  George Todorovic - 43537370
* @date    11032020
* @brief   Stage 1 LTA1000g main.
* REFERENCE: csse3010_stage1.pdf
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_lta1000g.h"
#include "s4353737_hal_pb.h"
#include "s4353737_hal_iss.h"
/* Private variables ---------------------------------------------------------*/
int shift = 1;
unsigned short value = 3;
/* Private function prototypes -----------------------------------------------*/
void init_hardware();
void update_value();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/**
  * @brief  Main program - flashes onboard LEDs
  * @param  None
  * @retval None
  */
void main() {
    init_hardware();
    while(1) {
        s4353737_hal_lta1000g_write(value);
    }
}

/**
 * @brief GPIO Interrupt call function. Depending on the event the code will 
 *        execute an interrupt to change the direction of the MPD or 
 *        to increment the MPD
 * @param GPIO_Pin: The pin to be on which an interrupt occurs
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == BRD_A0_PIN) {

        unsigned int tempEvent = 
            s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_1);
        s4353737_hal_iss_synchroniser(S4353737_HAL_ISS_SOURCE_1);

        if(s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_1) == 11) {

            s4353737_hal_iss_eventcounter_reset(S4353737_HAL_ISS_SOURCE_1);

        }
        if(s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_1) 
            != tempEvent) {  

            update_value();

        }
    }
    if(GPIO_Pin == GPIO_PIN_13) {

        unsigned int tempEvent = 
            s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_2);
        s4353737_hal_iss_synchroniser(S4353737_HAL_ISS_SOURCE_2);

        if(s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_2) == 11) {     
           
            s4353737_hal_iss_eventcounter_reset(S4353737_HAL_ISS_SOURCE_2);

        }
        if(s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_2) 
            != tempEvent) {
            
            shift = (shift == 1) ?  0 : 1;

        }
    } 
}

/**
 * @brief Override default mapping of this handler
 * @param None
 * @retval None
 */
void EXTI15_10_IRQHandler() {
    s4353737_hal_pb_on_isr();
}

/**
 * @brief Overrider default mapping of this handler
 * @param None
 * @retval None
 */
void EXTI3_IRQHandler() {
    s4353737_hal_pb_iss_isr();
}

/**
 * @brief Initialise hardware initialisation functions
 * @param None
 * @retval None
 */
void init_hardware() {
    BRD_init();
    s4353737_hal_lta1000g_init();
    s4353737_hal_pb_on_init();
    s4353737_hal_pb_iss_init();
}

/**
 * @brief Updates the MPD value on event
 * @param
 * @retval None
*/
void update_value() {
    if(value == 3) {

        shift = 1;

    }
    if(value == 768) {

        shift = 0;

    }
    if(shift == 1) {

        value = value << 1;
        debug_printf("0x%04x\n\r", value);

    }
    if(shift == 0) {

        value = value >> 1;
        debug_printf("0x%04x\n\r", value);

    }
}      