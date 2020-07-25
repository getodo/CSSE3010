/** 
 *******************************************************************************
 * @file 		mylib/keypad/s4353737_os_keypad.c
 * @author 		George Todorovic - 43537370
 * @date 		01062020
 * @brief 		Keypad OS task functions to be implemented in the keypad CAG files.
 * REFERENCE: 	csse3010_project.pdf 
 ******************************************************************************
 */

/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_keypad.h"
/* Variables ---------------------------------------------------------------- */
int subGridx 	= 0;
int subGridy 	= 0;
int subGrid_x 	= 0;
int subGrid_y 	= 0;
int type 		= 0;
int command		= 0;
int keypadCount = 0;
int queueFlag 	= 0;
int keyState 	= 0;
u_int16_t buttonBuffer[13];
/* Mnemonic Arrays Variables ------------------------------------------------ */
						   /* 7, 7, 7, 7, 8, 5, 5, 5 */
u_int16_t createSTL[8] 	= {1 << 8, 1 << 8, 1 << 8, 1 << 8, 1 << 9, 1 << 5, 1 << 5, 1 << 5};
						   /* 6, 6, 6, 7, 7, 7, 7, 2, 2, 2 */
u_int16_t createOSC[10] = {1 << 6, 1 << 6, 1 << 6, 1 << 8, 1 << 8, 1 << 8, 1 << 8, 1 << 1, 1 << 1, 1 << 1};
						   /* 4, 5, 5, 5, 3 */
u_int16_t createGLD[5] 	= {1 << 4, 1 << 5, 1 << 5, 1 << 5, 1 << 2};
						   /* 3, 5, 5, 5, 8 */
u_int16_t driverDLT[5] 	= {1 << 2, 1 << 5, 1 << 5, 1 << 5, 1 << 9};
						   /* 2, 2, 2, 7, 7, 7, 3, 3 */
u_int16_t driveCRE[8] 	= {1 << 1, 1 << 1, 1 << 1, 1 << 8, 1 << 8, 1 << 8, 1 << 2, 1 << 2};
/* Prototype ---------------------------------------------------------------- */
int compare_array_elements(u_int16_t a[], u_int16_t b[], int size);
int check_xy_coordinate(uint16_t xy);
int check_life_type(uint16_t type);
void store_cell_life();

/**
  * @brief  Give Task. Set LED ON and OFF events every second.
  * @param  None
  * @retval None
  */
void s4353737_TaskKeypadButtonPress() {

	EventBits_t uxBits;

	for (;;) {

		if ((KeypadValue & BUT_ONE) == BUT_ONE) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_ONE);

		} else if((KeypadValue & BUT_TWO) == BUT_TWO) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_TWO);

		} else if((KeypadValue & BUT_THREE) == BUT_THREE) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_THREE);

		} else if((KeypadValue & BUT_FOUR) == BUT_FOUR) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_FOUR);

		} else if((KeypadValue & BUT_FIVE) == BUT_FIVE) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_FIVE);

		} else if((KeypadValue & BUT_SIX) == BUT_SIX) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_SIX);

		} else if((KeypadValue & BUT_SEVEN) == BUT_SEVEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_SEVEN);

		} else if((KeypadValue & BUT_EIGHT) == BUT_EIGHT) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_EIGHT);

		} else if((KeypadValue & BUT_NINE) == BUT_NINE) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_NINE);

		} else if((KeypadValue & BUT_TEN) == BUT_TEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_TEN);

		} else if((KeypadValue & BUT_ELEVEN) == BUT_ELEVEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_ELEVEN);

		} else if((KeypadValue & BUT_TWELEVE) == BUT_TWELEVE) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_TWELEVE);

		} else if((KeypadValue & BUT_THIRTEEN) == BUT_THIRTEEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_THIRTEEN);

		} else if((KeypadValue & BUT_FOURTEEN) == BUT_FOURTEEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_FOURTEEN);

		} else if((KeypadValue & BUT_FIFTEEN) == BUT_FIFTEEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_FIFTEEN);

		} else if((KeypadValue & BUT_SIXTEEN) == BUT_SIXTEEN) {

			uxBits = xEventGroupSetBits(s4353737_keypadctrl_EventGroup, BUT_SIXTEEN);

		} 

		KeypadValue = 0;

        s4353737_hal_keypad_fsmprocessing();

		/* Wait for 100ms */
		vTaskDelay(100);
	}
}

