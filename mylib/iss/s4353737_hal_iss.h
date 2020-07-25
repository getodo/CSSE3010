/** 
**************************************************************
* @file mylib/s4353737_hal_iss.h
* @author George Todorovic - 43537370
* @date 11/03/2020
* @brief header file for iss synchonisation 
* REFERENCE: csse3010_mylib_hal_iss.pdf 
***************************************************************
*/

#ifndef __S4353737_HAL_ISS_H
#define __S4353737_HAL_ISS_H
/* Defines -------------------------------------------------- */
#define S4353737_HAL_ISS_SOURCE_1 0
#define S4353737_HAL_ISS_SOURCE_2 1
#define S4353737_HAL_ISS_SOURCE_3 2
/* Private Variables ---------------------------------------- */
extern unsigned int iss_eventcounter_val[3];
extern unsigned int iss_lasttimer_val[3];
extern unsigned int iss_delay_val[3];

void s4353737_hal_iss_init();
void s4353737_hal_iss_synchroniser(unsigned char signal_source_index);
unsigned int s4353737_hal_iss_eventcounter_read(unsigned char signal_source_index);
unsigned int s4353737_hal_uss_lasttimer_read(unsigned char signal_source_index);
void s4353737_hal_iss_eventcounter_reset(unsigned char signal_source_index);
void s4353737_hal_iss_lasttimer_reset(unsigned char signal_source_index);
void s4353737_hal_iss_delaytimer_ctrl(unsigned char signal_source_index, int delat_value);

#endif