/** 
 *******************************************************************************
 * @file        mylib/lta1000g/s4353737_os_lta1000g.h
 * @author      George Todorovic - 43537370
 * @date        05052020
 * @brief       lta1000g os header files
 * REFERENCE:   csse3010_stage4.pdf 
 *******************************************************************************
 */

#ifndef S4353737_OS_LTA1000G_H
#define S4353737_OS_LTA1000G_H

/*Includes ------------------------------------------------------------------ */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_lta1000g.h"
#include "string.h"
/*FreeRTOS Includes --------------------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Task Stack Allocation ---------------------------------------------------- */
#define S4353737_OS_LTA1000G_DISPLAY_STACK_SIZE     (configMINIMAL_STACK_SIZE * 2)
/* Task Priorities ---------------------------------------------------------- */
#define S4353737_OS_LTA1000G_DISPLAY_PRIORITY       (tskIDLE_PRIORITY + 2)
/* Structs ------------------------------------------------------------------ */
struct LTA1000GDisplay {
    int ltaSubGrid_x;
    int ltaSubGrid_y;
};
/* Variables ---------------------------------------------------------------- */
QueueHandle_t queueLTA1000GDisplay;
TaskHandle_t taskLTA1000g;

extern void s4353737_os_lta1000g_init();

#endif
