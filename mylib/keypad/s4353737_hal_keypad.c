 /** 
 *******************************************************************************
 * @file      mylib/keypad/s4353737_hal_keypad.c
 * @author    George Todorovic - 43537370
 * @date      01062020
 * @brief     Driver files for keypad. FSM used to process key presss. This file
 *            initialises the GPIO pins required for keypad functionality.
 * REFERENCE: csse3010_mylib_hal_keypad.pdf 
 *******************************************************************************
*/
/* Includes -------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_keypad.h"
#include "s4353737_hal_lta1000g.h"
#include "s4353737_os_pb.h"
/*Defines ---------------------------------------------------- */
#define PRESSED         1
#define NOT_PRESSED     0
#define INIT_STATE      0
#define COL1_STATE      1
#define COL2_STATE      2
#define COL3_STATE      3
#define COL4_STATE      4
#define ROWSCAN_STATE   5
#define DEINIT_STATE    6
#define keypad_col1()     keypad_writecol(COL1_STATE)
#define keypad_col2()     keypad_writecol(COL2_STATE)
#define keypad_col3()     keypad_writecol(COL3_STATE)
#define keypad_col4()     keypad_writecol(COL4_STATE)
/* Prototypes ------------------------------------------------ */
void keypad_gpio_init();
void change_state();
u_int16_t keypad_readrow();
/*Variables -------------------------------------------------- */
u_int16_t KeypadValue;
int KeypadFsmCurrentstate = INIT_STATE;
int KeypadStatus = NOT_PRESSED;
unsigned short lower = 0;
unsigned short upper = 0;

/**
 * @brief Initialise the GPIO pins and ports for the keypad
 * @param None
 * @retval None
 */
void s4353737_hal_keypad_init() {
    keypad_gpio_init();
}

/**
 * @brief Deinitialise GPIO pins and ports of the keypad
 * @param None
 * @retval None
 */
void s4357337_hal_keypad_deinit() {

    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_ROW1PINPORT, S4353737_HAL_KEYPAD_ROW1PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_ROW2PINPORT, S4353737_HAL_KEYPAD_ROW2PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_ROW3PINPORT, S4353737_HAL_KEYPAD_ROW3PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_ROW4PINPORT, S4353737_HAL_KEYPAD_ROW4PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN);
    HAL_GPIO_DeInit(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN);
}

/**
 * @brief State machine for keypad key processing. State will
 *        switch on 50ms timer from COLX->ROWSCAN->COLX->ROWSCAN
 *        start in INIT_STATE
 * @param None
 * @retval None
 */
void s4353737_hal_keypad_fsmprocessing() {
    switch (KeypadFsmCurrentstate) {

        case INIT_STATE:

            s4353737_hal_keypad_init();
            KeypadFsmCurrentstate = COL1_STATE;
            return;

        case COL1_STATE:

            KeypadStatus = NOT_PRESSED;
            keypad_col1();
            return;
        
        case COL2_STATE:

            KeypadStatus = NOT_PRESSED;
            keypad_col2();
            return;

        case COL3_STATE:

            KeypadStatus = NOT_PRESSED;
            keypad_col3();
            return;

        case COL4_STATE:

            KeypadStatus = NOT_PRESSED;
            keypad_col4();
            return;

        case ROWSCAN_STATE:
            keypad_readrow();
            change_state();
            return;
    }
}

/**
 * @brief Initialise GPIO pins for rows and columns
 * @param None
 * @retval None
 */
void keypad_gpio_init() {

    GPIO_InitTypeDef GPIO_InitStructure;

    S4353737_HAL_KEYPAD_COL1PINCLK;
    S4353737_HAL_KEYPAD_COL2PINCLK;
    S4353737_HAL_KEYPAD_COL3PINCLK;
    S4353737_HAL_KEYPAD_COL4PINCLK;
    S4353737_HAL_KEYPAD_ROW1PINCLK;
    S4353737_HAL_KEYPAD_ROW2PINCLK;
    S4353737_HAL_KEYPAD_ROW3PINCLK;
    S4353737_HAL_KEYPAD_ROW4PINCLK;

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_ROW1PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull     = GPIO_PULLUP;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FAST;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_ROW1PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_ROW2PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull     = GPIO_PULLUP;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FAST;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_ROW2PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_ROW3PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull     = GPIO_PULLUP;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FAST;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_ROW3PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_ROW4PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull     = GPIO_PULLUP;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FAST;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_ROW4PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_COL1PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_COL1PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_COL2PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_COL2PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_COL3PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_COL3PINPORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = S4353737_HAL_KEYPAD_COL4PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(S4353737_HAL_KEYPAD_COL4PINPORT, &GPIO_InitStructure);
    
    s4353737_hal_lta1000g_write(upper | lower);
}

/**
 * @brief Depending on current state, set 1 column pin to 0 and set others to 1
 *        to read which button has been pressed. 
 * @param Colval - the column to set to 0
 * @retval None
 */
