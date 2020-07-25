 /** 
 *******************************************************************************
 * @file        mylib/project/s4353737_os_CAG_Simulator.h
 * @author      George Todorovic - 43537370
 * @date        01062020
 * @brief       CAG Simulator header file.
 * REFERENCE:   csse3010_project.pdf 
 *******************************************************************************
 */

#ifndef S4353737_OS_CAG_SIMULATOR_H
#define S4353737_OS_CAG_SIMULATOR_H

/*Includes ------------------------------------------------------------------ */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_os_keypad.h"
#include "s4353737_os_pb.h"
#include "string.h"
#include "s4353737_os_CAG_keypad_grid.h"
#include "s4353737_os_CAG_keypad_mnemonic.h"
#include "s4353737_os_lta1000g.h"
/*FreeRTOS Includes --------------------------------------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/* Task Stack Allocation ---------------------------------------------------- */
#define S4353737_OS_GIVE_GRID_STACK_SIZE        (configMINIMAL_STACK_SIZE * 5)
#define S4353737_OS_READ_KEYPAD_GRID_STACK_SIZE (configMINIMAL_STACK_SIZE * 5)
/* Task Priorities ---------------------------------------------------------- */
#define S4353737_OS_GIVE_GRID_PRIORITY          (tskIDLE_PRIORITY + 3)
#define S4353737_OS_READ_KEYPAD_GRID_PRIORITY   (tskIDLE_PRIORITY + 2)
/* Defines ------------------------------------------------------------------ */
#define SCREEN_CLEAR()  debug_printf("\e[2J")
#define SCREEN_HOME()   debug_printf("\e[H")

#define FG_BLACK 	30
#define FG_RED		31
#define FG_GREEN	32
#define FG_YELLOW	33
#define FG_BLUE		34
#define FG_MAGENTA	35
#define FG_CYAN		36
#define FG_WHITE	37
#define BG_BLACK	40
#define BG_RED		41
#define BG_GREEN	42
#define BG_YELLOW	43
#define BG_BLUE		44
#define BG_MAGENTA	45
#define BG_CYAN		46
#define BG_WHITE	47

#define CELL_BLACK 		"\e[7;30;40m"
#define CELL_RED		"\e[7;31;41m"
#define CELL_GREEN		"\e[7;32;42m"
#define CELL_YELLOW		"\e[7;33;43m"
#define CELL_BLUE		"\e[7;34;44m"
#define CELL_MAGENTA	"\e[7;35;45m"
#define CELL_CYAN		"\e[7;36;46m"
#define CELL_WHITE 		"\e[7;37;47m"

#define GRID_WIDTH      15
#define GRID_HEIGHT     15
#define ALIVE_CELL      1
#define DEAD_CELL       0
/* Struct ------------------------------------------------------------------- */
struct GridMessage {
    int grid[GRID_WIDTH][GRID_HEIGHT];
};
/* Variables ---------------------------------------------------------------- */
QueueHandle_t s4353737_QueueSendGrid;
TaskHandle_t KeypadGrid;
TaskHandle_t KeypadMnemonic;

extern void s4353737_os_CAG_simulator_init();



#endif
