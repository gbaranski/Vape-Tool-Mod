#include <Arduino.h>

#include "config.h"
#include "gpio.h"
#include "heltec.h"
#include "utils.h"

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/,
               true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_16);
  setupGpio();
}

void loop() {
  loopGpio();
  uint16_t rawVoltage = analogRead(34);
  double voltage = analogReadToVolts(rawVoltage);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, String(voltage) + "V");
  Heltec.display->drawString(0, 16, String(RESISTANCE) + "OHM");
  Heltec.display->drawString(0, 32,
                             String(getWatts(RESISTANCE, voltage)) + "W");
  Heltec.display->drawString(0, 48, getDutyPercentString());
  Heltec.display->display();
}
