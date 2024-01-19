#ifndef KICK_H
#define KICK_H

const int HV_SENSE = 36;
const int FAULT = 27;
const int DONE = 26;
const int CHRG = 25;

void oneShotPulse(int gpioPin, int duration);
void IRAM_ATTR stopPulse();
bool ChargeCap(int CHRG, int FAULT, int DONE, int HV_SENSE);

#endif