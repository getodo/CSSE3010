/** 
 *******************************************************************************
 * @file        mylib/lta1000g/s4353737_os_lta1000g.c
 * @author      George Todorovic - 43537370
 * @date        01062020
 * @brief       lta1000g os files. The lta1000g will light up depending
 *              on which subgrid that is current selected.
 * REFERENCE:   csse3010_project.pdf 
 *******************************************************************************
*/
/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_lta1000g.h"
#include "s4353737_os_pb.h"


/**
 * @brief Initialise LTA1000g task. Will write to the the LTA1000g and display
 *        the current sub grid it is in.
 * @param None
 * @retval None
 */
void s4353737_TaskLTA1000GDisplay() {
    
    struct LTA1000GDisplay LtaRxMsg;
    int ltaSubGrid_x = 0;
    int ltaSubGrid_y = 0;

    while(1) {
        
        if(queueLTA1000GDisplay != NULL) {    
            
            if(xQueueReceive(queueLTA1000GDisplay, &LtaRxMsg, 10)) {
                s4353737_hal_lta1000g_write(ltaSubGrid_x);
            }
        }
        vTaskDelay(1);
    }
}

/**
 * @brief Initialise the LTA1000g GPIO pins and tasks
 * @param None
 * @retval None
 */
extern void s4353737_os_lta1000g_init() 
{
    s4353737_hal_lta1000g_init();

    xTaskCreate( (void *) &s4353737_TaskLTA1000GDisplay, (const signed char *) "LTA1000G", 
        S4353737_OS_LTA1000G_DISPLAY_STACK_SIZE, NULL, S4353737_OS_LTA1000G_DISPLAY_PRIORITY, &taskLTA1000g);
}
 