/**
  * @brief  Take Task. Used to check for LED ON and OFF events. Toggles LED.
  * @param  None
  * @retval None
  */
void s4353737_TaskKeypadGiveButtonQueue() {

	EventBits_t uxBits;

	struct ButtonMessage ButtonMessage;

	s4353737_QueueButtonPress  = xQueueCreate(10, sizeof(ButtonMessage));

	for (;;) {
		/* Wait a maximum of 100ms for either bit 0 or bit 1 to be set within
    	   the event group.  Clear the bits before exiting. */
    	uxBits = xEventGroupWaitBits(s4353737_keypadctrl_EventGroup, KEYPADCTRL_EVNT, pdTRUE, pdFALSE, 10);

		if ((uxBits & BUT_ONE) == BUT_ONE) {

			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 1;
				ButtonMessage.cell_x = 0 + (3 * subGridy);
				ButtonMessage.cell_y = 0 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {

                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_ONE);		
		}

		if ((uxBits & BUT_TWO) == BUT_TWO) {

			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 2;
				ButtonMessage.cell_x = 0 + (3 * subGridy);
				ButtonMessage.cell_y = 1 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}
			
			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_TWO);		
		}

		if ((uxBits & BUT_THREE) == BUT_THREE) {

			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 3;
				ButtonMessage.cell_x = 0 + (3 * subGridy);
				ButtonMessage.cell_y = 2 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {

                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}	
			
			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_THREE);		
		}

		if ((uxBits & BUT_FOUR) == BUT_FOUR) {
			
			if(s4353737_QueueButtonPress != NULL) {

				ButtonMessage.button = 10;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}
			
			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_FOUR);	
		}

		if ((uxBits & BUT_FIVE) == BUT_FIVE) {

			if(s4353737_QueueButtonPress != NULL) {

				ButtonMessage.button = 4;
				ButtonMessage.cell_x = 1 + (3 * subGridy);
				ButtonMessage.cell_y = 0 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_FIVE);		
		}

		if ((uxBits & BUT_SIX) == BUT_SIX) {

			if(s4353737_QueueButtonPress != NULL) {

				ButtonMessage.button = 5;
				ButtonMessage.cell_x = 1 + (3 * subGridy);
				ButtonMessage.cell_y = 1 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {

                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_SIX);		
		}

		if ((uxBits & BUT_SEVEN) == BUT_SEVEN) {

			if(s4353737_QueueButtonPress != NULL) {

				ButtonMessage.button = 6;
				ButtonMessage.cell_x = 1 + (3 * subGridy);
				ButtonMessage.cell_y = 2 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {

                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_SEVEN);
		}

		if ((uxBits & BUT_EIGHT) == BUT_EIGHT) {
			
			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 11;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_EIGHT);		
		}

		if ((uxBits & BUT_NINE) == BUT_NINE) {
			
			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 7;
				ButtonMessage.cell_x = 2 + (3 * subGridy);
				ButtonMessage.cell_y = 0 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_NINE);		
		}

		if ((uxBits & BUT_TEN) == BUT_TEN) {

			if(s4353737_QueueButtonPress != NULL) {			
				
				ButtonMessage.button = 8;
				ButtonMessage.cell_x = 2 + (3 * subGridy);
				ButtonMessage.cell_y = 1 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_TEN);
		}

		if ((uxBits & BUT_ELEVEN) == BUT_ELEVEN) {

			if(s4353737_QueueButtonPress != NULL) {			
				
				ButtonMessage.button = 9;
				ButtonMessage.cell_x = 2 + (3 * subGridy);
				ButtonMessage.cell_y = 2 + (3 * subGridx);
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_ELEVEN);
		}

		if ((uxBits & BUT_TWELEVE) == BUT_TWELEVE) {
			
			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 12;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_TWELEVE);		
		}

		if ((uxBits & BUT_THIRTEEN) == BUT_THIRTEEN) {
			
			if(s4353737_QueueButtonPress != NULL) {
				
				subGridx++;

				if(subGridx == 5) {
					subGridx = 0;
				}

				ButtonMessage.button = 13;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
					
                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_THIRTEEN);
		}

		if ((uxBits & BUT_FOURTEEN) == BUT_FOURTEEN) {
			
			if(s4353737_QueueButtonPress != NULL) {
				
				subGridy++;

				if(subGridy == 5) {
					subGridy = 0;
				}

				ButtonMessage.button = 14;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_FOURTEEN);
		}

		if ((uxBits & BUT_FIFTEEN) == BUT_FIFTEEN) {

			if(s4353737_QueueButtonPress != NULL) {	
				
				ButtonMessage.button = 15;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	
					portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_FIFTEEN);
		}

		if ((uxBits & BUT_SIXTEEN) == BUT_SIXTEEN) {

			if(s4353737_QueueButtonPress != NULL) {
				
				ButtonMessage.button = 16;
				ButtonMessage.cell_x = 0;
				ButtonMessage.cell_y = 0;
            	
				if(xQueueSendToFront(s4353737_QueueButtonPress, (void*) &ButtonMessage, (portTickType) 10) != pdPASS) {
                	portENTER_CRITICAL();
                	debug_printf("Failed to post the message, after 10 ticks.\n\r");
                	portEXIT_CRITICAL();
            	}
        	}

			uxBits = xEventGroupClearBits(s4353737_keypadctrl_EventGroup, BUT_SIXTEEN);	
		}

		vTaskDelay(100);
	}
}

