#include <Arduino.h>

#include "kick.h"

int HV_SENSE = 36;
int FAULT = 27;
int DONE = 26;
int CHRG = 25;

hw_timer_t * timer = NULL; 

/*
 * Creates a pulse for a given duration.
 *
 * @param duration the duration of the pulse in microseconds.
 */
void oneShotPulse(int gpioPin, int duration) {
  timerWrite(timer, 0);
  timerAlarmWrite(timer, duration, false); 
  timerAlarmEnable(timer);

  digitalWrite(gpioPin, HIGH);
}

/*
 * Helper function that ends a pulse.
 */
void IRAM_ATTR stopPulse() { //I'm not sure how to fix this, I just set both pins to low for now
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
}

int HVmeasure(int HV_SENSE){
  return analogRead(HV_SENSE);
}

bool ChargeCap(int CHRG, int FAULT, int DONE, int HV_SENSE){
  digitalWrite(CHRG, HIGH);
  Serial.println("ChargeHigh");
  while (digitalRead(DONE) == HIGH){
    //Serial.println(HVmeasure(HV_SENSE));
    if (digitalRead(FAULT) == LOW){
      Serial.println("FAIL");
      digitalWrite(CHRG,LOW);
      return false;
    }
  }
  digitalWrite(CHRG, LOW);
  return true;
}