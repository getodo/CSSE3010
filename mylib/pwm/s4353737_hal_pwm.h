/** 
 **************************************************************
 * @file mylib/s4353737_hal_joystick.h
 * @author George Todorovic - 43537370
 * @date 30032020
 * @brief Header files for joystick
 * REFERENCE: csse3010_mylib_hal_joystick.pdf 
 ***************************************************************
*/
#ifndef  S4353737_HAL_MYLIB_CONFIG_INC
#include "s4353737_hal_mylib_config.h"

#ifndef S4353737_HAL_PWM_CLOCKFREQ
#define S4353737_HAL_PWM_CLOCKFREQ		    100
#endif

#ifndef S4353737_HAL_PWM_PULSEPERIOD
#define S4353737_HAL_PWM_PULSEPERIOD	    100
#endif

#ifndef S4353737_HAL_PWM_PERIOD
#define S4353737_HAL_PWM_PERIOD			    100
#endif

#ifndef S4353737_HAL_PWM_CHANNEL
#define S4353737_HAL_PWM_CHANNEL		    0
#endif

#ifndef S4353737_HAL_PWM_TIMER
#define S4353737_HAL_PWM_TIMER			    0
#endif

#ifndef S4353737_HAL_PWM_TIMER_CLK
#define S4353737_HAL_PWM_TIMER_CLK()		0
#endif

#ifndef S4353737_HAL_PWM_TIMER_HANDLER
#define S4353737_HAL_PWM_TIMER_HANDLER	    0
#endif

#ifndef S4353737_HAL_PWM_PIN
#define S4353737_HAL_PWM_PIN                BRD_D0_PIN
#endif

#ifndef S4353737_HAL_PWM_PINGPIOPORT
#define S4353737_HAL_PWM_PINGPIOPORT        BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_PWM_PINGGPIOAF
#define S4353737_HAL_PWM_PINGGPIOAF         0
#endif

#ifndef S4353737_HAL_PWM_PINCLK
#define S4353737_HAL_PWM_PINCLK             0
#endif

#ifndef S4353737_HAL_PWM_PINCLKSPEED
#define S4353737_HAL_PWM_PINCLKSPEED        0
#endif

#define S4353737_PWM_DC_GET() 		    __HAL_TIM_GET_COMPARE(&TIM_Init2, TIM_CHANNEL_1)
#define S4353737_PWM_DC_SET(value) 	    __HAL_TIM_SET_COMPARE(&TIM_Init2, TIM_CHANNEL_1, value)

void s4353737_hal_pwm_init();

#endif