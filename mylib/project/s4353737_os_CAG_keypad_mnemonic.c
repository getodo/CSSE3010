/** 
 *******************************************************************************
 * @file      mylib/project/s4353737_os_CAG_keypad_mnemonic.c
 * @author    George Todorovic - 43537370
 * @date      01062020
 * @brief     Initialise the CAG keypad mnemonic tasks.
 * REFERENCE: csse3010_project.pdf 
 *******************************************************************************
 */
/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_CAG_keypad_mnemonic.h"

/**
 * @brief Initialise the keypad and required keypad GPIO pins
 * @param None
 * @retval None
 */
extern void s4353737_os_keypad_mnemonic_init() {
    
    xTaskCreate((void *) &s4353737_TaskKeypadMnemonic, (const signed char *) "GIVE", 
		S4353737_OS_GIVE_KEYPAD_STACK_SIZE, NULL, S4353737_OS_GIVE_KEYPAD_PRIORITY, &MnemonicTask);
}

 