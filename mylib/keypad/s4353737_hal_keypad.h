/** 
 *******************************************************************************
 * @file mylib/keypad/s4353737_hal_keypad.h
 * @author George Todorovic - 43537370
 * @date 20042020
 * @brief header files for keypad driver
 * REFERENCE: csse3010_mylib_hal_keypad.pdf 
 *******************************************************************************
*/

#ifndef   S4353737_HAL_MYLIB_CONFIGURE_INC
#include "s4353737_hal_mylib_configure.h"

#ifndef S4353737_HAL_KEYPAD_COL1PIN
#define S4353737_HAL_KEYPAD_COL1PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_COL2PIN
#define S4353737_HAL_KEYPAD_COL2PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_COL3PIN
#define S4353737_HAL_KEYPAD_COL3PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_COL4PIN
#define S4353737_HAL_KEYPAD_COL4PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_COL1PINPORT     
#define S4353737_HAL_KEYPAD_COL1PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_COL2PINPORT     
#define S4353737_HAL_KEYPAD_COL2PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_COL3PINPORT     
#define S4353737_HAL_KEYPAD_COL3PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_COL4PINPORT     
#define S4353737_HAL_KEYPAD_COL4PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_COL1PINCLK
#define S4353737_HAL_KEYPAD_COL1PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_COL2PINCLK
#define S4353737_HAL_KEYPAD_COL2PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_COL3PINCLK
#define S4353737_HAL_KEYPAD_COL3PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_COL4PINCLK
#define S4353737_HAL_KEYPAD_COL4PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_ROW1PIN
#define S4353737_HAL_KEYPAD_ROW1PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_ROW2PIN
#define S4353737_HAL_KEYPAD_ROW2PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_ROW3PIN
#define S4353737_HAL_KEYPAD_ROW3PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_ROW4PIN
#define S4353737_HAL_KEYPAD_ROW4PIN         BRD_D0_PIN
#endif

#ifndef S4353737_HAL_KEYPAD_ROW1PINPORT     
#define S4353737_HAL_KEYPAD_ROW1PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_ROW2PINPORT     
#define S4353737_HAL_KEYPAD_ROW2PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_ROW3PINPORT     
#define S4353737_HAL_KEYPAD_ROW3PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_ROW4PINPORT     
#define S4353737_HAL_KEYPAD_ROW4PINPORT     BRD_D0_GPIO_PORT
#endif

#ifndef S4353737_HAL_KEYPAD_ROW1PINCLK
#define S4353737_HAL_KEYPAD_ROW1PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_ROW2PINCLK
#define S4353737_HAL_KEYPAD_ROW2PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_ROW3PINCLK
#define S4353737_HAL_KEYPAD_ROW3PINCLK      __BRD_D0_GPIO_CLK()
#endif

#ifndef S4353737_HAL_KEYPAD_ROW4PINCLK
#define S4353737_HAL_KEYPAD_ROW4PINCLK      __BRD_D0_GPIO_CLK()
#endif

int KeypadStatus;
u_int16_t KeypadValue;
unsigned short lower;
unsigned short upper;

void s4353737_hal_keypad_init();
void s4357337_hal_keypad_deinit();
void s4353737_hal_keypad_fsmprocessing();
void keypad_gpio_init();
void keypad_writecol(int colval);
u_int16_t keypad_readrow();
int s4353737_hal_keypad_read_status();
unsigned char s4353737_keypad_read_key();
unsigned char s4353737_hal_keypad_read_ascii();
void change_state();

#endif
