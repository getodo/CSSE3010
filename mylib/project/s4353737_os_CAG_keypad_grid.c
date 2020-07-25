/** 
 *******************************************************************************
 * @file      mylib/project/s4353737_os_CAG_keypad_grid.c
 * @author    George Todorovic - 43537370
 * @date      01062020
 * @brief     CAG keypad files driver. Initialises keypad tasks and event bits.
 * REFERENCE: csse3010_project.pdf 
 *******************************************************************************
 */

/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_CAG_keypad_grid.h"

/**
 * @brief Initialise the keypad tasks, GPIO pins and event bits. 
 * @param None
 * @retval None
 */
extern void s4353737_os_keypad_grid_init() {

    xTaskCreate((void *) &s4353737_TaskKeypadButtonPress, (const signed char *) "GIVE", 
        S4353737_OS_GIVE_KEYPAD_STACK_SIZE, NULL, S4353737_OS_GIVE_KEYPAD_PRIORITY, &GridGiveTask);

    xTaskCreate((void *) &s4353737_TaskKeypadGiveButtonQueue, (const signed char *) "TAKE", 
        S4353737_OS_TAKE_KEYPAD_STACK_SIZE, NULL, S4353737_OS_TAKE_KEYPAD_PRIORITY, &GridTakeTask);

    /* Create Event Group */
    s4353737_keypadctrl_EventGroup = xEventGroupCreate();
}

 