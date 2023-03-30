/**************************************************************************/
/*!
  @file Adafruit_PCD8544.cpp

  @mainpage Adafruit PCD8544 Nokia 5110 LCD Library

  @section intro Introduction

  This is a library for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

  These displays use SPI to communicate, 4 or 5 pins are required to
  interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  @section author Author

  Written by Limor Fried/Ladyada  for Adafruit Industries.

  @section license License

  BSD license, check license.txt for more information
  All text above, and the splash screen below must be included in any
  redistribution

  Modified 30.3.2023. by Soldered for use in Soldered Nokia 5110 LCD Arduino Library

 */
/**************************************************************************/

#include "Adafruit_PCD8544.h"
#include "Arduino.h"
#include <stdlib.h>

/** the memory buffer for the LCD */
uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xfc,
    0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0xc3, 0xe1, 0xe0, 0xc1, 0xc1, 0x83, 0x87, 0x07, 0x0f, 0x0f,
    0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x02, 0x0f, 0x1f,
    0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf1, 0xf1, 0xe1, 0xe1, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x83, 0x87, 0x8f, 0x0f, 0x1f, 0x1f,
    0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0x40, 0x01, 0x01, 0x03, 0x03, 0x07, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e,
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xf0, 0xe0, 0xc1, 0xc1, 0x83, 0x83, 0x07, 0x87,
    0xc3, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x16, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x0f,
    0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*!
  @brief Update the bounding box for partial updates
  @param xmin left
  @param ymin bottom
  @param xmax right
  @param ymax top
 */
void Adafruit_PCD8544::updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax)
{
    xUpdateMin = min(xUpdateMin, xmin);
    xUpdateMax = max(xUpdateMax, xmax);
    yUpdateMin = min(yUpdateMin, ymin);
    yUpdateMax = max(yUpdateMax, ymax);
}

/*!
  @brief Constructor for software SPI with explicit CS pin
  @param sclk_pin SCLK pin
  @param din_pin  DIN pin
  @param dc_pin   DC pin
  @param cs_pin   CS pin
  @param rst_pin  RST pin
 */
Adafruit_PCD8544::Adafruit_PCD8544(int8_t sclk_pin, int8_t din_pin, int8_t dc_pin, int8_t cs_pin, int8_t rst_pin)
    : Adafruit_GFX(LCDWIDTH, LCDHEIGHT)
{
    spi_dev = new Adafruit_SPIDevice(cs_pin, sclk_pin, -1, din_pin,
                                     4000000); // 4mhz max speed

    _dcpin = dc_pin;
    _rstpin = rst_pin;
}

/*!
  @brief Constructor for hardware SPI based on hardware controlled SCK (SCLK)
  and MOSI (DIN) pins. CS is still controlled by any IO pin. NOTE: MISO and SS
  will be set as an input and output respectively, so be careful sharing those
  pins!
  @param dc_pin   DC pin
  @param cs_pin   CS pin
  @param rst_pin  RST pin
  @param theSPI   Pointer to SPIClass device for hardware SPI
 */
Adafruit_PCD8544::Adafruit_PCD8544(int8_t dc_pin, int8_t cs_pin, int8_t rst_pin, SPIClass *theSPI)
    : Adafruit_GFX(LCDWIDTH, LCDHEIGHT)
{
    spi_dev = new Adafruit_SPIDevice(cs_pin, 4000000, SPI_BITORDER_MSBFIRST, SPI_MODE0, theSPI);

    _dcpin = dc_pin;
    _rstpin = rst_pin;
}

/*!
  @brief The most basic function, set a single pixel, in the main buffer
  @param x     x coord
  @param y     y coord
  @param color pixel color (BLACK or WHITE)
 */
void Adafruit_PCD8544::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    setPixel(x, y, color, pcd8544_buffer);
}

/*!
  @brief The most basic function, set a single pixel
  @param x     x coord
  @param y     y coord
  @param color pixel color (BLACK or WHITE)
  @param buffer The framebuffer to set the pixel in
 */
