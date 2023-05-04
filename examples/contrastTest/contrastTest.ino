/**
 **************************************************
 *
 * @file        contrastTest.ino
 * @brief       Find optimal contrast value for your Soldered Nokia 5110 LCD Breakout.
 *
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board according to the diagrams below
 *              -Run the sketch and open serial monitor at 115200 baud to set the contrast
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

void setup()
{
    Serial.begin(115200); // For debugging and communication

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

    // Set the display's contrast to a baseline value
    display.setContrast(60);

    // Show the splash screen image and wait a bit
    display.display();
}

void loop()
{
    // Prompt the user to enter a number
    Serial.println("Send a number from 0 to 127 to use as contrast!");
    while(!Serial.available())
    {
        delay(1);
    }
    // Read the number and check if it's a valid input
    int userInput = Serial.parseInt();
    if(userInput < 0 || userInput > 127)
    {
        Serial.println("Invalid input! Number must be from 0 to 127");
        return;
    }

    // Notify the user and set the contrast
    Serial.print("Number ");
    Serial.print(userInput);
    Serial.println(" entered! Setting contrast...");
    Serial.println();
    display.setContrast(userInput);

    delay(5);
    Serial.print("Contrast set. If the image looks fine, ");
    Serial.print(userInput);
    Serial.println(" is fine to use as your contrast value.");
    Serial.println();
}
