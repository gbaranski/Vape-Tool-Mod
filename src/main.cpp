#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef LCD_H
#define LCD_H
#include "lcd.h"
#endif

#ifndef CONFIG_H
#define CONFIG_H
#include "config.h"
#endif

#ifndef OUTPUT_H
#define OUTPUT_H
#include "output.h"
#endif

#ifndef WIFISERVER_H
#define WIIFSERVER_H
#include "wifiserver.h"
#endif

unsigned long lastButtonPressMillis = 0;
bool checkSleepLcd();
void goSleep();

void setup()
{
    Serial.begin(9600);
    Serial.println("hello");
    pinMode(buttonPin, INPUT_PULLUP);
    setupLcd();
    setupWifiAndServer();
}

void loop()
{
    bool buttonState = digitalRead(buttonPin);
    if (!checkSleepLcd())
    {
        String screenData;
        screenData += "\n";
        screenData += buttonState ? "OFF" : "ON!";
        screenData += "\n";
        screenData += String(getPwm());
        printTextToLcd(screenData, 1);
    }
    else
    {
        // goSleep();
    }

    if (!buttonState)
    {
        lastButtonPressMillis = millis();
        setMosfetHigh();
    }
    else
    {

        setMosfetLow();
    }
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
