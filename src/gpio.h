#include <Arduino.h>

#ifndef GPIO_H
#define GPIO_H

#pragma once

#include "config.h"

RTC_DATA_ATTR int dutyCounter = 0;

int getDuty();

unsigned long lastProgButtonPress = 0;
unsigned long lastMosfetButtonPress = 0;

void setupGpio() {
  // PROG BUTTON
  pinMode(0, INPUT_PULLUP);
  // BUTTON
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // LED
  pinMode(LED, OUTPUT);
  // BATTERY ADC
  adcAttachPin(BATTERY_PIN);
  analogSetClockDiv(255);
  // MOSFET
  ledcSetup(OUTPUT_CHANNEL, OUTPUT_FREQUENCY, OUTPUT_RESOLUTION);
  ledcAttachPin(OUTPUT_PIN, OUTPUT_CHANNEL);
}

void changeMosfetState(bool state) {
  digitalWrite(LED, state);
  if (state) {
    ledcWrite(OUTPUT_CHANNEL, getDuty());
    lastMosfetButtonPress = millis();
  } else {
    ledcWrite(OUTPUT_CHANNEL, 0);
  }
}

void switchDuty() {
  dutyCounter++;
  if (dutyCounter > 4) {
    dutyCounter = 0;
  }
}

int getDuty() {
  // 4 is amount of max dutyCounter
  double duty = double(dutyCounter) / 4 * 255;
  return ceil(duty);
}

double getDutyPercent() { return double(getDuty()) / 255; }
String getDutyPercentString() {
  return String(int(getDutyPercent() * 100)) + "%";
}

void gpioLoop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  bool progButtonState = digitalRead(0);
  changeMosfetState(!buttonState);

  unsigned long now = millis();

  if (!progButtonState) {
    if (now - lastProgButtonPress >= 500) {
      switchDuty();
      lastProgButtonPress = now;
    }
  }
}

#endif