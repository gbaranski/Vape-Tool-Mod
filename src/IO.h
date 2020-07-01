#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef ANALOGWRITE_H
#define ANALOGWRITE_H
#include <analogWrite.h>
#endif

#ifndef CONFIG_H
#define CONFIG_H
#include "config.h"
#endif

double getBatteryVoltage()
{
    int raw = analogRead(34);
    return raw * 1.7 / 1000;
}

String formatBatteryVoltage(double batteryVoltage)
{
    String batteryVoltageStr = String(batteryVoltage);
    return batteryVoltageStr.substring(0, batteryVoltageStr.length() - 1);
}

uint32_t pwmStrength = 255;


void setupIO()
{
    pinMode(mosfetPin, OUTPUT);
}

void setMosfetHigh()
{
    analogWrite(mosfetPin, pwmStrength);
}

void setMosfetLow()
{
    analogWrite(mosfetPin, 0);
}

void setPwm(uint32_t newValue)
{
    pwmStrength = newValue;
}

uint32_t getPwm()
{
    return pwmStrength;
}