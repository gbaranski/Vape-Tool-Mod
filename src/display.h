#include <Arduino.h>

#ifndef DISPLAY_H
#define DISPLAY_H

#pragma once

#include "gpio.h"
#include "heltec.h"
#include "utils.h"

void goSleep();

void setupDisplay() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/,
               true /*Serial Enable*/);
  Heltec.display->setFont(ArialMT_Plain_10);
}

void displayLoop(double batteryVoltage, double outputVoltage) {
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, String(batteryVoltage) + "V");
  Heltec.display->drawString(0, 16, String(RESISTANCE) + "OHM");
  Heltec.display->drawString(0, 32,
                             String(getWatts(RESISTANCE, outputVoltage)) + "W");

  String outputVoltsString = String(outputVoltage) + "V";
  uint16_t realVoltsWidth = Heltec.display->getStringWidth(outputVoltsString);
  Heltec.display->drawString(128 - realVoltsWidth, 0, outputVoltsString);

  String ampsString = String(getAmps(RESISTANCE, outputVoltage)) + "A";
  uint16_t ampsStringWidth = Heltec.display->getStringWidth(ampsString);
  Heltec.display->drawString(128 - ampsStringWidth, 16, ampsString);

  String dutyPercentageString = getDutyPercentString();
  uint16_t dutyPercentageWidth =
      Heltec.display->getStringWidth(dutyPercentageString);
  Heltec.display->drawString(128 - dutyPercentageWidth, 32,
                             getDutyPercentString());

  Heltec.display->display();

  unsigned long now = millis();

  if (now - lastMosfetButtonPress >= DISPLAY_LIGHT_TIMEOUT &&
      now - lastProgButtonPress >= DISPLAY_LIGHT_TIMEOUT) {
    Heltec.display->setBrightness(DISPLAY_LIGHT_BRIGHTNESS);
    if (now - lastMosfetButtonPress >= DISPLAY_DEEP_TIMEOUT &&
        now - lastProgButtonPress >= DISPLAY_DEEP_TIMEOUT) {
      goSleep();
    }
  } else {
    Heltec.display->setBrightness(DISPLAY_NORMAL_BRIGHTNESS);
  }
}

void clearDisplay() {
  Heltec.display->clear();
  Heltec.display->display();
}

void goSleep() {
  clearDisplay();
  esp_sleep_enable_ext0_wakeup(BUTTON_GPIO, LOW);
  esp_deep_sleep_start();
}

#endif