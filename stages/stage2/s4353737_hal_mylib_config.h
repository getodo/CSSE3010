 /** 
 **************************************************************
 * @file csse3010/stages/stage2/s4353737_hal_atimer_config.h
 * @author George Todorovic - 43537370
 * @date 30032020
 * @brief Atimer configuration header files
 * REFERENCE: csse3010_mylib_hal_atimer.pdf
 ***************************************************************
*/

TIM_HandleTypeDef TIM_Init2;

#define S4353737_HAL_ATIMER_PIN             BRD_D10_PIN
#define S4353737_HAL_ATIMER_PINPORT         BRD_D10_GPIO_PORT
#define S4353737_HAL_ATIMER_PINCLK          __BRD_D10_GPIO_CLK()
#define S4353737_HAL_ATIMER_CLKSPEED        25000
#define S4353737_HAL_ATIMER_PERIOD          50

#define S4353737_HAL_PWM_CLOCKFREQ		    50000
#define S4353737_HAL_PWM_PULSEPERIOD	    (S4353737_HAL_PWM_CLOCKFREQ/100)
#define S4353737_HAL_PWM_PERIOD			    S4353737_HAL_PWM_CLOCKFREQ/2
#define S4353737_HAL_PWM_CHANNEL		    TIM_CHANNEL_1
#define S4353737_HAL_PWM_TIMER			    TIM1
#define S4353737_HAL_PWM_TIMER_CLK()		__TIM1_CLK_ENABLE()
#define S4353737_HAL_PWM_TIMER_HANDLER	    TIM_Init2
#define S4353737_HAL_PWM_PIN                BRD_D6_PIN
#define S4353737_HAL_PWM_PINGPIOPORT        BRD_D6_GPIO_PORT
#define S4353737_HAL_PWM_PINGGPIOAF         GPIO_AF1_TIM1
#define S4353737_HAL_PWM_PINCLK             __BRD_D6_GPIO_CLK()
#define S4353737_HAL_PWM_PINCLKSPEED