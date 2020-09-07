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

void loop() {
  bool buttonState = digitalRead(13);
  digitalWrite(27, !buttonState);
  digitalWrite(LED, !buttonState);
  Heltec.display->clear();
  Heltec.display->drawString(0, 10,
                             String(analogReadToVolts(analogRead(34))) + "V");
  Heltec.display->display();
}
