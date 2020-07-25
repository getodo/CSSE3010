/** 
**************************************************************
* @file mylib/s4353737_hal_pb.c
* @author George Todorovic - 43537370
* @date 11/03/2020
* @brief Mylib driver files for onboard button and pin A0 Xenon monitor inoput
* REFERENCE: csse3010_mylib_hal_pushbutton.pdf 
*************************************************************** 
*/
/* Includes --------------------------------------------------------------------*/ 
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_os_pb.h"
/* Private variables -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/**
 * @brief Initialise hardware for onboard button interrupt
 * @param None
 * @retval None
 */
void s4353737_hal_pb_on_init() {

   BRD_USER_BUTTON_GPIO_CLK_ENABLE();

   GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
   GPIO_InitStructure.Pull = GPIO_NOPULL;
   GPIO_InitStructure.Pin = BRD_USER_BUTTON_PIN;
   HAL_GPIO_Init(BRD_USER_BUTTON_GPIO_PORT, &GPIO_InitStructure);
   
   HAL_NVIC_SetPriority(BRD_USER_BUTTON_EXTI_IRQn, 10, 0);
   HAL_NVIC_EnableIRQ(BRD_USER_BUTTON_EXTI_IRQn);
}

/**
 * @brief Override default mapping of this handler
 * @param None
 * @retval None
 */
void s4353737_hal_pb_on_isr() {
   HAL_GPIO_EXTI_IRQHandler(BRD_USER_BUTTON_PIN);
}

/**
 * @brief Deinitialise onboard button
 * @param None
 * @retval None
 */
void s4353737_hal_pb_on_deinit() {
   HAL_GPIO_DeInit(BRD_USER_BUTTON_GPIO_PORT, BRD_USER_BUTTON_PIN);
}

/**
 * @brief Initialise hardware for pin A0 interrupt
 * @param None
 * @retval None
 */
void s4353737_hal_pb_iss_init() {
   __BRD_A0_GPIO_CLK();

   GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
   GPIO_InitStructure.Pull = GPIO_NOPULL;
   GPIO_InitStructure.Pin = BRD_A0_PIN;
   HAL_GPIO_Init(BRD_A0_GPIO_PORT, &GPIO_InitStructure);

   HAL_NVIC_SetPriority(BRD_A0_EXTI_IRQ, 10, 0);
   HAL_NVIC_EnableIRQ(BRD_A0_EXTI_IRQ);
}

/**
 * @brief Override default mapping of this handler
 * @param None
 * @retval None
 */ 
void s4353737_hal_pb_iss_isr() {
   HAL_GPIO_EXTI_IRQHandler(BRD_A0_PIN);
}

/**
 * @brief Deinitialise pin A0
 * @param None
 * @retval None
 */
void s4353737_hal_pb_iss_deinit() {
   HAL_GPIO_DeInit(BRD_A0_GPIO_PORT, BRD_A0_PIN);
}

/**
 * @brief EXTI line detection call back
 * @param GPIO_Pin: Specified the pins connected to the EXTI line
 * @retval None
 */ 
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   portENTER_CRITICAL();
   debug_printf("IN CALLBACK FUNCTION\n\r");
   portEXIT_CRITICAL();
  
	BaseType_t xHigherPriorityTaskWoken;

	if (GPIO_Pin == GPIO_PIN_13)
	{
		/* Is it time for another Task() to run? */
		xHigherPriorityTaskWoken = pdFALSE;

		if (s4353737LEDSemaphore != NULL) 
      {	/* Check if semaphore exists */
			xSemaphoreGiveFromISR( s4353737LEDSemaphore, &xHigherPriorityTaskWoken );		/* Give PB Semaphore from ISR*/
		}
			/* Perform context switching, if required. */
			portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

void EXTI15_10_IREHandler(void) 
{
   HAL_GPIO_EXTI_IRQHandler(BRD_USER_BUTTON_PIN);
}
   


