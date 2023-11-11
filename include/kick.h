#ifndef KICK_H
#define KICK_H

#include <Arduino.h>

void oneShotPulse(int gpioPin, int duration);
void IRAM_ATTR stopPulse();
bool ChargeCap(int CHRG, int FAULT, int DONE, int HV_SENSE);

#endif