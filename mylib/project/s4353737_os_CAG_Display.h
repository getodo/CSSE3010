/** 
 *******************************************************************************
 * @file      mylib/project/s4353737_os_CAG_Display.h
 * @author    George Todorovic - 43537370
 * @date      01062020
 * @brief     CAG Display header file.
 * REFERENCE: csse3010_stage4.pdf 
 *******************************************************************************
 */

#ifndef S4353737_OS_CAG_DISPLAY_H
#define S4353737_OS_CAG_DISPLAY_H

/*Includes ------------------------------------------------------------------ */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "string.h"
#include "s4353737_os_CAG_Simulator.h"
/*FreeRTOS Includes --------------------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h" 
#include "queue.h"
#include "semphr.h"
/* Task Stack Allocation ---------------------------------------------------- */
#define S4353737_OS_DISPLAY_GRID_STACK_SIZE     (configMINIMAL_STACK_SIZE * 4)
/* Task Priorities ---------------------------------------------------------- */
#define S4353737_OS_DISPLAY_GRID_PRIORITY       (tskIDLE_PRIORITY + 2)

extern void s4353737_os_display_grid_init();

#endif
