  /** 
 *******************************************************************************
 * @file 	  mylib/s4353737_hal_joystick.c
 * @author    George Todorovic - 43537370
 * @date      30032020
 * @brief 	  Joystick driver files
 * REFERENCE: csse3010_mylib_hal_joystick.pdf 
 *******************************************************************************
 */

/* Includes ----------------------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_joystick.h"
#include "s4353737_os_joystick.h"
/* Private typedefs --------------------------------------------------------- */
ADC_ChannelConfTypeDef xAdcChanConfig;
ADC_ChannelConfTypeDef yAdcChanConfig;
/* Private Variables -------------------------------------------------------- */

/**
 * @brief Initiate hardware required for joystick
 * @param None
 * @retval None
 */
void s4353737_hal_joystick_init() {
    GPIO_InitTypeDef GPIO_InitStructure;

	BRD_USER_BUTTON_GPIO_CLK_ENABLE();

   	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
   	GPIO_InitStructure.Pull = GPIO_NOPULL;
   	GPIO_InitStructure.Pin = BRD_USER_BUTTON_PIN;
   	HAL_GPIO_Init(BRD_USER_BUTTON_GPIO_PORT, &GPIO_InitStructure);
   
   	HAL_NVIC_SetPriority(BRD_USER_BUTTON_EXTI_IRQn, 10, 0);
   	HAL_NVIC_EnableIRQ(BRD_USER_BUTTON_EXTI_IRQn);

	__BRD_A3_GPIO_CLK();

	GPIO_InitStructure.Pin 		= BRD_A3_PIN;
	GPIO_InitStructure.Mode 	= GPIO_MODE_IT_RISING;
    GPIO_InitStructure.Pull 	= GPIO_PULLUP;
	GPIO_InitStructure.Speed 	= GPIO_SPEED_FAST;
    
	HAL_GPIO_Init(BRD_A3_GPIO_PORT, &GPIO_InitStructure);
   
    HAL_NVIC_SetPriority(BRD_A3_EXTI_IRQ, 10, 0);
    HAL_NVIC_EnableIRQ(BRD_A3_EXTI_IRQ);

	__BRD_A1_GPIO_CLK();
	
	GPIO_InitStructure.Pin  = BRD_A1_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(BRD_A1_GPIO_PORT, &GPIO_InitStructure);

	__ADC1_CLK_ENABLE();

    xAdcHandle.Instance 				  = (ADC_TypeDef *)(ADC1_BASE);		//Use ADC1
	xAdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	xAdcHandle.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	xAdcHandle.Init.ScanConvMode          = DISABLE;
	xAdcHandle.Init.ContinuousConvMode    = DISABLE;
	xAdcHandle.Init.DiscontinuousConvMode = DISABLE;
	xAdcHandle.Init.NbrOfDiscConversion   = 0;
	xAdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	xAdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;	//No Trigger
	xAdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;			//Right align data
	xAdcHandle.Init.NbrOfConversion       = 1;
	xAdcHandle.Init.DMAContinuousRequests = DISABLE;
	xAdcHandle.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&xAdcHandle);

	/* Configure ADC Channel for pin A0*/
	xAdcChanConfig.Channel      = BRD_A1_ADC_CHAN;						
	xAdcChanConfig.Rank         = 1;
	xAdcChanConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	xAdcChanConfig.Offset       = 0;

	HAL_ADC_ConfigChannel(&xAdcHandle, &xAdcChanConfig);

	__BRD_A2_GPIO_CLK();

	GPIO_InitStructure.Pin = BRD_A2_PIN;

	HAL_GPIO_Init(BRD_A2_GPIO_PORT, &GPIO_InitStructure);

    yAdcHandle.Instance 				  = (ADC_TypeDef *)(ADC2_BASE);						//Use ADC1
	yAdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	yAdcHandle.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	yAdcHandle.Init.ScanConvMode          = DISABLE;
	yAdcHandle.Init.ContinuousConvMode    = DISABLE;
	yAdcHandle.Init.DiscontinuousConvMode = DISABLE;
	yAdcHandle.Init.NbrOfDiscConversion   = 0;
	yAdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	yAdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	yAdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	yAdcHandle.Init.NbrOfConversion       = 1;
	yAdcHandle.Init.DMAContinuousRequests = DISABLE;
	yAdcHandle.Init.EOCSelection          = DISABLE;

    HAL_ADC_Init(&yAdcHandle);

	__ADC2_CLK_ENABLE();

	/* Configure ADC Channel for pin A2*/
	yAdcChanConfig.Channel      = BRD_A2_ADC_CHAN;							
	yAdcChanConfig.Rank         = 1;
	yAdcChanConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	yAdcChanConfig.Offset       = 0;

	HAL_ADC_ConfigChannel(&yAdcHandle, &yAdcChanConfig);		
}

/**
 * @brief Read the ADC value of the joystick in x and y direction
 * @param AdcHandle: the handlers of the read joystick
 * @retval adc_value: value of the adc read
 */
int joystick_readxy(ADC_HandleTypeDef AdcHandle) {
    unsigned int adc_value;
    HAL_ADC_Start(&AdcHandle); // Start ADC conversion
	// Wait for ADC conversion to finish
	while (HAL_ADC_PollForConversion(&AdcHandle, 10) != HAL_OK);
	return (uint16_t)(HAL_ADC_GetValue(&AdcHandle));
}
