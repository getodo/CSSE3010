/** 
 **************************************************************
 * @file mylib/hamming/s4353737_lib_hamming.c
 * @author George Todorovic - 43537370
 * @date 20042020
 * @brief Driver files for hamming encoding and decoding
 * REFERENCE: csse3010_mylib_lib_hamming.pdf
 ***************************************************************
*/
/* Includes ------------------------------------------------- */
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4353737_lib_hamming.h"
/* Prototype Functions -------------------------------------- */
int s4353737_lib_hamming_parity_error(uint8_t byte);
uint8_t s4353737_lib_hamming_byte_decode(uint16_t input);
uint16_t s4353737_lib_hamming_byte_encode(uint16_t input);

/**
 * @brief Internal function to encode a half byte
 * @param in - the half byte to be encoded
 * @retval out - the encoded half byte
 */
uint8_t s4353737_lib_hamming_hbyte_encode(uint8_t in) {

	uint8_t d0, d1, d2, d3;
	uint8_t p0 = 0, h0, h1, h2;
	uint8_t z;
	uint8_t out;
	/* extract bits */
	d0 = ((in & 0x01) ? 1 : 0);
    d1 = ((in & 0x02) ? 1 : 0);
    d2 = ((in & 0x04) ? 1 : 0);
    d3 = ((in & 0x08) ? 1 : 0);
	/* calculate hamming parity bits */
	h0 = d1 ^ d2 ^ d3;
	h1 = d0 ^ d2 ^ d3;
	h2 = d0 ^ d1 ^ d3;
	/* generate out byte without parity bit P0 */
	out = (h0 << 1) | (h1 << 2) | (h2 << 3) |
		(d0 << 4) | (d1 << 5) | (d2 << 6) | (d3 << 7);
	/* calculate even parity bit */
	for (z = 1; z<8; z++)
		p0 = p0 ^ !!(out & (1 << z));

	out |= p0;

	return(out);
}

/**
 * @brief Return the decoded half byte from a byte. Will
 *        detect errors and correct if error has occured.
 *        Only one bit errors will be corrected.
 * @param input - The byte to be decoded
 * @retval dn - The 8bit decoded value
 */
uint8_t s4353737_lib_hamming_byte_decode(uint16_t input) {
    /* extract hamming bits */
    uint8_t h0 = ((input >> 1) & 0x1);
    uint8_t h1 = ((input >> 2) & 0x1);
    uint8_t h2 = ((input >> 3) & 0x1);
    /* extract data bits */
    uint8_t d0 = ((input & 16) ? 1 : 0);
    uint8_t d1 = ((input & 32) ? 1 : 0);
    uint8_t d2 = ((input & 64) ? 1 : 0);
    uint8_t d3 = ((input & 128) ? 1 : 0);
    /* check parity */
    uint8_t p0 = h0 ^ h1 ^ h2 ^ d0 ^ d1 ^ d2 ^ d3;
    /* find syndrome matrix s values */
    uint8_t s0 = h0 ^ d1 ^ d2 ^ d3;
    uint8_t s1 = h1 ^ d0 ^ d2 ^ d3;
    uint8_t s2 = h2 ^ d0 ^ d1 ^ d3;
    /* generate out byte without parity bit P0 */
    uint8_t dn = (d0 << 0) + (d1 << 1) + (d2 << 2) + (d3 << 3);
    /* calculate syndrome */
    uint8_t syndrome = (s0 << 0) + (s1 << 1) + (s2 << 2);
    /* check parity error */
    int parityError = s4353737_lib_hamming_parity_error(input);
    /* check if the syndrome is 0 */
    if(!syndrome) {

        if(!parityError) {

            debug_printf("HD %d P%d\n\r", dn, parityError);
            return 0; //no error found
        } else {

            debug_printf("HD %d P%d\n\r", dn, parityError);
            return 1; //two bit error found can't fix
        }
    } else {

        switch(syndrome) { //correct the bit if depending on the syndrome value
            
            case 1:

                h0 = h0 ^ (0x1);
                break;

            case 2:

                h1 = h1 ^ (0x1);
                break;

            case 3:

                h2 = h2 ^ (0x1);
                break;

            case 4:

                d0 = d0 ^ (0x1);
                break;

            case 5:

                d1 = d1 ^ (0x1);
                break;

            case 6:

                d2 = d2 ^ (0x1);
                break;

            case 7:

                d3 = d3 ^ (0x1);
                break;

        }
        /* recalculate parity value */
        p0 = h0 ^ h1 ^ h2 ^ d0 ^ d1 ^ d2 ^ d3;
        debug_printf("HD %d P%d\n\r", dn, s4353737_lib_hamming_parity_error(input));
    }
    return dn;
}

/**
  * Implement Hamming Code on a full byte of input
  * This means that 16-bits out output is needed
  */
uint16_t s4353737_lib_hamming_byte_encode(uint16_t input) {
	uint16_t out;
	/* first encode D0..D3 (first 4 bits),
	 * then D4..D7 (second 4 bits).
	 */
	out = s4353737_lib_hamming_hbyte_encode(input & 0xF) |
		(s4353737_lib_hamming_hbyte_encode(input >> 4) << 8);

	return(out);
}

int s4353737_lib_hamming_parity_error(uint8_t byte) {

    uint8_t h0 = ((byte >> 1) & 0x1);
    uint8_t h1 = ((byte >> 2) & 0x1);
    uint8_t h2 = ((byte >> 3) & 0x1);

    uint8_t d0 = ((byte & 16) ? 1 : 0);
    uint8_t d1 = ((byte & 32) ? 1 : 0);
    uint8_t d2 = ((byte & 64) ? 1 : 0);
    uint8_t d3 = ((byte & 128) ? 1 : 0);

    uint8_t p0 = h0^h1^h2^d0^d1^d2^d3;

    if(p0 == ((byte & 0x1) ? 1 : 0)) {

        return 0;   //no error
    } else {
        
        return 1;   //error                       
    }
}
