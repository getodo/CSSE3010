/** 
 *******************************************************************************
 * @file       mylib/s4353737_os_joystick.c
 * @author     George Todorovic - 43537370
 * @date       01062020
 * @brief      Joystick OS files. Gives the task functionality.
 * REFERENCE:  csse3010_stage4.pdf 
 *******************************************************************************
*/

/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_joystick.h"
#include "s4353737_hal_joystick.h"

/**
 * @brief Queues the ADC valeus for the y and x directions to be received by 
 *        another task.
 * @param None
 * @retval None
 */
void s4353737_TaskSetColourSpeed() {
    
    struct AdcMessage AdcMessage;

    s4353737_QueueSendAdc = xQueueCreate(10, sizeof(AdcMessage));

    while(1) {

        if(s4353737_QueueSendAdc != NULL) {

            int xAdcValue = S4353737_HAL_JOYSTICK_X_READ();
            int yAdcValue = S4353737_HAL_JOYSTICK_Y_READ();

            AdcMessage.xAdcValue = xAdcValue;
            AdcMessage.yAdcValue = yAdcValue;
            
  
            if(xQueueSendToFront(s4353737_QueueSendAdc, (void*) &AdcMessage, (portTickType) 10) != pdPASS) {

            }
        }

        vTaskDelay(100);
    }
}