void Adafruit_PCD8544::setPixel(int16_t x, int16_t y, bool color, uint8_t *buffer)
{
    if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
        return;

    int16_t t;
    switch (rotation)
    {
    case 1:
        t = x;
        x = y;
        y = LCDHEIGHT - 1 - t;
        break;
    case 2:
        x = LCDWIDTH - 1 - x;
        y = LCDHEIGHT - 1 - y;
        break;
    case 3:
        t = x;
        x = LCDWIDTH - 1 - y;
        y = t;
        break;
    }
    updateBoundingBox(x, y, x, y);

    // x is which column
    if (color)
        buffer[x + (y / 8) * LCDWIDTH] |= 1 << (y % 8);
    else
        buffer[x + (y / 8) * LCDWIDTH] &= ~(1 << (y % 8));
}

/*!
  @brief The most basic function, get a single pixel
  @param  x x coord
  @param  y y coord
  @param buffer The framebuffer to get the pixel from
  @return   color of the pixel at x,y
 */
bool Adafruit_PCD8544::getPixel(int16_t x, int16_t y, uint8_t *buffer)
{
    if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
        return false;

    int16_t t;
    switch (rotation)
    {
    case 1:
        t = x;
        x = y;
        y = LCDHEIGHT - 1 - t;
        break;
    case 2:
        x = LCDWIDTH - 1 - x;
        y = LCDHEIGHT - 1 - y;
        break;
    case 3:
        t = x;
        x = LCDWIDTH - 1 - y;
        y = t;
        break;
    }

    return (buffer[x + (y / 8) * LCDWIDTH] >> (y % 8)) & 0x1;
}

/*!
  @brief Initialize the display. Set bias and contrast, enter normal mode.
 */
