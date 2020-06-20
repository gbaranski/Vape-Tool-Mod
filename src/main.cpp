#include <Arduino.h>

#ifndef LCD_H
#define LCD_H
#include "lcd.h"
#endif

const int buttonPin = 13;
const gpio_num_t buttonPinGpio = GPIO_NUM_13;
const int mosfetPin = 32;
const int deepSleepTime = 5000;

unsigned long lastButtonPressMillis = 0;
void checkSleepLcd(bool buttonState);

void setup()
{
    pinMode(mosfetPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    setupLcd();
}

void loop()
{
    bool buttonState = digitalRead(buttonPin);
    checkSleepLcd(buttonState);
    if (!buttonState)
    {
        lastButtonPressMillis = millis();
    }
    digitalWrite(mosfetPin, !buttonState);
}

void checkSleepLcd(bool buttonState)
{
    if (millis() - lastButtonPressMillis > deepSleepTime)
    {
        clearAndDisplayLcd();
        esp_sleep_enable_ext0_wakeup(buttonPinGpio, LOW); // wake up ESP when button is pressed
        esp_deep_sleep_start();
    }
    else
    {
        printTextToLcd(buttonState ? "OFF" : "FIRING!", 2);
    }
}
