/** 
 **************************************************************
 * @file mylib/s4353737_hal_joystick.h
 * @author George Todorovic - 43537370
 * @date 30032020
 * @brief Header files for joystick
 * REFERENCE: csse3010_mylib_hal_joystick.pdf 
 ***************************************************************
*/
#ifndef __S4353737_HAL_JOYSTICK_H
#define __S4353737_HAL_JOYSTICK_H

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"

ADC_HandleTypeDef xAdcHandle;
ADC_HandleTypeDef yAdcHandle;

#define S4353737_HAL_JOYSTICK_X_READ() joystick_readxy(xAdcHandle)
#define S4353737_HAL_JOYSTICK_Y_READ() joystick_readxy(yAdcHandle)
#define S4353737_HAL_JOYSTICK_Z_READ() 1

void s4353737_hal_joystick_init();
int joystick_readxy(ADC_HandleTypeDef AdcHandle);

#endif
