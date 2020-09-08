#include <Arduino.h>

#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "config.h"
#include "gpio.h"

double analogReadToVolts(int readValue) {
  double volts;
  volts = readValue * ADC_CONV_FACTOR / 1000;
  return volts;
}

double getWatts(double resistance, double voltage) {
  int newVoltage = voltage * getDutyPercent();
  return newVoltage * newVoltage / resistance;
}

#endif