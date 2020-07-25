/** 
 **************************************************************
 * @file mylib/s4353737_hal_atimer.h
 * @author George Todorovic - 43537370
 * @date 300320
 * @brief atimer header file
 * REFERENCE: csse3010_mylib_hal_atimer.pdf 
 ***************************************************************
*/
#ifndef   S4353737_HAL_MYLIB_CONFIGURE_INC
#include "s4353737_hal_mylib_configure.h"

#ifndef S4353737_HAL_ATIMER_PIN
#define S4353737_HAL_ATIMER_PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_ATIMER_PINPORT     
#define S4353737_HAL_ATIMER_PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_ATIMER_PINCLK
#define S4353737_HAL_ATIMER_PINCLK      __BRD_D10_GPIO_CLK()
#endif

#ifndef S4353737_HAL_ATIMER_PERIOD 
#define S4353737_HAL_ATIMER_PERIOD      2
#endif

#ifndef S4353737_HAL_ATIMER_CLKSPEED 
#define S4353737_HAL_ATIMER_CLKSPEED    50000
#endif

#define s4353737_hal_atimer_read()      __HAL_TIM_GetCounter(&TIM_Init)

void s4353737_hal_atimer_init();
unsigned int s4353737_hal_atimer_getms();
void s4353737_hal_atimer_timer_reset();
void s4353737_hal_atimer_timer_pause();
void s4353737_hal_atimer_resume();
void s4353737_hal_atimer_clkspeed_set(int frequency);
void s4353737_hal_atimer_period_set(int period);
int s4353737_hal_get_period();
int s4353737_hal_get_atimer_frequency();
void GPIO_config(uint32_t pin, GPIO_TypeDef* port);
void s4353737_hal_atimer_init_pin();
int s4353737_hal_atimer_clkspeed_get();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void TIM3_IRQHandler();

#endif
