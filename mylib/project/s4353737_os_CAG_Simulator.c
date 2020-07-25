 /** 
  ******************************************************************************
  * @file 		mylib/project/s4353737_os_CAG_Simulator.c
  * @author 	George Todorovic - 43537370
  * @date 		01062020
  * @brief 		Runs the Game of Life alogorithm for cell movement. Sends
  *             the grid to the display to be printed and creates cells when
  *             new commands from the keypad have been recognised.
  * REFERENCE: 	csse3010_project.pdf
  ******************************************************************************
  * EXTERNAL FUNCTIONS 
  ******************************************************************************
  * keypad_gpio_init(); - Initialise the keypad
  * s4353737_hal_pb_on_init(); - Initialise push buttons A0 and A3
  ******************************************************************************
  */

/* Includes ----------------------------------------------------------------- */
#include "s4353737_os_CAG_Simulator.h"
/* Macros ------------------------------------------------------------------- */
#define PAUSE_UPDATE     0
#define START_UPDATE     1
/* Variables ---------------------------------------------------------------- */
int state = START_UPDATE;
int grid[GRID_WIDTH][GRID_HEIGHT];
int tempGrid[GRID_WIDTH][GRID_HEIGHT];
char* cell_colour_palatte[] = {CELL_BLACK, CELL_RED, CELL_GREEN, CELL_YELLOW, CELL_BLUE, CELL_MAGENTA, CELL_CYAN, CELL_WHITE};
/* Prototypes ------------------------------------------------ */
void update_grid();
void set_cells_dead_grid();
void draw_glider(int xSub, int ySub);
void draw_oscillator(int xSub, int ySub, int type);
void draw_still_life(int xSub, int ySub, int type);

/**
 * @brief Initalise the grid at the start of the Game of Life. Grid will
 *        be initialised as such as 15x15 integer array with all values
 *        set to 0. Will also be used to reset the grid on keypad command.
 * @param None
 * @retval None
 */       
void set_cells_dead_grid() {
    
    for(int x = 0; x < GRID_WIDTH; x++) {
        
        for(int y = 0; y < GRID_HEIGHT; y++) { 
            /* set all cells to dead */  
            grid[x][y] = DEAD_CELL;
        }
    }
}

/**
 * @brief Task to receive a queue from the CAG keypad when in grid mode.
 * @param None
 * @retval None
 */
void s4353737_TaskReadKeypadGrid() {

    struct ButtonMessage ReadButton;

    s4353737_QueueButtonPress = xQueueCreate(10, sizeof(ReadButton));

    while(1) {

		if(s4353737_QueueButtonPress != NULL) {
            
            if(xQueueReceive(s4353737_QueueButtonPress, &ReadButton, 10)) {
                
                if(ReadButton.button >= 1 && ReadButton.button <= 9) {
                    grid[ReadButton.cell_x][ReadButton.cell_y] = ALIVE_CELL;
                
                } else if(ReadButton.button == 10) {
                    state = START_UPDATE;
                
                } else if(ReadButton.button == 11) {
                    state = PAUSE_UPDATE;
                
                } else if(ReadButton.button == 12) {
                    set_cells_dead_grid();
                }
            }
        }
        vTaskDelay(100);
    }
}

/**
 * @brief Task to receive a queue from the CAG keypad when in mnemonic mode.
 * @param None
 * @retval None
 */
void s4353737_TaskReadKeypadMnemonic() {

    struct MnemonicMessage MnemonicMessage;

    s4353737_QueueMnemonicKeypad = xQueueCreate(10, sizeof(MnemonicMessage));

    while(1) {

		if(s4353737_QueueMnemonicKeypad != NULL) {
            
            if(xQueueReceive(s4353737_QueueMnemonicKeypad, &MnemonicMessage, 10)) {
                
                if(MnemonicMessage.command == 0) {
                    draw_still_life(MnemonicMessage.subGrid_x, MnemonicMessage.subGrid_y, MnemonicMessage.type);
                
                } else if(MnemonicMessage.command == 1) {
                    draw_oscillator(MnemonicMessage.subGrid_x, MnemonicMessage.subGrid_y, MnemonicMessage.type);

                } else if(MnemonicMessage.command == 2) {
                    draw_glider(MnemonicMessage.subGrid_x, MnemonicMessage.subGrid_y);

                } else if(MnemonicMessage.command == 3) {
                    state = START_UPDATE;

                } else if(MnemonicMessage.command == 4) {
                    state = PAUSE_UPDATE;
                
                } else if(MnemonicMessage.command == 5) {
                    set_cells_dead_grid();
                }
            }
        }
        vTaskDelay(100);
    }
}