void keypad_writecol(int colval) {

    if(colval == COL1_STATE) {

        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN, 0);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN, 1);
    }
    if(colval == COL2_STATE) {

        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN, 0);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN, 1);
    }
    if(colval == COL3_STATE) {

        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN, 0);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN, 1);
    }
    if(colval == COL4_STATE) {

        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN, 1);
        HAL_GPIO_WritePin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN, 0);
    }
    KeypadFsmCurrentstate = ROWSCAN_STATE;
}

/**
 * @brief Read the rows of the keypad. If a row has a button pressed down in it. Read the 
 *        value of that row. Depending on what column state is currently zero, save the value
 *        of the key pressed to KeypadValue.
 * @param None
 * @retval lowRow - the hex value of the row with a button pressed down.
 */
uint16_t keypad_readrow() {
    
    uint8_t lowRow;
    if(!(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_ROW1PINPORT, S4353737_HAL_KEYPAD_ROW1PIN))) {
        BRD_LEDToggle(BRD_GREEN_LEDMASK);
        lowRow = 0x0E;
        KeypadStatus = PRESSED;
        if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN) == 0) {

            KeypadValue = 1 << 0;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN) == 0) {

            KeypadValue = 1 << 1;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN) == 0) {

            KeypadValue = 1 << 2;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN) == 0) {

            KeypadValue = 1 << 3;
        }
    }
    if(!(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_ROW2PINPORT, S4353737_HAL_KEYPAD_ROW2PIN))) {
        BRD_LEDToggle(BRD_GREEN_LEDMASK);
        lowRow = 0x0D;
        KeypadStatus = PRESSED;
        if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN) == 0) {

            KeypadValue = 1 << 4;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN) == 0) {

            KeypadValue = 1 << 5;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN) == 0) {

            KeypadValue = 1 << 6;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN) == 0) {

            KeypadValue = 1 << 7;
        }
    }
    if(!(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_ROW3PINPORT, S4353737_HAL_KEYPAD_ROW3PIN))) {
        BRD_LEDToggle(BRD_GREEN_LEDMASK);
        lowRow = 0x0B;
        KeypadStatus = PRESSED;
        if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN) == 0) {

            KeypadValue = 1 << 8;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN) == 0) {

            KeypadValue = 1 << 9;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN) == 0) {

            KeypadValue = 1 << 10;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN) == 0) {

            KeypadValue = 1 << 11;
        }
    }
    if(!(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_ROW4PINPORT, S4353737_HAL_KEYPAD_ROW4PIN))) {
        BRD_LEDToggle(BRD_GREEN_LEDMASK);
        lowRow = 0x07;
        KeypadStatus = PRESSED;
        if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN) == 0) {
            KeypadValue = 1 << 12;
            
            if(currentMode == 0) {
                lower++;
                
                if(lower == 5) {
                    lower = 0;
                }
                s4353737_hal_lta1000g_write(upper | lower);
            }
            
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN) == 0) {
            KeypadValue = 1 << 13;

            if(currentMode == 0) {
                upper = upper + 8;
                
                if(upper == 40) {
                    upper = 0;
                }
                s4353737_hal_lta1000g_write(upper | lower);
            }
            
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN) == 0) {
            KeypadValue = 1 << 14;
        } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN) == 0) {

            KeypadValue = 1 << 15;
        }
    }
    return lowRow;
}

/**
 * @brief Return the current status of the keypad whether or not a key
 *        has been pressed.
 * @param None
 * @retval KeypadStatus - 1 if a key has been pressed, else 0.
 */
int s4353737_hal_keypad_read_status() {
    return KeypadStatus;
}

/**
 * @brief Return the hexadecimal value of the last stored key press.
 * @param None
 * @retval KeypadValue - the hex value of the key pressed
 */
unsigned char s4353737_keypad_read_key() {
    return KeypadValue;
}

/**
 * @brief Return the ascii value of the last stored key press.
 * @param None
 * @retval Return the ascii value of the key
 */
unsigned char s4353737_hal_keypad_read_ascii() {

    if(KeypadValue >= 0x0A) {

        return KeypadValue + '7';
    } else {

        return KeypadValue + '0';
    }
}


/**
 * @brief Helper function to processes FSM state changes. State will 
 *        switch depending on the read value of the pins.
 * @param None
 * @retval None
 */
void change_state() {

    if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL1PINPORT, S4353737_HAL_KEYPAD_COL1PIN) == 0) {

        KeypadFsmCurrentstate = COL2_STATE;
    } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL2PINPORT, S4353737_HAL_KEYPAD_COL2PIN) == 0) {

        KeypadFsmCurrentstate = COL3_STATE;
    } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL3PINPORT, S4353737_HAL_KEYPAD_COL3PIN) == 0) {

        KeypadFsmCurrentstate = COL4_STATE;
    } else if(HAL_GPIO_ReadPin(S4353737_HAL_KEYPAD_COL4PINPORT, S4353737_HAL_KEYPAD_COL4PIN) == 0) {

        KeypadFsmCurrentstate = COL1_STATE;
    }
}
