/** 
 **************************************************************
 * @file mylib/hamming/s4353737_lib_hamming.h
 * @author George Todorovic - 43537370
 * @date 20042020
 * @brief header file for hamming drivers
 * REFERENCE: csse3010_mylib_lib_hamming.pdf 
 ***************************************************************
*/
#ifndef __S4353737_LIB_HAMMING_H
#define __S4353737_LIB_HAMMING_H

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"

uint8_t s4353737_lib_hamming_hbyte_encode(uint8_t in);
int s4353737_lib_hamming_parity_error(uint8_t byte);
uint8_t s4353737_lib_hamming_byte_decode(uint16_t input);
uint16_t s4353737_lib_hamming_byte_encode(uint16_t input);

#endif
