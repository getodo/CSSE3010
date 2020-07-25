/** 
 **************************************************************
 * @file mylib/s4353737_hal_pwm.c
 * @author George Todorovic - 43537370
 * @date 30032020
 * @brief PWM driver files 
 * REFERENCE: csse3010_mylib_hal_pwm.pdf 
***************************************************************
*/
/*Includes -------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_pwm.h"
/*Private typedefs ------------------------------------------ */
TIM_HandleTypeDef TIM_Init2;

/**
 * @brief Initialise and setup pwm pins
 * @param None
 * @retval None
 */
void s4353737_hal_pwm_init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OC_InitTypeDef PWMConfig;

	uint16_t PrescalerValue = 0;

	S4353737_HAL_PWM_TIMER_CLK();
	S4353737_HAL_PWM_PINCLK;
	
	GPIO_InitStructure.Pin       = S4353737_HAL_PWM_PIN;
	GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull      = GPIO_NOPULL;
	GPIO_InitStructure.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStructure.Alternate = S4353737_HAL_PWM_PINGGPIOAF;
	HAL_GPIO_Init(BRD_D6_GPIO_PORT, &GPIO_InitStructure);

	PrescalerValue = (uint16_t) ((SystemCoreClock) / S4353737_HAL_PWM_CLOCKFREQ) - 1;

	TIM_Init2.Instance               = S4353737_HAL_PWM_TIMER;
	TIM_Init2.Init.Period            = S4353737_HAL_PWM_PERIOD;
	TIM_Init2.Init.Prescaler         = PrescalerValue;
	TIM_Init2.Init.ClockDivision     = 0;
	TIM_Init2.Init.RepetitionCounter = 0;
	TIM_Init2.Init.CounterMode       = TIM_COUNTERMODE_UP;

	PWMConfig.OCMode        = TIM_OCMODE_PWM1;
	PWMConfig.Pulse         = S4353737_HAL_PWM_PULSEPERIOD;
	PWMConfig.OCPolarity    = TIM_OCPOLARITY_HIGH;
	PWMConfig.OCNPolarity   = TIM_OCNPOLARITY_HIGH;
	PWMConfig.OCFastMode    = TIM_OCFAST_DISABLE;
	PWMConfig.OCIdleState   = TIM_OCIDLESTATE_RESET;
	PWMConfig.OCNIdleState  = TIM_OCNIDLESTATE_RESET;

	HAL_TIM_PWM_Init(&TIM_Init2);

	HAL_TIM_PWM_ConfigChannel(&TIM_Init2, &PWMConfig, TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&TIM_Init2, TIM_CHANNEL_1);
 }
