#include <Arduino.h>

#include "kick.h"

hw_timer_t * timer2 = NULL; 

/*
 * Creates a pulse for a given duration.
 *
 * @param duration the duration of the pulse in microseconds.
 */
void oneShotPulse(int gpioPin, int duration) {
  timerWrite(timer2, 0);
  timerAlarmWrite(timer2, duration, false); 
  timerAlarmEnable(timer2);

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