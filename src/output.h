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

uint32_t pwmStrength = 255;

void setupOutput()
{
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