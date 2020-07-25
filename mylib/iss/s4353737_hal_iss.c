/** 
 **************************************************************
 * @file mylib/s4353737_hal_iss.c
 * @author George Todorovic - 43537370
 * @date 11/03/2020
 * @brief Drivers for ISS synchronisation of signals from A0 and
 *        on board push button.
 * REFERENCE: csse3010_mylib_hal_iss.pdf
 ***************************************************************
/* Includes  ------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_iss.h"
/* Defines -------------------------------------------------- */
#define RELEASED 0
#define PRESSED 1
/* External Variables --------------------------------------- */
unsigned int iss_eventcounter_val[3] = {0, 0, 0};
unsigned int iss_lasttimer_val[3] = {0, 0, 0};
unsigned int iss_delay_val[3] = {50, 200, 50};
/* Private Variables ---------------------------------------- */
unsigned int pinStateA0 = RELEASED; //starting state of pin

/**
 * @brief Initialise event counter values for the sources
 * @param None
 * @retval None
 */
void s4353737_hal_iss_init() {
    iss_eventcounter_val[S4353737_HAL_ISS_SOURCE_1] = 0;    //xenon monitor
    iss_eventcounter_val[S4353737_HAL_ISS_SOURCE_2] = 0;    //onboard  button
    iss_eventcounter_val[S4353737_HAL_ISS_SOURCE_3] = 0;    
}

/**
 * @brief Synchronise the signal to element noise and introduce a deboucning 
 *        feature to applicable signal sources. Each source will interact 
 *        with the synchronise function differently. Signal sources iss arrays
 *        will be used to keep track of the sources prevous behavior
 * @param signal_source_index: The triggered signal to be sampled
 * @retval None
 */
void s4353737_hal_iss_synchroniser(unsigned char signal_source_index) {
    if(signal_source_index == S4353737_HAL_ISS_SOURCE_1) {

        if(pinStateA0 == RELEASED) {

            iss_lasttimer_val[signal_source_index] = HAL_GetTick();
            pinStateA0 = PRESSED;
        
        } else {
            
            if(((HAL_GetTick() - iss_lasttimer_val[signal_source_index]) > 
                    iss_delay_val[signal_source_index]) && pinStateA0 == PRESSED) {

                debug_printf("ISS:%02d\n\r", iss_eventcounter_val[signal_source_index]);       
                iss_eventcounter_val[signal_source_index] = 
                    iss_eventcounter_val[signal_source_index] + 1;
            }

        pinStateA0 = RELEASED;
        }
    }
    if(signal_source_index == S4353737_HAL_ISS_SOURCE_2) {

        if((HAL_GetTick() - iss_lasttimer_val[signal_source_index]) > 
            iss_delay_val[signal_source_index]) {
            
            debug_printf("PB:%02d\n\r", iss_eventcounter_val[signal_source_index]);
            iss_eventcounter_val[signal_source_index] = 
                iss_eventcounter_val[signal_source_index] + 1;
            iss_lasttimer_val[signal_source_index] = HAL_GetTick();
        }
    }
    if(signal_source_index == S4353737_HAL_ISS_SOURCE_3) {

        if((HAL_GetTick() - iss_lasttimer_val[signal_source_index]) > 
            iss_delay_val[signal_source_index]) {
            
            iss_eventcounter_val[signal_source_index] = 
                iss_eventcounter_val[signal_source_index] + 1;
            iss_lasttimer_val[signal_source_index] = HAL_GetTick();
        }
    }
} 

/**
 * @brief Returns the event counter value of the signal source
 * @param signal_source_index: The sources of the signal to be returned
 * @retval Returns the value of eventcounter of the specified source
 */
unsigned int s4353737_hal_iss_eventcounter_read(unsigned char signal_source_index) {
    return iss_eventcounter_val[signal_source_index];
}

/**
 * @brief Returns the last time the interrupts was triggered. Used HAL_GetTick();
 * @param signal_source_index: THe sources of the signal to be returned
 * @retval Returns the value of the lasttimer of the specified sources
 */
unsigned int s4353737_hal_uss_lasttimer_read(unsigned char signal_source_index) {
    return iss_lasttimer_val[signal_source_index];
}

/**
 * @brief Resets the current value of the singal sources event counter to 0
 * @param signal_source_index: The source of the signal to be reset
 * @retval None
 */
void s4353737_hal_iss_eventcounter_reset(unsigned char signal_source_index) {
    iss_eventcounter_val[signal_source_index] = 0;
}

/**
 * @brief Reset the current value of the signal sources last timer to 0
 * @param signal_source_index: The source of the signal to be reset
 * @retval None
 */
void s4353737_hal_iss_lasttimer_reset(unsigned char signal_source_index) {
    iss_lasttimer_val[signal_source_index] = 0;
}

/**
 * @brief Update the delay value of the signal source
 * @param signal_source_index: The signal to be updated
 * @param delay_value: The value to be updated by
 * @retval None
 */
void s4353737_hal_iss_delaytimer_ctrl(unsigned char signal_source_index, int delay_value) {
    iss_delay_val[signal_source_index] = delay_value;
}