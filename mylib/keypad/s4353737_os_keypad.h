/** 
 *******************************************************************************
 * @file        mylib/keypad/s4353737_os_keypad.h
 * @author      George Todorovic - 43537370
 * @date        02062020
 * @brief       keypad os header files
 * REFERENCE:   csse3010_project.pdf 
 *******************************************************************************
 * EXTERNAL FUNCTIONS 
 *******************************************************************************
 * s4353737SemaphoreLTA1000g - Semphore for LTA1000g to shift
 *******************************************************************************
*/

#ifndef S4353737_OS_KEYPAD_H
#define S4353737_OS_KEYPAD_H

/*Includes ------------------------------------------------------------------ */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "string.h"
#include "s4353737_hal_keypad.h"
/*FreeRTOS Includes --------------------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/* Private macros ----------------------------------------------------------- */
#define GRID_MODE       0
#define MNEMONIC        1

#define BUT_ONE			1 << 0
#define BUT_TWO			1 << 1
#define BUT_THREE		1 << 2
#define BUT_FOUR		1 << 3
#define BUT_FIVE		1 << 4
#define BUT_SIX 		1 << 5
#define BUT_SEVEN		1 << 6
#define BUT_EIGHT		1 << 7
#define BUT_NINE		1 << 8
#define BUT_TEN	    	1 << 9
#define BUT_ELEVEN		1 << 10
#define BUT_TWELEVE		1 << 11
#define BUT_THIRTEEN	1 << 12
#define BUT_FOURTEEN	1 << 13
#define BUT_FIFTEEN 	1 << 14
#define BUT_SIXTEEN		1 << 15
#define KEYPADCTRL_EVNT		BUT_ONE | BUT_TWO | BUT_THREE | BUT_FOUR | BUT_FIVE | BUT_SIX | BUT_SEVEN | BUT_EIGHT | BUT_NINE | BUT_TEN | BUT_ELEVEN | BUT_TWELEVE | BUT_THIRTEEN | BUT_FOURTEEN | BUT_FIFTEEN | BUT_SIXTEEN
/* Variables ---------------------------------------------------------------- */
EventGroupHandle_t  s4353737_keypadctrl_EventGroup;
QueueHandle_t       s4353737_QueueButtonPress;
QueueHandle_t       s4353737_QueueMnemonicKeypad;
TaskHandle_t        MnemonicTask;
TaskHandle_t        MnemonicTask;
TaskHandle_t        GridGiveTask;
TaskHandle_t        GridTakeTask;
/* Task Stack Allocation ---------------------------------------------------- */
#define S4353737_OS_GIVE_KEYPAD_STACK_SIZE  (configMINIMAL_STACK_SIZE * 2)
#define S4353737_OS_TAKE_KEYPAD_STACK_SIZE  (configMINIMAL_STACK_SIZE * 2)
/* Task Priorities ---------------------------------------------------------- */
#define S4353737_OS_GIVE_KEYPAD_PRIORITY    (tskIDLE_PRIORITY + 2)
#define S4353737_OS_TAKE_KEYPAD_PRIORITY    (tskIDLE_PRIORITY + 2)
/* Private Struct ----------------------------------------------------------- */
struct ButtonMessage {
    int button;
	int mode;
    int cell_x;
    int cell_y;
};

struct MnemonicMessage {
    int command;
	int type;
    int subGrid_x;
    int subGrid_y;
};

void s4353737_TaskKeypadButtonPress();
void s4353737_TaskKeypadGiveButtonQueue();
void s4353737_TaskKeypadMnemonic();

#endif
