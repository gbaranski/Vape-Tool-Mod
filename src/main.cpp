#include <Arduino.h>

#ifndef LCD_H
#define LCD_H
#include "lcd.h"
#endif

#ifndef WIFISERVER_H
#define WIIFSERVER_H
#include "wifiserver.h"
#endif

const int buttonPin = 13;
const gpio_num_t buttonPinGpio = GPIO_NUM_13;
const int mosfetPin = 32;
const int deepSleepTime = 5000;

unsigned long lastButtonPressMillis = 0;
bool checkSleepLcd();
void goSleep();

void setup()
{
    Serial.begin(9600);
    Serial.println("hello");
    pinMode(mosfetPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    setupLcd();
    setupWifiAndServer();
}

void loop()
{
    bool buttonState = digitalRead(buttonPin);
    if (!checkSleepLcd())
    {
        printTextToLcd(buttonState ? "OFF" : "FIRING!", 2);
    }
    else
    {
        // goSleep();
    }

    if (!buttonState)
    {
        lastButtonPressMillis = millis();
    }
    digitalWrite(mosfetPin, !buttonState);
}

bool checkSleepLcd()
{
    return millis() - lastButtonPressMillis > deepSleepTime;
}

void goSleep()
{
    clearAndDisplayLcd();
    esp_sleep_enable_ext0_wakeup(buttonPinGpio, LOW); // wake up ESP when button is pressed
    esp_deep_sleep_start();
}
