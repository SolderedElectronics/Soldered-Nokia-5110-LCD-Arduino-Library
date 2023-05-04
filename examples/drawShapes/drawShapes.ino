/**
 **************************************************
 *
 * @file        drawShapes.ino
 * @brief       Drawing Shapes example for Soldered Nokia 5110 LCD Breakout.
 *              This example demonstrates drawing different shapes.
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
#define CLK_PIN  18
#define MOSI_PIN 23
#define DC_PIN   33
#define CS_PIN   5
#define RST_PIN  32

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
    // Depending on the current rotation, draw shapes either horizontally or vertically
    // Default rotation is 0
    // 1 is 90 degrees
    // 2 is 180 degrees
    // 3 is 270 degrees
    if (currentRotation == 0 || currentRotation == 2)
    {
        drawShapesOnHorizontalScreen();
    }
    else if (currentRotation == 1 || currentRotation == 3)
    {
        drawShapesOnVerticalScreen();
    }

    // After drawing wait 5 seconds and change the rotation accordingly
    delay(5000);
    currentRotation++;
    if (currentRotation >= 4)
        currentRotation = 0;
    display.setRotation(currentRotation);
}

// Function for drawing shapes when the screen is in horizontal mode
// (Rotation 0 or 2)
void drawShapesOnHorizontalScreen()
{
    // Clear the display's buffer
    // This doesn't clear the display fully before we call display.display(), just the memory buffer
    display.clearDisplay();

    // Drawing individual pixels
    // Three pixels in upper left corner
    display.drawPixel(3, 2, BLACK);
    display.drawPixel(5, 2, BLACK);
    display.drawPixel(7, 2, BLACK);

    // Draw horizontal line
    display.drawLine(3, 4, 81, 4, BLACK);

    // Let's draw some shapes!
    // For hollow shapes use draw___ functions
    // For filled shapes, use fill___ functions

    // Draw a filled square
    display.fillRect(3, 8, 23, 23, BLACK);

    // Draw a filled circle
    display.fillCircle(42, 19, 11, BLACK);

    // Draw a hollow triangle
    display.drawTriangle(58, 31, 81, 31, 70, 8, BLACK);

    // Draw a rounded rectangle
    display.drawRoundRect(3, 34, 23, 12, 5, BLACK);

    // Draw three vertical lines fast
    // (This function is optimized and will be faster than drawLine)
    display.drawFastVLine(59, 33, 13, BLACK);
    display.drawFastVLine(70, 33, 13, BLACK);
    display.drawFastVLine(81, 33, 13, BLACK);

    // Draw three horizontal lines fast
    // (This function is optimized and will be faster than drawLine)
    display.drawFastHLine(32, 34, 20, BLACK);
    display.drawFastHLine(32, 40, 20, BLACK);
    display.drawFastHLine(32, 45, 20, BLACK);

    // Show the display
    display.display();
}

// Function for drawing shapes when the screen is in vertical mode
// (Rotation 1 or 3)
void drawShapesOnVerticalScreen()
{
    // Clear the display's buffer
    // This doesn't clear the display fully before we call display.display(), just the memory buffer
    display.clearDisplay();

    // Drawing individual pixels
    // Three pixels in upper left corner
    display.drawPixel(3, 2, BLACK);
    display.drawPixel(5, 2, BLACK);
    display.drawPixel(7, 2, BLACK);

    // Draw horizontal line
    display.drawLine(3, 4, 45, 4, BLACK);

    // Let's draw some shapes!
    // For hollow shapes use draw___ functions
    // For filled shapes, use fill___ functions

    // Draw a filled square
    display.fillRect(3, 6, 18, 18, BLACK);

    // Draw a filled circle
    display.fillCircle(35, 15, 9, BLACK);

    // Draw a hollow triangle
    display.drawTriangle(3, 81, 27, 81, 15, 62, BLACK);

    // Draw a rounded rectangle
    display.drawRoundRect(3, 27, 42, 15, 5, BLACK);

    // Draw three vertical lines fast
    // (This function is optimized and will be faster than drawLine)
    display.drawFastVLine(29, 62, 19, BLACK);
    display.drawFastVLine(36, 62, 19, BLACK);
    display.drawFastVLine(43, 62, 19, BLACK);

    // Draw three horizontal lines fast
    // (This function is optimized and will be faster than drawLine)
    display.drawFastHLine(4, 46, 40, BLACK);
    display.drawFastHLine(4, 52, 40, BLACK);
    display.drawFastHLine(4, 58, 40, BLACK);

    // Show the display
    display.display();
}