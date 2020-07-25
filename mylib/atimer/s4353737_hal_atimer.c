/** 
 **************************************************************
 * @file mylib/atimer/s4353737_hal_atimer
 * @author George Todorovic - 43537370
 * @date 30032020
 * @brief Atimer driver files
 * REFERENCE: csse3010_mylib_hal_atimer.pdf
 ***************************************************************
*/
/* Includes -------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_atimer.h"
/* Private typedefs ------------------------------------------ */
TIM_HandleTypeDef TIM_Init;
/* Private Defines ------------------------------------------- */
#define RESUME 1
#define PAUSE  0
/* Private Variables ----------------------------------------- */
int atimerState = 1;
int atimerPeriodVal = S4353737_HAL_ATIMER_PERIOD;
int atimerClkSpeedVal = S4353737_HAL_ATIMER_CLKSPEED;
unsigned int atimerCounterVal = 0;
unsigned short atimerPrescalerVal;

/**
 * @brief Initialise and start the atimer
 * @param None
 * @param None
*/
void s4353737_hal_atimer_init() {
    
    __TIM3_CLK_ENABLE();
    
    /* Set Prescaler Value */
    atimerPrescalerVal = (uint16_t)((SystemCoreClock/2) / atimerClkSpeedVal) - 1;
    
    /* TIM Base Config */
    TIM_Init.Instance               = TIM3;
    TIM_Init.Init.Period            = atimerPeriodVal;
    TIM_Init.Init.Prescaler         = atimerPrescalerVal;	//Set prescaler value
    TIM_Init.Init.ClockDivision     = 0;
    TIM_Init.Init.RepetitionCounter = 0;
    TIM_Init.Init.CounterMode       = TIM_COUNTERMODE_UP;

    /* Initialise the timer */
    HAL_TIM_Base_Init(&TIM_Init);
    /* Setup interrupt timer */
    HAL_NVIC_SetPriority(TIM3_IRQn, 10, 0);
    /* Enable the timer */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    /* Start the timer */
    HAL_TIM_Base_Start_IT(&TIM_Init);
}

/**
 * @brief Return the atimer counter value  in ms
 * @param None
 * @retval Current value of the atimer
 */
unsigned int s4353737_hal_atimer_getms() {
    return atimerCounterVal;
}

/**
 * @brief Reset the atimer counter value to 0
 * @param None
 * @retval None
 */
void s4353737_hal_atimer_timer_reset() {
    atimerCounterVal = 0;
}

/**
 * @brief Pause the atimer
 * @param None
 * @retval None
 */
void s4353737_hal_atimer_timer_pause() {
    atimerState = PAUSE;
}

/**
 * @brief Resume the atimer from a paused state
 * @param None
 * @retval None
 */
void s4353737_hal_atimer_resume() {
    atimerState = RESUME;
}

/**
 * @brief Update the clockspeed of the atimer
 * @param frequency: The frequency added to the current frequency
 * @retval None
 */
void s4353737_hal_atimer_clkspeed_set(int frequency) {
    atimerClkSpeedVal = atimerClkSpeedVal + frequency;
}

/**
 * @brief Return the current clock speed
 * @param None
 * @retval The current clock speed
 */
int s4353737_hal_atimer_clkspeed_get() {
    return atimerClkSpeedVal;
}

/**
 * @brief Add to the current period value
 * @param period: The value to be added
 * @retval None
 */
void s4353737_hal_atimer_period_set(int period) {
    atimerPeriodVal = s4353737_hal_get_period() + period;
}

/**
 * @brief Return the current period
 * @param None
 * @retval The current period value
 */
int s4353737_hal_get_period() {
    return atimerPeriodVal;
}

/**
 * @brief Helper function to configure pins
 * @param pin: pin to be configured
 * @param port: port of the pin to be configured
 * @retval None
 */
void GPIO_config(uint32_t pin, GPIO_TypeDef* port) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;
    GPIO_InitStructure.Pin = pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(port, &GPIO_InitStructure);
}

/**
 * @brief Initialise the atimer pin
 * @param None
 * @retval None
 */
void s4353737_hal_atimer_init_pin() {
    S4353737_HAL_ATIMER_PINCLK;
    GPIO_config(S4353737_HAL_ATIMER_PIN, S4353737_HAL_ATIMER_PINPORT);
    HAL_GPIO_WritePin(S4353737_HAL_ATIMER_PINPORT, S4353737_HAL_ATIMER_PIN, 1);
}

/**
 * @brief Period elapsed callback in non blocking mode
 * @param htim: Pointer to a TIM_HandleTypeDef that contains the configuration information for the TIM module.
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3) {
        if(atimerState == 1) {
            atimerCounterVal++;
        }
        HAL_GPIO_TogglePin(S4353737_HAL_ATIMER_PINPORT, S4353737_HAL_ATIMER_PIN);
	}
}

/**
 * @brief IRQ handler for interrupt call
 * @param None
 * @retval None
 */
void TIM3_IRQHandler() {
    HAL_TIM_IRQHandler(&TIM_Init);
}
