/**
 **************************************************
 *
 * @file        drawBitmap.ino
 * @brief       Drawing a bitmap on the Soldered Nokia 5110 LCD Breakout.
 *
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board according to the diagrams below
 *              -Adjust the contrast value (see contrastTest.ino)
 *
 *              NOTE: This library uses Adafruit GFX functions and is compatible with the Adafruit GFX library!
 *              Learn more about Adafruit GFX: https://learn.adafruit.com/adafruit-gfx-graphics-library
 *
 *              Soldered Nokia 5110 LCD Breakout: solde.red/333272
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert @ soldered.com
 ***************************************************/

// Include the library
#include "Nokia-5510-LCD-SOLDERED.h"

// Set pin defines
// Change this according to your board and the diagrams below
// These are for Dasduino ConnectPlus
#define CLK_PIN  13
#define MOSI_PIN 11
#define DC_PIN   12
#define CS_PIN   10
#define RST_PIN  8

// Set contrast
// To find out the optimal value check contrastTest.ino
#define CONTRAST_VAL 63

/**
 * When declaring the LCD object, you may use Hardware SPI or Software SPI.
 * Hardware SPI is faster but must use certain pins on your Dasduino board.
 */

/**
 * Hardware SPI connecting diagram:
 *
 * Nokia 5110 LCD Breakout      Dasduino Core / Connect / ConnectPlus
 * VCC------------------------->3V3
 * GND------------------------->GND
 * CLK------------------------->13/IO14/IO18
 * MOSI------------------------>11/IO13/IO23
 * DC-------------------------->12/IO4/IO33
 * CS-------------------------->10/IO15/IO5
 * RST------------------------->RST_PIN (set by user)
 * OE-------------------------->3V3
 * LED (Backlight)------------->3V3
 * 
 * The LED Backlight pin may be connected to a GPIO pin to turn the backlight on or off,
 * or even a PWM pin to set the brightness!
 *
 * If you are using hardware SPI, the declaration of the LCD object is:
 * LCD_5510(DC Pin, CS Pin, RST Pin);
 *
 * Note: with Hardware SPI MISO and SS pins aren't used but will still be read
 * and written to during SPI transfer. Be careful when sharing these pins!
 */

/**
 * For software SPI, use any available pins on your Dasduino Board.
 *
 * If you are using software SPI, the declaration of the LCD object is:
 * LCD_5510 display(CLK Pin, MOSI Pin (DIN), DC Pin, CS Pin, RST Pin);
 *
 */

// Create the LCD display object on hardware SPI
LCD_5510 display(DC_PIN, CS_PIN, RST_PIN);

/**
 * To convert an image in bitmap format, use image2cpp:
 * https://javl.github.io/image2cpp/
 *
 * Use Draw Mode "Horizontal - 1 bits per pixel"
 *
 * Upload an 84x48 px image and convert it.
 * Copy and paste the generated code here
 */

const uint8_t image_w = 84;
const uint8_t image_h = 48;
static const unsigned char PROGMEM image_bmp[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0x3F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x80, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
    0x8F, 0x07, 0xC3, 0xE1, 0xE7, 0xC1, 0xE0, 0x20, 0x70, 0x10, 0x70, 0x9D, 0x8F, 0x81, 0x80, 0xE7, 0xC0, 0x60, 0x20,
    0x30, 0x10, 0x10, 0x98, 0x7F, 0x1F, 0x8C, 0x67, 0xC6, 0x23, 0xE3, 0x11, 0xF1, 0x10, 0x98, 0x3F, 0x1F, 0x9E, 0x67,
    0xC6, 0x23, 0xE3, 0x11, 0xF3, 0x80, 0x8E, 0x0F, 0x83, 0x1E, 0x27, 0xC7, 0x20, 0x63, 0x10, 0x33, 0x80, 0x83, 0x0F,
    0xC1, 0x1E, 0x27, 0xC7, 0x20, 0x60, 0x30, 0x33, 0x80, 0xC1, 0xCF, 0xF0, 0x9E, 0x67, 0xC6, 0x23, 0xE0, 0x71, 0xF3,
    0x80, 0xF0, 0xCF, 0xB8, 0x8C, 0x63, 0xC6, 0x23, 0xE2, 0x31, 0xF3, 0x80, 0x1D, 0xCF, 0x01, 0x80, 0x70, 0x40, 0x60,
    0x23, 0x30, 0x10, 0x10, 0x07, 0x0F, 0x83, 0xC0, 0xF8, 0x40, 0xE0, 0x23, 0x10, 0x10, 0x30, 0x80, 0x0F, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF8,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// For remembering the current rotation setting
int currentRotation = 0;
void setup()
{
    Serial.begin(115200); // For debugging

    // Check if we can initialize the display correctly
    if (!display.begin())
    {
        Serial.println("Can't initialize display!");
        // Go to infinite loop
        while (true)
        {
            delay(100);
        }
    }

    // Set the display's contrast, this is important
    display.setContrast(CONTRAST_VAL);

    // Show the splash screen image and wait a bit
    display.display();
    delay(3000);
}

void loop()
{
    // Clear the display's buffer
    // This doesn't clear the display fully before we call display.display(), just the memory buffer
    display.clearDisplay();

    // Draw the generated bitmap
    // Arguments are: x start position, y start position, the bitmap in memory, image width and height and color
    display.drawBitmap(0, 0, image_bmp, image_w, image_h, BLACK);

    // Show the image and wait 5 seconds
    display.display();
    delay(5000);

    // Rotate the image 180 degeres each time
    currentRotation += 2;
    if (currentRotation == 4)
        currentRotation = 0;
    display.setRotation(currentRotation);
}