/**
 * @brief Give the grid array to the display task. This task will call update
 *        grid to process cell movement as according to Game of Life rules.
 * @param None
 * @retval None
 */
void s4353737_TaskGiveGridToDisplay() {

    int ledToggle = 0;

    struct GridMessage GridMessage;

    s4353737_QueueSendGrid = xQueueCreate(10, sizeof(GridMessage));

    while(1) {

        if(s4353737_QueueSendGrid != NULL) {
            
            if(state == START_UPDATE) {
                update_grid();
            }
            /* Copy Grid Struct */

            memcpy(GridMessage.grid, grid, sizeof(int) * GRID_WIDTH * GRID_HEIGHT);

            if(ledToggle == 0) {

                s4353737_hal_lta1000g_write(upper | lower | 512);
                ledToggle = 1;

            } else if(ledToggle == 1) {

                s4353737_hal_lta1000g_write(upper | lower);
                ledToggle = 0;
            }

            if(xQueueSendToFront(s4353737_QueueSendGrid, (void*) &GridMessage, (portTickType) 10) != pdPASS) {

            }
        }

        vTaskDelay(2000);
    }
}

/**
 * @brief Copy the grid into the temp grid
 * @param None
 * @retval None
 */
void copy_grid_to_temp() {
    for(int x = 0; x < GRID_WIDTH; x++) {

        for(int y = 0; y < GRID_HEIGHT; y++) {

            tempGrid[x][y] = grid[x][y];
        }
    }
}

/**
 * @brief Update the grid to apply rules of Game of Life. Rules are followed as set
 *        in the criteria. The grid will update before a queue is sent to the display
 *        task.
 * @param None
 * @retval None
 */
void update_grid() {

    copy_grid_to_temp();

    for(int x = 0; x < GRID_WIDTH; x++) {

        for(int y = 0; y < GRID_HEIGHT; y++) {

            int count = 0;

            for(int xx = x - 1; xx <= x + 1; xx++) {

                for(int yy = y - 1; yy <= y + 1; yy++) {

                    if((xx >= 0) && (xx < GRID_WIDTH) && (yy >= 0) && (yy < GRID_HEIGHT)) {

                        if(!((xx == x) && (yy == y))) {
                            
                            /* If near a cell with neighbours add to count */
                            if(tempGrid[xx][yy] == ALIVE_CELL) {
                                count++;
                            }
                        }
                    }
                }
            }

            /* Apply Conway Game of Life rules to grid */
            if(tempGrid[x][y] == ALIVE_CELL) {

                if((count < 2 || count > 3)) {
                    grid[x][y] = DEAD_CELL;
                }
            
            } else {

                if(count == 3) {
                    grid[x][y] = ALIVE_CELL;
                }
            }
        }
    }
} 

/**
 * @brief Draw a glider to the designated sub grid
 * @param xSub - The x sub grid value
 * @param ySub - the y sub grid value
 * @retval None
 */
