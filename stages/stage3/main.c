/** 
 **************************************************************
 * @file stages/stage3/main.c
 * @author George Todorovic - 43537370
 * @date 20042020
 * @brief main file for stage3
 * REFERENCE: csse3010_mylib_hal_hamming.pdf
 ***************************************************************
/* Private define -------------------------------------------- */
#define IDLE_STATE      0
#define ENCODE_STATE    1
#define DECODE_STATE    2
/* Includes -------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_atimer.h"
#include "s4353737_hal_keypad.h"
#include "s4353737_lib_hamming.h"
/* Private variables ----------------------------------------- */
uint16_t codedWord;
uint16_t decodedWord;
int keypadCount = 0;
int hammingFsmCurrentstate = IDLE_STATE;
char keypadCharOne;
char keypadCharTwo;
char keypadHexOne;
char keypadHexTwo;
char codeState;
/* Prototype Functions --------------------------------------- */
void init_hardware();
void process_idle_state();
void process_encode_state();
void process_decode_state();
int change_fsm_state(char keyChar1, char keyChar2);

void main() {

    init_hardware();
    while(1) {
        
        if(s4353737_hal_atimer_getms() == 50) {

            s4353737_hal_keypad_fsmprocessing();
            s4353737_hal_atimer_timer_reset();
            if(s4353737_hal_keypad_read_status()) {

                keypadCount++;
                switch(hammingFsmCurrentstate) {

                    case IDLE_STATE:

                        process_idle_state();
                        break;

                    case ENCODE_STATE:

                        process_encode_state();
                        break;

                    case DECODE_STATE:

                        process_decode_state();
                        break;
                }
            }
        }
    }
}

/**
 * @brief Process idle state FSM commands. Idle state will print
 *        ascii key values to the terminal after two key presses
 *        have been detected. Values will print as <c><c>. Idle
 *        state is enetered when <f><f> has been detected.
 * @param None
 * @retval None
 */ 
void process_idle_state() {

    if(keypadCount%2 == 1) {

        keypadCharOne = s4353737_hal_keypad_read_ascii();
    } else {

        keypadCharTwo = s4353737_hal_keypad_read_ascii();
        if(change_fsm_state(keypadCharOne, keypadCharTwo)) {

            return;
        } else {

            debug_printf("<%c><%c>\n\r", keypadCharOne, keypadCharTwo);
        } 
    }
}

/**
 * @brief Process encode state FSM commands. Encode state will print
 *        the ascii values to be encoded. It will then change
 *        those values to hex values shift the first keypress
 *        value left by 4 then or the two values together.
 *        It will then print the new encoded value. Encode state
 *        is entered when <e><e> has been detected. 
 * @param None
 * @retval None
 */ 
void process_encode_state() {

    if(keypadCount%2 == 1) {

        keypadCharOne = s4353737_hal_keypad_read_ascii();
        keypadHexOne = s4353737_keypad_read_key();
    } else {

        keypadCharTwo = s4353737_hal_keypad_read_ascii();
        keypadHexTwo = s4353737_keypad_read_key();
        if(change_fsm_state(keypadCharOne, keypadCharTwo)) {

            return;
        } else {

            char encodeKeypadValue = ((keypadHexOne << 4) | keypadHexTwo);
            debug_printf("<%c> <%c> <%c><%c>\n\r", codeState, codeState, keypadCharOne, keypadCharTwo);
            codedWord = s4353737_lib_hamming_byte_encode(encodeKeypadValue);
            debug_printf("HE %04x\r\n", codedWord);
        }
    }
}

/**
 * @brief Process decode state FSM commands. Decode state will print
 *        the ascii values to be Decoded. It will then change
 *        those values to hex values shift the first keypress
 *        value left by 4 then or the two values together.
 *        It will then print the new decoded value. Decode state
 *        is entered when <d><d> has been detected.  
 * @param None
 * @retval None
 */ 
void process_decode_state() {

    if(keypadCount%2 == 1) {

        keypadCharOne = s4353737_hal_keypad_read_ascii();
        keypadHexOne = s4353737_keypad_read_key();
    } else {

        keypadCharTwo = s4353737_hal_keypad_read_ascii();
        keypadHexTwo = s4353737_keypad_read_key();
        if(change_fsm_state(keypadCharOne, keypadCharTwo)) {

            return;
        } else {

            debug_printf("<%c> <%c> <%c><%c>\n\r", codeState, codeState, keypadCharOne, keypadCharTwo);
            char decodeKeypadValue = (keypadHexOne << 4) | keypadHexTwo;
            s4353737_lib_hamming_byte_decode(decodeKeypadValue);
        }
    }
}

/**
 * @brief Change the state of the FSM. State will change depending
 *        on keypress. Will return 1 if a change of state is made
 *        otherwise will return 0.
 * @param keyChar1 - first key press
 * @param keyChar2 - second key press
 * @retval Returns 1 if a state change is made else will return 0
 */
int change_fsm_state(char keyChar1, char keyChar2) {
    
    keypadCount = 0;

    if(keyChar1 == 'E' && keyChar2 == 'E' && codeState != 'E') {

        hammingFsmCurrentstate = ENCODE_STATE;
        codeState = 'E';
        return 1;
    } else if(keyChar1 == 'F' && keyChar2 == 'F' && codeState != 'F') {

        hammingFsmCurrentstate = IDLE_STATE;
        codeState = 'F';
        return 1;
    } else if(keyChar1 == 'D' && keyChar2 == 'D' && codeState != 'D') {

        hammingFsmCurrentstate = DECODE_STATE;
        codeState = 'D';
        return 1;
    }
    return 0;
}

/**
 * @brief Initilise driver and board hardware.
 * @param None
 * @retval None
 */
void init_hardware() {
    BRD_init();
    s4353737_hal_atimer_init();
}
