#include <Arduino.h>

#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "config.h"

double analogReadToVolts(int readValue) {
  double volts;
  volts = readValue * ADC_CONV_FACTOR / 1000;
  return volts;
}

double getWatts(double resistance, double voltage) {
  return voltage * voltage / resistance;
}

#endif