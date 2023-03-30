/**
 **************************************************
 *
 * @file        Print_Text.ino
 * @brief       Printing text example for Soldered Nokia 5110 LCD Breakout.
 *              This example demonstrates basic text printing functions.
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

    // Set the default text size (6x8), text color black and set the cursor to the top left of the screen
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 0);

    // Write hello world and show it
    display.write("Hello world!");
    display.display();

    // Wait a bit
    delay(3000);

    // Write chars from 0 to 168
    display.clearDisplay();
    display.setCursor(0, 0);
    for (uint8_t i = 0; i < 168; i++)
    {
        // Skip newline character
        if (i == '\n')
            continue;
        display.write(i);
    }
    display.display();
}

void loop()
{
    // Do nothing
    delay(1000);
}
