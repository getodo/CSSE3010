/** 
 *******************************************************************************
 * @file      mylib/project/s4353737_os_CAG_joystick.c
 * @author    George Todorovic - 43537370
 * @date      04052020
 * @brief     Joystick OS files for the project. Contains initalisation of tasks
 *            and required joystick drivers. 
 * REFERENCE: csse3010_project.pdf 
 *******************************************************************************
*/

/* Includes -------------------------------------------------- */
#include "s4353737_os_joystick.h"
#include "s4353737_hal_joystick.h"

/**
 * @brief Initialise joystick GPIO pins and tasks.
 * @param None
 * @retval None
 */
extern void s4353737_os_joystick_init() {
    
    s4353737_hal_joystick_init();

    xTaskCreate((void*) &s4353737_TaskSetColourSpeed, (const signed char *) "ADCVALUE", 
        S4353737_OS_JOYSTICK_ADC_STACK_SIZE, NULL, S4353737_OS_JOYSTICK_ADC_PRIORITY, NULL);

}