void Adafruit_PCD8544::initDisplay()
{

    // toggle RST low to reset
    if (_rstpin >= 0)
    {
        pinMode(_rstpin, OUTPUT);
        digitalWrite(_rstpin, LOW);
        delay(1); // 1 ns minimum
        digitalWrite(_rstpin, HIGH);
    }

    setBias(_bias);
    setContrast(_contrast);

    // normal mode
    command(PCD8544_FUNCTIONSET);

    // Set display to Normal
    command(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

/*!
  @brief Set up SPI, initialize the display, set the bounding box
  @param contrast Initial contrast value
  @param bias     Initial bias value
  @returns True on initialization success
 */
bool Adafruit_PCD8544::begin(uint8_t contrast, uint8_t bias)
{

    if (!spi_dev->begin())
    {
        return false;
    }

    // Set common pin outputs.
    pinMode(_dcpin, OUTPUT);
    if (_rstpin >= 0)
        pinMode(_rstpin, OUTPUT);

    _bias = bias;
    _contrast = contrast;
    _reinit_interval = 0;
    _display_count = 0;
    initDisplay();

    // initial display line
    // set page address
    // set column address
    // write display data

    // set up a bounding box for screen updates

    updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
    // Push out pcd8544_buffer to the Display (will show the AFI logo)
    display();

    return true;
}

/*!
  @brief  Send a command to the LCD
  @param c Command byte
 */
void Adafruit_PCD8544::command(uint8_t c)
{
    digitalWrite(_dcpin, LOW);
    spi_dev->write(&c, 1);
}

/*!
  @brief  Send data to the LCD
  @param c Data byte
 */
void Adafruit_PCD8544::data(uint8_t c)
{
    digitalWrite(_dcpin, HIGH);
    spi_dev->write(&c, 1);
}

/*!
  @brief  Set the contrast level
  @param val Contrast value
 */
void Adafruit_PCD8544::setContrast(uint8_t val)
{
    if (val > 0x7f)
    {
        val = 0x7f;
    }
    _contrast = val;
    command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    command(PCD8544_SETVOP | val);
    command(PCD8544_FUNCTIONSET);
}

/*!
  @brief  Set the bias level
  @param val Bias value
 */
void Adafruit_PCD8544::setBias(uint8_t val)
{
    if (val > 0x07)
    {
        val = 0x07;
    }
    _bias = val;
    command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
    command(PCD8544_SETBIAS | val);
    command(PCD8544_FUNCTIONSET);
}

/*!
  @brief  Get the bias level
  @return Bias value
 */
uint8_t Adafruit_PCD8544::getBias()
{
    return _bias;
}

/*!
  @brief  Get the contrast level
  @return Contrast value
 */
uint8_t Adafruit_PCD8544::getContrast()
{
    return _contrast;
}

/*!
  @brief  Set the interval for reinitializing the display
  @param val Reinit after this many calls to display()
 */
void Adafruit_PCD8544::setReinitInterval(uint8_t val)
{
    _reinit_interval = val;
}

/*!
  @brief  Get the reinit interval
  @return Reinit interval
 */
uint8_t Adafruit_PCD8544::getReinitInterval()
{
    return _reinit_interval;
}

/*!
  @brief Update the display
 */
void Adafruit_PCD8544::display(void)
{
    if (_reinit_interval)
    {
        _display_count++;
        if (_display_count >= _reinit_interval)
        {
            _display_count = 0;
            initDisplay();
        }
    }

    for (uint8_t page = (yUpdateMin / 8); page < (yUpdateMax / 8) + 1; page++)
    {
        command(PCD8544_SETYADDR | page);

        uint8_t startcol = xUpdateMin;
        uint8_t endcol = xUpdateMax;

        command(PCD8544_SETXADDR | startcol);

        digitalWrite(_dcpin, HIGH);
        spi_dev->write(pcd8544_buffer + (LCDWIDTH * page) + startcol, endcol - startcol + 1);
    }

    command(PCD8544_SETYADDR); // no idea why this is necessary but it is to
                               // finish the last byte?

    xUpdateMin = LCDWIDTH - 1;
    xUpdateMax = 0;
    yUpdateMin = LCDHEIGHT - 1;
    yUpdateMax = 0;
}

/*!
  @brief Clear the entire display
 */
void Adafruit_PCD8544::clearDisplay(void)
{
    memset(pcd8544_buffer, 0, LCDWIDTH * LCDHEIGHT / 8);
    updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
    cursor_y = cursor_x = 0;
}

/*!
  @brief Invert the entire display
  @param i True to invert the display, false to keep it uninverted
 */
void Adafruit_PCD8544::invertDisplay(bool i)
{
    command(PCD8544_FUNCTIONSET);
    command(PCD8544_DISPLAYCONTROL | (i ? PCD8544_DISPLAYINVERTED : PCD8544_DISPLAYNORMAL));
}

/*!
  @brief Scroll the display by creating a new buffer and moving each pixel
  @param xpixels The x offset, can be negative to scroll backwards
  @param ypixels The y offset, can be negative to scroll updwards
 */
void Adafruit_PCD8544::scroll(int8_t xpixels, int8_t ypixels)
{
    uint8_t new_buffer[LCDWIDTH * LCDHEIGHT / 8];
    memset(new_buffer, 0, LCDWIDTH * LCDHEIGHT / 8);

    // negative pixels wrap around
    while (ypixels < 0)
    {
        ypixels += height();
    }
    ypixels %= height();
    while (xpixels < 0)
    {
        xpixels += width();
    }
    xpixels %= width();

    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {
            if (getPixel(x, y, pcd8544_buffer))
            {
                int new_x = (x + xpixels) % _width;
                int new_y = (y + ypixels) % _height;
                setPixel(new_x, new_y, true, new_buffer);
            }
        }
    }
    memcpy(pcd8544_buffer, new_buffer, LCDWIDTH * LCDHEIGHT / 8);
    updateBoundingBox(0, 0, LCDWIDTH - 1, LCDHEIGHT - 1);
}
