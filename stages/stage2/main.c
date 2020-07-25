/** 
 **************************************************************
 * @file mylib/atimer/s4353737_hal_atimer
 * @author George Todorovic - 43537370
 * @date 30032020
 * @brief Atimer driver files
 * REFERENCE: csse3010_mylib_hal_atimer.pdf
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * sxxxxxx_mylib_template_init() - intialise mylib template driver
 * sxxxxxx_mylib_template_set() - set mylib template driver 
 *************************************************************** 
 */
/* Private define -------------------------------------------- */
#define ON  1
#define OFF 0
/* Includes -------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_hal_atimer.h"
#include "s4353737_hal_joystick.h"
#include "s4353737_hal_lta1000g.h"
#include "s4353737_hal_pwm.h"
#include "s4353737_hal_iss.h"
/* Private variables ----------------------------------------- */
unsigned short ledSeg;
int pinState = S4353737_HAL_JOYSTICK_Z_READ();
//store the pin values for looping
uint16_t pinArrays[10] = {BRD_D16_PIN,
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
GPIO_TypeDef* portArrays[10] = {BRD_D16_GPIO_PORT,
                               BRD_D17_GPIO_PORT,
                               BRD_D18_GPIO_PORT,
                               BRD_D19_GPIO_PORT,
                               BRD_D20_GPIO_PORT,
                               BRD_D21_GPIO_PORT,
                               BRD_D22_GPIO_PORT,
                               BRD_D23_GPIO_PORT,
                               BRD_D24_GPIO_PORT,
                               BRD_D25_GPIO_PORT};
/* Prototype functions --------------------------------------- */
void init_hardware();
void run_atimer();
void yadc_increment_led();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void EXTI3_IRQHandler();

int main() {
    init_hardware();
    uint32_t current_val = 0;
	uint32_t next_val = 0;
	uint8_t mode = 0;
    while(1) {
        int xAdcValue = S4353737_HAL_JOYSTICK_X_READ();
        run_atimer();
        yadc_increment_led();
        current_val = S4353737_PWM_DC_GET();
        if (mode) {
            next_val = (uint32_t)(current_val*1.1);
        } else {
            next_val = (uint32_t)(current_val*0.9);
        }
        S4353737_PWM_DC_SET(2*xAdcValue);

        if ((next_val > S4353737_HAL_PWM_PULSEPERIOD*20) && (mode == 1)) {
            mode = 0;
        }
        if ((next_val < S4353737_HAL_PWM_PULSEPERIOD) && (mode == 0)) {
            mode = 1;
        }
    }   
}

/**
 * @brief Increment the upper segment of LED's on the board as the via the value
 *        returned on the yAdc.
 * @param None
 * @retval None
 */
void yadc_increment_led() {
    int yAdcValue = S4353737_HAL_JOYSTICK_Y_READ();
    if(yAdcValue < 2000) {

            if(yAdcValue < 50 && yAdcValue > 0) {
                ledSeg = 1023;
            }
            if(yAdcValue < 500 && yAdcValue > 51) {
                ledSeg = 511;
            }
            if(yAdcValue < 760 && yAdcValue > 501) {
                ledSeg = 255;
            }
            if(yAdcValue < 1140 && yAdcValue > 761) {
                ledSeg = 127;
            }
            if(yAdcValue < 1520 && yAdcValue > 1141) {
                ledSeg = 63;
            }
        } 
    
    else if(yAdcValue < 2100) {
        ledSeg = 31;
    }

    if(yAdcValue > 2475) {
        ledSeg = 63;
    }
    if(yAdcValue > 2850) {
        ledSeg = 127;
    }
    if(yAdcValue > 3375) {
        ledSeg = 255;
    }
    if(yAdcValue > 4050) {
        ledSeg = 511;
    }
    if(yAdcValue > 4051) {
        ledSeg = 1023;
    }
    s4353737_hal_lta1000g_write(ledSeg);
}

/**
 * @brief Initialise driver hardware
 * @param None
 * @retval None
 */
void init_hardware() {
    BRD_init();
    s4353737_hal_pwm_init();
    s4353737_hal_atimer_init();
    s4353737_hal_atimer_init_pin();
    s4353737_hal_joystick_init();
    s4353737_hal_lta1000g_init();
}

/**
 * @brief Waits for user input to display information about the current 
 *        values of the atimer
 * @param None
 * retval None
 */
void run_atimer() {
    char RxChar = debug_getc();

        if(RxChar != '\0') {

            switch(RxChar) {
                case 'f':
                    s4353737_hal_atimer_timer_pause();
                    s4353737_hal_atimer_init();
                    break;

                case 'r':
                    s4353737_hal_atimer_resume();
                    break;

                case 'z':
                    s4353737_hal_atimer_timer_reset();
                    break;

                case 'c':
                    debug_printf("atimer tick: %d\n\r", s4353737_hal_atimer_getms()*
                        s4353737_hal_atimer_clkspeed_get());
                    break;

                case 't':
                    debug_printf("atimer ms: %d\n\r", s4353737_hal_atimer_getms());
                    break;

                case '+':
                    s4353737_hal_atimer_period_set(s4353737_hal_atimer_clkspeed_get()/100);
                    s4353737_hal_atimer_init();
                    break;
                
                case '-':
                    s4353737_hal_atimer_period_set(-(s4353737_hal_atimer_clkspeed_get()/100));
                    s4353737_hal_atimer_init();
                    break;

                case 'i':
                    s4353737_hal_atimer_period_set(s4353737_hal_get_period()/(s4353737_hal_atimer_clkspeed_get()/1000));
                    s4353737_hal_atimer_clkspeed_set(1000);
                    s4353737_hal_atimer_init();
                    break;

                case 'd':
                    s4353737_hal_atimer_clkspeed_set(-1000);
                    s4353737_hal_atimer_period_set(s4353737_hal_get_period()/(s4353737_hal_atimer_clkspeed_get()/1000));
                    s4353737_hal_atimer_init();
                    break;
        }
    }
}
/**
 * @brief GPIO Interrupt call function. LED lights will switch on or off
          depending on their current state.
 * @param GPIO_Pin: The pin to be on which an interrupt occurs.
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)  {
    if(GPIO_Pin == BRD_A3_PIN) {
        unsigned int tempEvent = 
            s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_3);
        s4353737_hal_iss_synchroniser(S4353737_HAL_ISS_SOURCE_3);

        if(s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_3) == 11) {     
           
            s4353737_hal_iss_eventcounter_reset(S4353737_HAL_ISS_SOURCE_3);

        }
        if(s4353737_hal_iss_eventcounter_read(S4353737_HAL_ISS_SOURCE_3) 
            != tempEvent) {
                if(pinState == ON) {

                    for(int i = 0; i < 10; i++) {
                        HAL_GPIO_DeInit(portArrays[i], pinArrays[i]);
                        pinState = OFF;
                    } 
                } else {
                        s4353737_hal_lta1000g_init();
                        pinState = ON;
                }
        }
    } 
}

/**
 * @brief Overrider default mapping of this handler
 * @param None
 * @retval None
 */
void EXTI3_IRQHandler() {
    HAL_GPIO_EXTI_IRQHandler(BRD_A3_PIN);
}