/**
  * @brief  Sends a queue with the type of life and the sub grid to create a life
  * 		form in the simulator. Will be sent over a struct. Keypad presses
  * 		must be done in the correct order for a command to go through.
  * 		This order is specifed in the above arrays
  * @param  None
  * @retval None
  **/
void s4353737_TaskKeypadMnemonic() {

	struct MnemonicMessage MnemonicMessage;

	while(1) {

		if(s4353737_hal_keypad_read_status()) {

			/* Button 1 */
			if(keypadCount % 13 == 0) {
				
				if(KeypadValue == BUT_TWO || KeypadValue  == BUT_THREE || KeypadValue  == BUT_FIVE || 
					KeypadValue  == BUT_SEVEN || KeypadValue  == BUT_NINE || KeypadValue == BUT_THIRTEEN) {
					
					/* Clear Screen */
					if(KeypadValue == BUT_THIRTEEN) {
						
						command = 5; //clear screen command
						s4353737_QueueMnemonicKeypad  = xQueueCreate(10, sizeof(MnemonicMessage));
						keyState = 1;

					} else if(KeypadValue == BUT_FOURTEEN) {

						command = 3; //clear screen command
						s4353737_QueueMnemonicKeypad  = xQueueCreate(10, sizeof(MnemonicMessage));
						keyState = 1;
					
					} else if(KeypadValue == BUT_SIXTEEN) {

						command = 4;
						s4353737_QueueMnemonicKeypad  = xQueueCreate(10, sizeof(MnemonicMessage));
						keyState = 1;
					} else {

						buttonBuffer[keypadCount] = KeypadValue;
						keypadCount = 1;
					}
					
				} else {
					keypadCount = 0;
				}
			
			/* Button 2 */
			} else if(keypadCount % 13 == 1) {

				if(KeypadValue == BUT_TWO || KeypadValue  == BUT_SIX || KeypadValue  == BUT_SEVEN || KeypadValue  == BUT_NINE) {
					
					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 2;

				} else {
					keypadCount = 0;
				}
			
			/* Button 3 */
			} else if(keypadCount % 13 == 2) {

				if(KeypadValue == BUT_TWO || KeypadValue  == BUT_SIX || KeypadValue  == BUT_SEVEN || KeypadValue  == BUT_NINE) {

					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 3;

				} else {
					keypadCount = 0;
				}
			
			/* Button 4 */
			} else if(keypadCount % 13 == 3) {

				if(KeypadValue == BUT_SIX || KeypadValue  == BUT_NINE) { 

					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 4;

				} else {
					keypadCount = 0;
				}
			
			/* Button 5 */
			} else if(keypadCount % 13 == 4) { 

				if(KeypadValue == BUT_THREE || KeypadValue  == BUT_NINE || KeypadValue  == BUT_TEN) { 

					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 5;

				} else {
					keypadCount = 0;
				}
			
			/* Button 6 */
			} else if(keypadCount % 13 == 5) {

				if(KeypadValue == BUT_ONE || KeypadValue  == BUT_TWO || KeypadValue  == BUT_THREE || 
					KeypadValue  == BUT_FOUR || KeypadValue == BUT_FIVE || KeypadValue == BUT_SIX || 
						KeypadValue == BUT_NINE || KeypadValue == BUT_THIRTEEN) {

					buttonBuffer[keypadCount] = KeypadValue;

					if(compare_array_elements(buttonBuffer, driverDLT, 5)) {
						type = check_life_type(buttonBuffer[keypadCount]);
						keypadCount = 0;
					
					} else {
						keypadCount = 6;
					}

				} else {
					keypadCount = 0;
				}
			
			/* Button 7 */
			} else if(keypadCount % 13 == 6) {

				if(KeypadValue == BUT_ONE || KeypadValue  == BUT_TWO || KeypadValue  == BUT_THREE || 
					KeypadValue == BUT_FOUR || KeypadValue == BUT_FIVE || KeypadValue == BUT_SIX || 
						KeypadValue == BUT_NINE || KeypadValue == BUT_THIRTEEN) {

					buttonBuffer[keypadCount] = KeypadValue;

					if(compare_array_elements(buttonBuffer, createGLD, 5)) {

						store_cell_life();
						
						if(subGrid_x == 5 || subGrid_y == 5) {
							keypadCount = 0;
						
						} else {
							s4353737_QueueMnemonicKeypad  = xQueueCreate(10, sizeof(MnemonicMessage));
							keyState = 1;
							keypadCount = 0;
							command = 2;

						}
					}

					keypadCount = 7;
				} else {
					keypadCount = 0;
				}

				
			
			/* Button 8 */
			} else if(keypadCount % 13 == 7) {

				if(KeypadValue == BUT_ONE || KeypadValue  == BUT_TWO || KeypadValue  == BUT_THREE || 
					KeypadValue == BUT_FOUR || KeypadValue == BUT_SIX || 
						KeypadValue == BUT_NINE || KeypadValue == BUT_THIRTEEN) { 
					
					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 8;
					
				} else {
					keypadCount = 0;
				}

			
			/* Button 9 */
			} else if(keypadCount % 13 == 8) { 

				if(KeypadValue  == BUT_ONE || KeypadValue  == BUT_TWO|| 
					KeypadValue == BUT_THREE || KeypadValue == BUT_THIRTEEN) {
					
					buttonBuffer[keypadCount] = KeypadValue;

					if(compare_array_elements(buttonBuffer, driveCRE, 8)) {
						keypadCount = 0;		
					
					} else {
						keypadCount = 9;
					}
				
				} else {
					keypadCount = 0;
				}
			
			/* Button 10 */
			} else if(keypadCount % 13 == 9) {

				if(KeypadValue  == BUT_ONE || KeypadValue  == BUT_TWO || KeypadValue  == BUT_THREE|| 
					KeypadValue  == BUT_FOUR || KeypadValue  == BUT_FIVE) {

					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 10;

				} else {
					keypadCount = 0;
				}

			/* Button 11 */
			} else if(keypadCount % 13 == 10) {

				if(KeypadValue  == BUT_ONE || KeypadValue  == BUT_TWO || 
					KeypadValue  == BUT_THREE || KeypadValue == BUT_THIRTEEN) {
					
					buttonBuffer[keypadCount] = KeypadValue;

					if(compare_array_elements(buttonBuffer, createSTL, 8)) {
					
						store_cell_life();
							
						if(subGrid_x != 5 || subGrid_y != 5 || type != 3) {
							
							s4353737_QueueMnemonicKeypad  = xQueueCreate(10, sizeof(MnemonicMessage));
							keyState = 1;
							command = 0;
						}	
					
					} else {
						keypadCount = 11;
					}

				} else {
					keypadCount = 0;
				}
			
			/* Button 12 */
			} else if(keypadCount % 13 == 11) {

				if(KeypadValue  == BUT_ONE || KeypadValue  == BUT_TWO || KeypadValue  == BUT_THREE|| 
					KeypadValue  == BUT_FOUR || KeypadValue  == BUT_FIVE) {

					buttonBuffer[keypadCount] = KeypadValue;
					keypadCount = 12;

				} else {
					keypadCount = 0;
				}
			
			
			/* Button 13 */
			} else if(keypadCount % 13 == 12) {

				if(KeypadValue  == BUT_ONE || KeypadValue  == BUT_TWO || KeypadValue  == BUT_THREE|| 
					KeypadValue  == BUT_FOUR || KeypadValue  == BUT_FIVE) {

					buttonBuffer[keypadCount] = KeypadValue;
					
					if(compare_array_elements(buttonBuffer, createOSC, 10)) {
						store_cell_life();
						
						if(subGrid_x != 5 || subGrid_y != 5 || type != 3) {
							
							s4353737_QueueMnemonicKeypad  = xQueueCreate(10, sizeof(MnemonicMessage));
							keyState = 1;
							command = 1;
						}		
					}

				} else {
					keypadCount = 0;
				}
			}
		}

		if(s4353737_QueueMnemonicKeypad != NULL && keyState == 1) {
		
			MnemonicMessage.command 	= command;
    		MnemonicMessage.type 		= type;
			MnemonicMessage.subGrid_x 	= subGrid_x;
			MnemonicMessage.subGrid_y 	= subGrid_y;
            	
			if(xQueueSendToFront(s4353737_QueueMnemonicKeypad, (void*) &MnemonicMessage, (portTickType) 10) != pdPASS) {
                	
				portENTER_CRITICAL();
                debug_printf("Failed to post the message, after 10 ticks.\n\r");
                portEXIT_CRITICAL();
            }
        }
		keyState = 0;
		s4353737_hal_keypad_fsmprocessing();
		vTaskDelay(100);
	}
}

