/** 
 **************************************************************
 * @file mylib/s4353737_os_pb.h
 * @author George Todorovic - 43537370
 * @date 01062020
 * @brief pb os driver header files
 * REFERENCE: csse3010_project.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * sxxxxxx_mylib_template_init() - intialise mylib template driver
 * sxxxxxx_mylib_template_set() - set mylib template driver 
 *************************************************************** 
 */

#ifndef S4353737_OS_JOYSTICK_H
#define S4353737_OS_JOYSTICK_H

/*Includes --------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_pb.h"
#include "string.h"
/*FreeRTOS Includes ------------------------------------------ */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Task Stack Allocation ----------------------------------------- */
#define S4353737_OS_LED_STACK_SIZE  (configMINIMAL_STACK_SIZE * 2) 
/* Task Priorities ----------------------------------------------- */
#define S4353737_OS_LED_PRIORITY    (tskIDLE_PRIORITY + 3)
/* Macros -------------------------------------------------------- */
#define GRID_MODE   0
#define MNEMONIC    1

SemaphoreHandle_t s4353737LEDSemaphore;

extern void s4353737_os_pb_init();

#endif
