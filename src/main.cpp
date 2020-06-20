#include <Arduino.h>

#ifndef LCD_H
#define LCD_H
#include "lcd.h"
#endif

const int buttonPin = 13;
const gpio_num_t buttonPinGpio = GPIO_NUM_13;
const int mosfetPin = 32;

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
    if (millis() - lastButtonPressMillis > 5000)
    {
        clearAndDisplayLcd();
        esp_sleep_enable_ext0_wakeup(buttonPinGpio, 0);
        esp_deep_sleep_start();
    }
    else
    {
        printTextToLcd(buttonState ? "OFF" : "FIRING!");
    }
}
