/*
 LEDC Software Fade
 This example shows how to software fade LED
 using the ledcWrite function.
 Code adapted from original Arduino Fade example:
 https://www.arduino.cc/en/Tutorial/Fade
 This example code is in the public domain.
 */

#include <Arduino.h>

const int buttonPin = 13;
const int mosfetPin = 32;

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
void setup()
{
    pinMode(mosfetPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    Wire.begin(23, 19);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
    }
    delay(1000);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.println("    ezz");
    display.display();
}

void loop()
{
    bool buttonState = digitalRead(buttonPin);
    digitalWrite(mosfetPin, !buttonState);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.clearDisplay();
    display.println(buttonState);
    display.display();
}