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

#ifndef IO_H
#define IO_H
#include "IO.h"
#endif

#ifndef WIFISERVER_H
#define WIIFSERVER_H
#include "wifiserver.h"
#endif

#define batteryCheckInterval 60000 // check battery voltage every minute

unsigned long lastButtonPressMillis = 0;
unsigned long lastBatteryVoltageCheck = 0;
double batteryVoltage = 0;
bool checkSleepLcd();
void goSleep();

void setup()
{
    Serial.begin(9600);
    Serial.println("hello");
    pinMode(buttonPin, INPUT_PULLUP);
    setupLcd();
    setupIO();
    // setupWifiAndServer();
    batteryVoltage = getBatteryVoltage();
}

void loop()
{
    bool buttonState = digitalRead(buttonPin);
    if (millis() - lastBatteryVoltageCheck > batteryCheckInterval)
    {
        Serial.println("Retreiving battery voltage");
        batteryVoltage = getBatteryVoltage();
        lastBatteryVoltageCheck = millis();
    }

    if (!checkSleepLcd())
    {

        String screenData;
        screenData += "\n";
        screenData += buttonState ? "OFF" : "ON!";
        screenData += "\n";
        screenData += String(getPwm());
        screenData += "\n";
        screenData += formatBatteryVoltage(batteryVoltage);
        screenData += "\n";

        printTextToLcd(screenData, 1);
    }
    else
    {
        goSleep();
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
