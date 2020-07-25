/**
******************************************************************************
* @file    stages/stage4/main.c
* @author  George Todorovic - 43537370
* @date    05052020
* @brief   Stage 4 main file for freertos lta1000g and button.
* REFERENCE: csse3010_stage1.pdf
******************************************************************************
*/
/* Includes ---------------------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_os_joystick.h"
#include "s4353737_os_lta1000g.h"
/* FreeRTOS Includes ------------------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Private variables ------------------------------------------------------- */
/* Prototypes -------------------------------------------------------------- */
static void hardware_init();

/**
  * @brief  Main program - flashes onboard LEDs
  * @param  None
  * @retval None
  */
int main() {

    BRD_init();
    hardware_init();

    /* Start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
    vTaskStartScheduler();

    return 0;
}

/**
 * @brief Initialise hardware initialisation functions
 * @param None
 * @retval None
 */
static void hardware_init() {

GPIO_InitTypeDef GPIO_InitStructure;

    portDISABLE_INTERRUPTS();	//Disable interrupts
    
  	BRD_LEDInit();				//Initialise Blue LED
  	s4353737_os_joystick_init();
  	s4353737_os_lta1000g_init();

  	portENABLE_INTERRUPTS();	//Enable interrupts
}

/**
  * @brief  vApplicationStackOverflowHook
  * @param  Task Handler and Task Name
  * @retval None
  */
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName ) {
	/* This function will get called if a task overflows its stack.   If the
	parameters are corrupt then inspect pxCurrentTCB to find which was the
	offending task. */

	BRD_LEDBlueOff();
	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}
