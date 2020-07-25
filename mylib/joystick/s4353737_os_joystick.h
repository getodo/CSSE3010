/** 
 *******************************************************************************
 * @file        mylib/joystick/s4353737_os_joystick.h
 * @author      George Todorovic - 43537370
 * @date        05052020
 * @brief       Joystick os header file
 * REFERENCE:   csse3010_stage4.pdf 
 *******************************************************************************
 */

#ifndef S4353737_OS_JOYSTICK_H
#define S4353737_OS_JOYSTICK_H

/*Includes ------------------------------------------------------------------ */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_joystick.h"
#include "string.h"
/*FreeRTOS Includes --------------------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Task Stack Allocation ---------------------------------------------------- */
#define S4353737_OS_JOYSTICK_ADC_STACK_SIZE      (configMINIMAL_STACK_SIZE * 2)  
/* Task Priorities ---------------------------------------------------------- */
#define S4353737_OS_JOYSTICK_ADC_PRIORITY        (tskIDLE_PRIORITY + 2)
/* Private Struct ------------------------------------------------------------*/
struct AdcMessage {
    int xAdcValue;
    int yAdcValue;
};
/* Variables ---------------------------------------------------------------- */
SemaphoreHandle_t s4353737_SemaphoreZButton;
QueueHandle_t     s4353737_QueueSendAdc;
int pauseTask;

extern void s4353737_os_joystick_init();
void s4353737_TaskSetColourSpeed();

#endif
