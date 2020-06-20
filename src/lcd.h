#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#endif

#ifndef lcd_address
#define lcd_address 0x3C
#endif

#ifndef OLED_RESET
#define OLED_RESET -1
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void clearLcd();

void setupLcd()
{
    Wire.begin(23, 19);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
    }
    clearLcd();
}

void clearLcd()
{
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
}

void clearAndDisplayLcd()
{
    clearLcd();
    display.display();
}

void printTextToLcd(String text, int fontSize)
{
    clearLcd();
    display.setTextSize(fontSize);

    display.println(text);
    display.display();
}