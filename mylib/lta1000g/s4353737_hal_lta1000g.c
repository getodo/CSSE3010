 /** 
 **************************************************************
 * @file mylib/s4353737_hal_lta1000g.c
 * @author George Todorovic - 43537370
 * @date 11032020
 * @brief lta1000g driver files
 * REFERENCE: csse3010_mylib_hal_lta1000g.pdf 
 ***************************************************************
/* Includes --------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
/* Prototypes ------------------------------------------------------------------*/
void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void s4353737_hal_lta1000g_write(unsigned short value);
void lta1000g_seg_set(int segment, unsigned char segment_value);
/* Private variables -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;
//store the pin values for looping
uint16_t pinArray[10] = {BRD_D16_PIN,
                         BRD_D17_PIN,
                         BRD_D18_PIN,
                         BRD_D19_PIN,
                         BRD_D20_PIN,
                         BRD_D21_PIN,
                         BRD_D22_PIN,
                         BRD_D23_PIN,
                         BRD_D24_PIN,
                         BRD_D25_PIN};
//store the port values for looping
GPIO_TypeDef* portArray[10] = {BRD_D16_GPIO_PORT,
                               BRD_D17_GPIO_PORT,
                               BRD_D18_GPIO_PORT,
                               BRD_D19_GPIO_PORT,
                               BRD_D20_GPIO_PORT,
                               BRD_D21_GPIO_PORT,
                               BRD_D22_GPIO_PORT,
                               BRD_D23_GPIO_PORT,
                               BRD_D24_GPIO_PORT,
                               BRD_D25_GPIO_PORT};
/**
 * @brief Helper function to write GPIO_Pins for LTA1000g
 * @param GPIOx: The specified GPIO port
 * @param GPIO_Pin: Specified the pin to be configured
 * @retval None
 */
void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    GPIO_InitStructure.Pin = GPIO_Pin;				    //Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;		//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;			//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;			//Pin latency
  	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);	        //Initialise Pin
}

/**
 * @brief Initialise hardware for LTA1000g
 * @param None
 * @retval None
 */
void s4353737_hal_lta1000g_init() {
    __BRD_D16_GPIO_CLK();
	__BRD_D17_GPIO_CLK();
    __BRD_D18_GPIO_CLK();
    __BRD_D19_GPIO_CLK();
    __BRD_D20_GPIO_CLK();
    __BRD_D21_GPIO_CLK();
    __BRD_D22_GPIO_CLK();
    __BRD_D23_GPIO_CLK();
    __BRD_D24_GPIO_CLK();
    __BRD_D25_GPIO_CLK();

    /* Set D16 - D25 as output pins */
    write_pin(BRD_D16_GPIO_PORT, BRD_D16_PIN);
    write_pin(BRD_D17_GPIO_PORT, BRD_D17_PIN);
    write_pin(BRD_D18_GPIO_PORT, BRD_D18_PIN);
    write_pin(BRD_D19_GPIO_PORT, BRD_D19_PIN);
    write_pin(BRD_D20_GPIO_PORT, BRD_D20_PIN);
    write_pin(BRD_D21_GPIO_PORT, BRD_D21_PIN);
    write_pin(BRD_D22_GPIO_PORT, BRD_D22_PIN);
    write_pin(BRD_D23_GPIO_PORT, BRD_D23_PIN);
    write_pin(BRD_D24_GPIO_PORT, BRD_D24_PIN);
    write_pin(BRD_D25_GPIO_PORT, BRD_D25_PIN);
}

/**
 * @brief Set the value for the corresponding LED bar
 * @param segment: The pin and port to be written
 * @param segment_value: The pin to be written HIGH or LOW (1 or 0)
 * @retval None
 */
void lta1000g_seg_set(int segment, unsigned char segment_value) {
    HAL_GPIO_WritePin(portArray[segment], pinArray[segment], segment_value);
}

/**
 * @brief Write the LED bar segments
 * @param value: The value of the two lights to be switched on
 * @retval None
 */
void s4353737_hal_lta1000g_write(unsigned short value) {
    for(int i = 0; i < 10; i++) {      //loop through all 10 pins
        for(int k = 0; k < 10; ++k) {  //loop through all 10 pins comparing them to value
            _Bool pinState = ((value  & (1 << k)) != 0); 
            lta1000g_seg_set(k, pinState);
        }
    }
}
