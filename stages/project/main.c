 /** 
  ******************************************************************************
  * @file 		stages/project/main.c
  * @author 	George Todorovic - 43537370
  * @date 		01062020
  * @brief 		main.c for CSSE3010 Project Embedded Display Controller for 
  * 			Cellular Automation Graphics
  * REFERENCE: 	csse3010_project.pdf
  ******************************************************************************
  * EXTERNAL FUNCTIONS 
  ******************************************************************************
  * s4353737_os_joystick_init() - 	Initialise joystick drivers and tasks
  * s4353737_os_lta1000g_init() - 	Initialise LTA1000G drivers and tasks
  *	s4353737_os_display_grid_init() - Initialise CAG grid display and tasks
  *	s4353737_os_CAG_simulator_init() - Initialise CAG simulator, keypad and tasks
  *	s4353737_os_keypad_grid_init() - Initialise keypad grid tasks
  *	s4353737_os_keypad_mnemonic_init() - Initialise keypad mnemonic tasks
  ******************************************************************************
  */

/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_CAG_Display.h"
#include "s4353737_os_joystick.h"
/* Prototype Functions ------------------------------------------------------ */
void Hardware_init(void);

int main(void) {
	
	Hardware_init();

	/* Start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
    vTaskStartScheduler();

    return 0;
}

void Hardware_init(void) {
	
	portDISABLE_INTERRUPTS();
    
	BRD_init();
  	BRD_LEDInit();
	s4353737_os_joystick_init();
	s4353737_os_lta1000g_init();
	s4353737_os_display_grid_init();
	s4353737_os_keypad_grid_init();
	s4353737_os_keypad_mnemonic_init();
	s4353737_os_CAG_simulator_init();

  	portENABLE_INTERRUPTS();
}
