/** 
 **************************************************************
 * @file        mylib/project/s4353737_os_pb.h
 * @author      George Todorovic - 43537370
 * @date        01062020
 * @brief       Pushbutton os driver header files
 * REFERENCE:   csse3010_project.pdf 
 ***************************************************************
 */

#ifndef S4353737_OS_PB_H
#define S4353737_OS_PB_H
/*Includes ------------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_pb.h"
#include "string.h"
#include "s4353737_os_CAG_Simulator.h"
/*FreeRTOS Includes ---------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Task Stack Allocation ----------------------------------------- */
#define S4353737_OS_JOYSTICK_BUTTON_STACK_SIZE   (configMINIMAL_STACK_SIZE * 3)
#define S4353737_OS_LED_STACK_SIZE               (configMINIMAL_STACK_SIZE * 3)
/* Task Priorities ----------------------------------------------- */
#define S4353737_OS_JOYSTICK_BUTTON_PRIORITY     (tskIDLE_PRIORITY + 3)
#define S4353737_OS_LED_PRIORITY                 (tskIDLE_PRIORITY + 8)
/* Macros -------------------------------------------------------- */
#define GRID_MODE       0
#define MNEMONIC_MODE   1
/* Variables ----------------------------------------------------- */
SemaphoreHandle_t s4353737LEDSemaphore;
SemaphoreHandle_t s4353737_SemaphoreZButton;
unsigned int currentMode;

extern void s4353737_os_pb_init();

#endif
