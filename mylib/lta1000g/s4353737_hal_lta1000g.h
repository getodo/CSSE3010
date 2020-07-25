/** 
**************************************************************
* @file mylib/lta1000g/s4353737_hal_lta1000g.h
* @author George Todorovic - 43537370
* @date 11032020
* @brief Header file for LTA1000g drivers
***************************************************************
*/

#ifndef __S4353737_HAL_LTA1000G_H
#define __S4353737_HAL_LTA1000G_H

void s4353737_hal_lta1000g_init();
void lta1000g_seg_set(int segment, unsigned char segment_value);
void s4353737_hal_lta1000g_write(unsigned short value);

#endif
