#include <Arduino.h>

#include "config.h"
#include "display.h"
#include "gpio.h"

void setup() {
  setupDisplay();
  setupGpio();
}

void loop() {
  uint16_t rawBatteryVoltage = analogRead(34);
  double batteryVoltage = analogReadToVolts(rawBatteryVoltage);
  double outputVoltage = getRealVoltage(batteryVoltage);

  gpioLoop();
  displayLoop(batteryVoltage, outputVoltage);
}
