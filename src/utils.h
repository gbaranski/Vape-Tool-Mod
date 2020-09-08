#include <Arduino.h>

#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "config.h"
#include "gpio.h"

double analogReadToVolts(int readValue) {
  double volts = readValue * ADC_CONV_FACTOR / 1000;
  return floor(volts * 10) / 10;
}

double getRealVoltage(double voltage) { return voltage * getDutyPercent(); }

double getWatts(double resistance, double voltage) {
  return voltage * voltage / resistance;
}

double getAmps(double resistance, double voltage) {
  return voltage / resistance;
}

#endif