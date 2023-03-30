/**
 **************************************************
 *
 * @file        Draw_Shapes.ino
 * @brief       Drawing shapes example for Soldered Nokia 5110 LCD Breakout.
 *              This example demonstrates how to draw shapes on the LCD
 *
 *              Soldered Nokia 5110 LCD Breakout: solde.red/xxxxxx
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Robert @ soldered.com
 ***************************************************/

#include "Nokia-5510-LCD-SOLDERED.h"

/**
 * When declaring the LCD object, you may use Hardware SPI or Software SPI
 * Hardware SPI is faster but must use certain pins on your Dasduino board
 * Note: with Hardware SPI MISO and SS pins aren't used but will still be read
 * and written to during SPI transfer. Be careful when sharing these pins!
 */

/**
 * Hardware SPI
 * Connecting diagram for Dasduino ConnectPlus:
 *
 * Dasduino                 Nokia 5110 LCD Breakout
 * 3V3--------------------->VCC
 * GND--------------------->GND
 * 18---------------------->CLK
 * 23---------------------->MOSI
 * IO33-------------------->DC
 * 5----------------------->CS
 * IO32-------------------->RST
 * 3V3--------------------->OE
 * 3V3--------------------->LED (Backlight)
 *
 * For other boards, change pins CS, MOSI and CLK according to your Hardware SPI pins.
 * For DC and RST you may use any GPIO pins.
 *
 * Declaration is LCD_5510(DC Pin, CS Pin, RST Pin);
 */
// LCD_5510 display = LCD_5510(33, 5, 32);

/**
 * Software SPI
 * Connecting diagram for Dasduino ConnectPlus:
 *
 * Dasduino                 Nokia 5110 LCD Breakout
 * 3V3--------------------->VCC
 * GND--------------------->GND
 * IO25-------------------->CLK
 * IO0--------------------->MOSI
 * IO33-------------------->DC
 * 26---------------------->CS
 * IO32-------------------->RST
 * 3V3--------------------->OE (Output Enable)
 * 3V3--------------------->LED (Backlight)
 *
 * You may change this to any avaiable GPIO pins
 *
 * Declaration is LCD_5510(CLK Pin, MOSI Pin (DIN), DC Pin, CS Pin, RST Pin);
 */
LCD_5510 display = LCD_5510(25, 0, 33, 26, 32);

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
    // Adjust the value until you get a satisfactory result for your particular display
    // Values range from 0 to 127
    display.setContrast(63);

    // Show the splash screen image and wait a bit
    display.display();
    delay(3000);

    // Clear the display's buffer
    // This doesn't clear the display fully before we call display.display(), just the memory buffer
    display.clearDisplay();

    // Let's draw some shapes
    // For hollow shapes use draw___ functions
    // For filled shapes, use fill___ functions

    // Draw horizontal lines
    display.drawLine(3, 4, 81, 4, BLACK);
    display.drawLine(3, 45, 81, 45, BLACK);

    // Draw a filled square
    display.fillRect(3, 13, 23, 23, BLACK);

    // Draw a filled circle
    display.fillCircle(42, 24, 11, BLACK);

    // Draw a hollow triangle
    display.drawTriangle(58, 36, 81, 36, 70, 13, BLACK);

    // Show the display
    display.display();
}

void loop()
{
    // Do nothing
    delay(1000);
}