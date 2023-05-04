/**
 **************************************************
 *
 * @file        printText.ino
 * @brief       Printing text example for Soldered Nokia 5110 LCD Breakout.
 *              This example demonstrates basic text printing functions.
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
#define CLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN 33
#define CS_PIN 5
#define RST_PIN 32

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
 * CLK------------------------->8/IO14/IO18
 * MOSI------------------------>11/IO13/IO23
 * DC-------------------------->12/IO4/IO33
 * CS-------------------------->10/IO15/IO5
 * RST------------------------->9/IO5/IO32
 * OE-------------------------->3V3
 * LED (Backlight)------------->3V3
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
 * LCD_5510(CLK Pin, MOSI Pin (DIN), DC Pin, CS Pin, RST Pin);
 *
 */

// Create the LCD display object on hardware SPI
LCD_5510 display(DC_PIN, CS_PIN, RST_PIN);

// To remember which series of chars we are printing
int indexOfPage = 0;

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

    // Clear the display's buffer
    // This doesn't clear the display fully before we call display.display(), just the memory buffer
    display.clearDisplay();

    // Set the default text size (6x8), text color black and set the cursor to the top left of the screen
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 0);

    // Write hello world and show it
    display.write("Hello world!");
    display.display();

    // Wait a bit
    delay(3000);
}

void loop()
{
    // Clear the display and set the cursor to the start
    display.clearDisplay();
    display.setCursor(0, 0);

    // Write 168 characters
    for (uint8_t i = 0; i < 168; i++)
    {
        // Skip newline character
        if (i == '\n')
            continue;
        
        // Write the character incremented by the current page index
        // This way different characters get written each iteration
        display.write(i + 168*indexOfPage);
    }
    // Show the text on the display
    display.display();

    // Go to next page of chars
    indexOfPage++;
    // If we are at page 10, go back to the start
    if(indexOfPage >= 10) indexOfPage = 0;

    // Wait a bit before printing next series of characters
    delay(3000);
}
