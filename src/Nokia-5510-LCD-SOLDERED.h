/**
 **************************************************
 *
 * @file        Nokia-5510-LCD-SOLDERED.h
 * @brief       Header file Nokia 5510 LCD library
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Robert @ soldered.com
 ***************************************************/

#ifndef __NOKIA_5510_LCD_SOLDERED__
#define __NOKIA_5510_LCD_SOLDERED__

#include "Arduino.h"
#include "libs/Adafruit_PCD8544_Nokia_5110_LCD_library/Adafruit_PCD8544.h"

class LCD_5510 : public Adafruit_PCD8544
{
  public:
    LCD_5510(int8_t sclk_pin, int8_t din_pin, int8_t dc_pin, int8_t cs_pin, int8_t rst_pin) : Adafruit_PCD8544(sclk_pin, din_pin, dc_pin, cs_pin, rst_pin)
    {

    }
    LCD_5510(int8_t dc_pin, int8_t cs_pin, int8_t rst_pin, SPIClass *theSPI = &SPI) : Adafruit_PCD8544(dc_pin, cs_pin, rst_pin)
    {

    }
};

#endif