/**
 * @brief When a correct button combination has been matched to a
 * 		  life form array, store the button presses to be sent in the queue
 * @param None
 * @retval None
 */ 
void store_cell_life() {
	type = check_life_type(buttonBuffer[keypadCount - 2]);
	subGrid_x = check_xy_coordinate(buttonBuffer[keypadCount - 1]);
	subGrid_y = check_xy_coordinate(buttonBuffer[keypadCount]);
	keypadCount = 0;
}

/**
 * @brief Compares array elements of two array up to a given size. If the array 
 * 		  elements are the same up to that size, will return true, else false.
 * @param a[] - Array to be compared.
 * @param b[] - Array to be compared.
 * @param size - Compare both arrays up to this value
 * @retval Returns 1 if true else 0 if false.
 */
int compare_array_elements(u_int16_t a[], u_int16_t b[], int size) {
	
	for(int i = 0; i < size; i++) {

		if(a[i] != b[i]) {
			return 0;
		}
	}

	return 1;
}

/**
 * @brief Check the coordinates of one either x or y from the button. This function
 * 		  will convert the x or y coordinates from the bit shifted value to the integer
 * 		  value to be processed by the simulator.
 * @param xy - The x or y coordinate to be converted to an integer.
 * @retval The bit shifted x or y coordinate. It will be an integer from 0 - 4.
 */
int check_xy_coordinate(uint16_t xy) {
	
	if(xy == 1 << 12) {
		return 0;

	} else if(xy == 1 << 0) {
		return 1;

	} else if(xy == 1 << 1) {
		return 2;
	
	} else if(xy == 1 << 2) {
		return 3;
	
	} else if(xy == 1 << 4) {
		return 4;
	
	} else {
		return 5;
	}
}

/**
 * @brief Check the type of life given by the user from the keypad. The type
 * 		  will be bit shifted and converted to an int to be processed by the 
 * 	      simulator.
 * @param xy - The type to be converted to an integer.
 * @retval The bit shifted type. It will be an integer from 0 - 3.
 */
int check_life_type(uint16_t type) {
	
	if(type == 1 << 12) {
		return 0;

	} else if(type == 1 << 0) {
		return 1;

	} else if(type == 1 << 1) {
		return 2;
	
	} else {
		return 3;
	} 
}
 