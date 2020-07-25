/** 
 **************************************************************
 * @file mylib/s4353737_hal_pb.h
 * @author George Todorovic - 43537370
 * @date 11/03/2020
 * @brief header file for onboard push button and pin A0 GPIO config
 * REFERENCE: csse3010_mylib_hal_pushbutton.pdf 
 ***************************************************************
*/
#ifndef __S4353737_HAL_PB_h
#define __S4353737_HAL_PB_h

void s4353737_hal_pb_on_init();
void s4353737_hal_pb_on_isr();
void s4353737_hal_pb_on_deinit();
void s4353737_hal_pb_iss_init();
void s4353737_hal_pb_iss_isr();
void s4353737_hal_pb_iss_deinit();

#endif

