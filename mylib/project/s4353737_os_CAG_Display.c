/** 
 *******************************************************************************
 * @file 		mylib/project/s4353737_os_CAG_Display.c
 * @author 		George Todorovic - 43537370
 * @date 		01062020
 * @brief 		CAG Display os files. Contains task functions and task creation.
 * REFERENCE: 	csse3010_project.pdf 
 ******************************************************************************
*/
/* Includes ---------------------------------------------------------------- */
#include "s4353737_os_CAG_Display.h"
#include "s4353737_os_CAG_Simulator.h"
#include "s4353737_os_joystick.h"
/* Variables --------------------------------------------------------------- */
char* cell_colour = CELL_BLUE; //Initial cell value
int display_delay = 2000;

/**
 * @brief Print the grid to the screen. A task sent from the simulator
 * 		  will provide the grid. This task only prints the grid but
 * 		  does not alter the grids value.
 * @param None
 * @retval None
 */
void TaskDisplayGrid() {
    
	struct GridMessage UpdateGrid;
	
	while(1) {

		if(s4353737_QueueSendGrid != NULL) {

            if(xQueueReceive(s4353737_QueueSendGrid, &UpdateGrid, 10)) {

				SCREEN_CLEAR();
				SCREEN_HOME();

				for(int x = 0; x < GRID_WIDTH; x++) {

					for(int y = 0; y < GRID_HEIGHT; y++) {
						
						if(UpdateGrid.grid[x][y] == 0) {

							portENTER_CRITICAL();
							debug_printf("%s   ", CELL_BLACK);
							portEXIT_CRITICAL();

						} else if(UpdateGrid.grid[x][y] == 1) {

							portENTER_CRITICAL();
							debug_printf("%s   ", cell_colour); //Need joystick to ADC value
							portEXIT_CRITICAL();
						}
					}

					portENTER_CRITICAL();
					debug_printf("\n\r");
					portEXIT_CRITICAL();
				}
			}
		}
		vTaskDelay(2000);
	}
}

/**
 * @brief Reads the joystick ADC x value and changes the colour of the 
 * 		  alive cells on the grid to be updated in the TaskDisplayGrid
 * 	      task. The default colour when the joystick is at a midpoint
 * 		  is blue. At maximum extreme value cells will be white and at
 * 		  minimum extreme values the cells will be black.
 * @param None
 * @retval None
 */
void TaskReadJoystickAdc() {

	struct AdcMessage AdcValues;
	
	while(1) {

		if(s4353737_QueueSendAdc != NULL) {

            if(xQueueReceive(s4353737_QueueSendAdc, &AdcValues, 10)) {

				if(AdcValues.xAdcValue < 512) {
					cell_colour = CELL_BLACK;
            	}

            	else if(AdcValues.xAdcValue < 1024 && AdcValues.xAdcValue > 513) {
					cell_colour = CELL_RED;
            	}

            	else if(AdcValues.xAdcValue < 1536 && AdcValues.xAdcValue > 1023) {
					cell_colour = CELL_GREEN;
            	}

            	else if(AdcValues.xAdcValue < 1699 && AdcValues.xAdcValue > 1536) {
					cell_colour = CELL_YELLOW;
            	}

            	else if(AdcValues.xAdcValue < 2560 && AdcValues.xAdcValue > 1700) {
					cell_colour = CELL_BLUE;
            	}

				else if(AdcValues.xAdcValue < 3072 && AdcValues.xAdcValue > 2561) {
        			cell_colour = CELL_MAGENTA;
    			}

    			else if(AdcValues.xAdcValue < 3584 && AdcValues.xAdcValue > 3073) {
        			cell_colour = CELL_CYAN;
    			}

				else if(AdcValues.xAdcValue < 4096 && AdcValues.xAdcValue > 3585) {
        			cell_colour = CELL_WHITE;
    			}
        	} 
		}
		
		vTaskDelay(1000);
	}
}
	
/**
 * @brief Initialise display grid tasks.
 * @param None
 * @retval None
*/
extern void s4353737_os_display_grid_init() {

    xTaskCreate((void*) &TaskDisplayGrid, (const signed char*) "DISPLAY",
		S4353737_OS_DISPLAY_GRID_STACK_SIZE, NULL, S4353737_OS_DISPLAY_GRID_PRIORITY, NULL);

	xTaskCreate((void*) &TaskReadJoystickAdc, (const signed char*) "ADCValue",
		S4353737_OS_DISPLAY_GRID_STACK_SIZE, NULL, S4353737_OS_DISPLAY_GRID_PRIORITY, NULL);
}

 