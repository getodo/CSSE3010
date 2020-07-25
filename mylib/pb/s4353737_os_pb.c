 /** 
 **************************************************************
 * @file mylib/s4353737_os_pb.c
 * @author George Todorovic - 43537370
 * @date 01062020
 * @brief pb os driver files
 * REFERENCE: csse3010_project.pdf 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * sxxxxxx_mylib_template_init() - intialise mylib template driver
 * sxxxxxx_mylib_template_set() - set mylib template driver 
 *************************************************************** 
 */
/* Includes --------------------------------------------------- */
#include "s4353737_os_pb.h"
/* Variables -------------------------------------------------- */
/* Prototypes ------------------------------------------------- */
void LED_Task( void );

void LED_Task( void ) {
    
    //mode = GRID_MODE;
    
    BRD_LEDRedToggle();

    s4353737LEDSemaphore = xSemaphoreCreateBinary();

    for(;;) 
    {
        /* Delay the task for 50ms to save CPU time. */
        vTaskDelay(50);

        portENTER_CRITICAL();
    debug_printf("HELLO TESTING\n\r");
    portEXIT_CRITICAL();

        if(s4353737LEDSemaphore != NULL) 
        {
            portENTER_CRITICAL();

            debug_printf("in task\n\r");

            portEXIT_CRITICAL();
            
            if(xSemaphoreTake(s4353737LEDSemaphore, 10) == pdTRUE) 
            {

            portENTER_CRITICAL();

            debug_printf("in task\n\r");

            portEXIT_CRITICAL();
            
            }
        }

        vTaskDelay(1000);
    }
}

/**
 * @brief create semaphore for pushbutton
 * @param None
 * @retval None
 */
extern void s4353737_os_pb_init() {

    s4353737_hal_pb_on_init();

    xTaskCreate( (void*) &LED_Task, (const signed char*) "LED", 
        S4353737_OS_LED_STACK_SIZE, NULL, S4353737_OS_LED_PRIORITY, NULL);

}

