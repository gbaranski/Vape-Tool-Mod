#include <Arduino.h>

#include "config.h"
#include "gpio.h"
#include "heltec.h"
#include "utils.h"

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/,
               true /*Serial Enable*/);
  Heltec.display->setFont(ArialMT_Plain_10);
  setupGpio();
}

void loop() {
  loopGpio();
  uint16_t rawBatteryVoltage = analogRead(34);
  double batteryVoltage = analogReadToVolts(rawBatteryVoltage);
  double outputVoltage = getRealVoltage(batteryVoltage);

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
}
