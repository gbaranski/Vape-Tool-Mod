#include <Arduino.h>

#include "heltec.h"

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/,
               true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  pinMode(27, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  adcAttachPin(34);
  analogSetClockDiv(255);
}

double analogReadToVolts(int readValue) {
  double volts;
  volts = readValue * 1.7 / 1000;
  return volts;
}
double getWatts(double resistance, double voltage) {
  return voltage * voltage / resistance;
}

void loop() {
  bool buttonState = digitalRead(13);
  double resistance = 0.22;
  uint16_t rawVoltage = analogRead(34);
  double voltage = analogReadToVolts(rawVoltage);
  digitalWrite(27, !buttonState);
  digitalWrite(LED, !buttonState);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, String(voltage) + "V");
  Heltec.display->drawString(0, 8, String(resistance) + "OHM");
  Heltec.display->drawString(0, 16,
                             String(getWatts(resistance, voltage)) + "W");
  Heltec.display->drawString(0, 24, String(buttonState));
  Heltec.display->drawString(0, 32, String(millis()));
  Heltec.display->display();
}