void draw_glider(int xSub, int ySub) {
    grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
    grid[1 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
    grid[2 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
    grid[2 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
    grid[2 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
}

/**
 * @brief Draw a oscillator life form at sub grid x, y. Oscillator life forms 
 *        can be blinkers (0), toad(1) and beacon(2). Depending on the queue message
 *        received from the keypad will determine the type of life form.
 * @param xSub - The x sub grid value
 * @param ySub - The y sub grid value
 * @retval None
 */
void draw_oscillator(int xSub, int ySub, int type) {
    
    /* Draw Blinker */
    if(type == 0) {
        grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[2 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
    
    /* Draw Toad */
    } else if(type == 1) {
        grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[0 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
        grid[0 + (xSub * 3)][3 + (ySub * 3)] = ALIVE_CELL;

        grid[1 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
    
    /* Draw Beacon */
    } else if(type == 2) {
        grid[0 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;

        grid[2 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
        grid[2 + (xSub * 3)][3 + (ySub * 3)] = ALIVE_CELL;
        grid[3 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
        grid[3 + (xSub * 3)][3 + (ySub * 3)] = ALIVE_CELL;
    }
}

/**
 * @brief Draw a still life form at sub grid x, y. Still life forms 
 *        can be block (0), behive(1) and loaf(2). Depending on the queue message
 *        received from the keypad will determine the type of life form.
 * @param xSub - The x sub grid value
 * @param ySub - The y sub grid value
 * @retval None
 */
void draw_still_life(int xSub, int ySub, int type) {

    /* Block life form */
    if(type == 0) {
        grid[0 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;

    /*Bee-hive life form */
    } else if(type == 1) {
        grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[2 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;

        grid[0 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][3 + (ySub * 3)] = ALIVE_CELL;
        grid[2 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;

    /* Loaf life form */
    } else if(type == 2) {
        grid[1 + (xSub * 3)][0 + (ySub * 3)] = ALIVE_CELL;
        grid[2 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[3 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;

        grid[0 + (xSub * 3)][1 + (ySub * 3)] = ALIVE_CELL;
        grid[0 + (xSub * 3)][2 + (ySub * 3)] = ALIVE_CELL;
        grid[1 + (xSub * 3)][3 + (ySub * 3)] = ALIVE_CELL;
        grid[2 + (xSub * 3)][3 + (ySub * 3)] = ALIVE_CELL;
    }
}

/**
 * @brief Task to switch the mode of the keypad from grid mode to
 *        mnemonic mode. While in grid mode the red led will be on.
 *        In grid mode the blue led will be turned on.
 * @param None
 * @retval None
 */
void s4353737_TaskSwitchMode() {

    currentMode = 0;
    
    s4353737LEDSemaphore = xSemaphoreCreateBinary();

    if(currentMode == GRID_MODE) {
        BRD_LEDRedOn();
    }

    while(1) {
        /* Delay the task for 50 ms to save CPU time. */
        vTaskDelay(50);
        
        /* Check if the semaphore exists. */
        if(s4353737LEDSemaphore != NULL) {
        
            if(xSemaphoreTake(s4353737LEDSemaphore, 10) == pdTRUE) {    
                
                if(currentMode == GRID_MODE) {
                  
                    BRD_LEDRedOff();
                    BRD_LEDBlueOn();
                    currentMode = MNEMONIC_MODE;
                    vTaskResume(KeypadMnemonic);
                    vTaskResume(MnemonicTask);
                    vTaskSuspend(KeypadGrid);
                    vTaskSuspend(GridTakeTask);
                    vTaskSuspend(GridGiveTask);

                } else {
                    BRD_LEDBlueOff();
                    BRD_LEDRedOn();
                    currentMode = GRID_MODE;
                    vTaskResume(KeypadGrid);
                    vTaskResume(GridTakeTask);
                    vTaskResume(GridGiveTask);
                    vTaskSuspend(KeypadMnemonic);
                    vTaskSuspend(MnemonicTask);
                }
            }
        }
    }
}

/**
 * @brief Joystick os task. Receives semaphores when joystick is z
 *        button is triggered.
 * @param None
 * @retval None
 */
void s4353737_TaskJoystickZButton() {
    
    s4353737_SemaphoreZButton = xSemaphoreCreateBinary();

    for(;;) {
        
        /* Delay the task for 50 ms to save CPU time. */
        
        /* Check if the semaphore exists. */
        if(s4353737_SemaphoreZButton != NULL) {
            
            if(xSemaphoreTake(s4353737_SemaphoreZButton, 10) == pdTRUE) {
                set_cells_dead_grid();
            }
        }
        
        vTaskDelay(50);
    }
}

/**
 * @brief Create tasks for CAG simulator. Will initialise the grid.
 * @param None
 * @retval None
 */
extern void s4353737_os_CAG_simulator_init() {

    set_cells_dead_grid();
    keypad_gpio_init();
    s4353737_hal_pb_on_init();

    xTaskCreate((void*) &s4353737_TaskGiveGridToDisplay, (const signed char*) "GiveToDisplay", 
        S4353737_OS_READ_KEYPAD_GRID_STACK_SIZE, NULL, S4353737_OS_READ_KEYPAD_GRID_PRIORITY, NULL);

    xTaskCreate((void*) &s4353737_TaskReadKeypadGrid, (const signed char*) "ReadKeypad", 
        S4353737_OS_READ_KEYPAD_GRID_STACK_SIZE, NULL, S4353737_OS_READ_KEYPAD_GRID_PRIORITY, &KeypadGrid);

    xTaskCreate((void*) &s4353737_TaskReadKeypadMnemonic, (const signed char*) "ReadKeypad", 
        S4353737_OS_READ_KEYPAD_GRID_STACK_SIZE, NULL, S4353737_OS_READ_KEYPAD_GRID_PRIORITY, &KeypadMnemonic);

    xTaskCreate((void *) &s4353737_TaskSwitchMode, (const signed char *) "TAKE", 
        S4353737_OS_LED_STACK_SIZE, NULL, S4353737_OS_LED_PRIORITY, NULL);

    xTaskCreate((void*) &s4353737_TaskJoystickZButton, (const signed char *) "ZBUTTON", 
        S4353737_OS_JOYSTICK_BUTTON_STACK_SIZE, NULL, S4353737_OS_JOYSTICK_BUTTON_PRIORITY, NULL);

    vTaskSuspend(KeypadMnemonic);
    vTaskSuspend(MnemonicTask);
}
