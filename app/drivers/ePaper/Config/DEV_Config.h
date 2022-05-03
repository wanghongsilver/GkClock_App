/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
* 1.add:
*   UBYTE\UWORD\UDOUBLE
* 2.Change:
*   EPD_RST -> EPD_RST_PIN
*   EPD_DC -> EPD_DC_PIN
*   EPD_CS -> EPD_CS_PIN
*   EPD_BUSY -> EPD_BUSY_PIN
* 3.Remote:
*   EPD_RST_1\EPD_RST_0
*   EPD_DC_1\EPD_DC_0
*   EPD_CS_1\EPD_CS_0
*   EPD_BUSY_1\EPD_BUSY_0
* 3.add:
*   #define DEV_Digital_Write(_pin, _value) bcm2835_gpio_write(_pin, _value)
*   #define DEV_Digital_Read(_pin) bcm2835_gpio_lev(_pin)
*   #define DEV_SPI_WriteByte(__value) bcm2835_spi_transfer(__value)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "gpio.h"

#include <stdint.h>
#include <stdio.h>

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * e-Paper GPIO
**/
#define EPD_RST_PIN     GPIO_ID_PIN(2)
#define EPD_DC_PIN      GPIO_ID_PIN(0)
#define EPD_CS_PIN      GPIO_ID_PIN(15)
#define EPD_BUSY_PIN    GPIO_ID_PIN(4)

#define EPD_SCLK_PIN GPIO_ID_PIN(14)
#define EPD_SDIN_PIN GPIO_ID_PIN(13)

//-----------------OLED端口定义----------------

#define EPD_SCLK_Clr() GPIO_OUTPUT(EPD_SCLK_PIN, 0) // CLK
#define EPD_SCLK_Set() GPIO_OUTPUT(EPD_SCLK_PIN, 1)

#define EPD_SDIN_Clr() GPIO_OUTPUT(EPD_SDIN_PIN, 0) // DIN
#define EPD_SDIN_Set() GPIO_OUTPUT(EPD_SDIN_PIN, 1)

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) GPIO_OUTPUT(_pin, _value)
#define DEV_Digital_Read(_pin)          GPIO_INPUT_GET(_pin)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) DEV_User_Delayms(__xms);

void DEV_SPI_WriteByte(UBYTE value);

int DEV_Module_Init(void);
void DEV_Module_Exit(void);
void DEV_User_Delayms(uint32 ms);
#endif
