/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2019-07-08
* | Info        :   Basic version
*
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

//#include "Debug.h"

// NOTE: This file originally targeted a Raspberry Pi (Linux SBC) using
// bcm2835/wiringPi/DEV_LIB. None of those exist on the Pico, so the pins
// below now match your actual wiring. Arduino/SPI headers are intentionally
// NOT included here - this header is shared with plain-C files like
// LCD_1in69.c, which can't parse C++-only headers (namespaces, classes,
// etc). SPI.h is included directly in the .ino instead.

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>



/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

// Actual Pico GPIO wiring (BCM pin numbers from the Pi demo do NOT apply here)
#define LCD_CS   17   // CS
#define LCD_RST  13   // RST
#define LCD_DC   22   // DC
#define LCD_BL   21   // BL
#define LCD_DIN  19   // MOSI - Pico's default hardware SPI0 MOSI pin
#define LCD_CLK  18   // SCK  - Pico's default hardware SPI0 SCK pin



//LCD
#define LCD_CS_0		DEV_Digital_Write(LCD_CS,0)
#define LCD_CS_1		DEV_Digital_Write(LCD_CS,1)

#define LCD_RST_0		DEV_Digital_Write(LCD_RST,0)
#define LCD_RST_1		DEV_Digital_Write(LCD_RST,1)

#define LCD_DC_0		DEV_Digital_Write(LCD_DC,0)
#define LCD_DC_1		DEV_Digital_Write(LCD_DC,1)

#define LCD_BL_0		DEV_Digital_Write(LCD_BL,0)
#define LCD_BL_1		DEV_Digital_Write(LCD_BL,1)

// (Removed: KEY_* pin defines from Waveshare's button-equipped Pico boards.
// Your bare 1.69" module has no buttons, and some of those pin numbers
// collided with pins you're actually using - e.g. KEY_DOWN_PIN was 19,
// the same pin as your DIN line.)

#define LCD_SetBacklight(Value) DEV_SetBacklight(Value)

/*------------------------------------------------------------------------------------------------------*/
// extern "C" is required here: these functions are defined in DEV_Config.c,
// which is compiled as plain C, but this header is also included from your
// .ino, which is compiled as C++. Without this, the linker looks for a
// mangled C++ symbol name that doesn't exist and you'll get "undefined
// reference" errors at link time.
#ifdef __cplusplus
extern "C" {
#endif

UBYTE DEV_ModuleInit(void);
void DEV_ModuleExit(void);

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode);
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);
void DEV_Delay_ms(UDOUBLE xms);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len);
void DEV_SetBacklight(UWORD Value);

#ifdef __cplusplus
}
#endif
#endif
