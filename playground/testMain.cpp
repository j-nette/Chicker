#include <Arduino.h>
#include "kick.h"

hw_timer_t * timer = NULL; 

//const int GPIO_PIN_KICK = 32; //kicking pin
//const int GPIO_PIN_CHIP = 33; //chipping pin

const int GPIO_PIN_KICK = 2; //kicking pin
const int GPIO_PIN_CHIP = 4; //chipping pin
int gpioPin;

int getPin(int);
void action(int, int);

void setup() {
  Serial.begin(115200);
  pinMode(HV_SENSE, INPUT);
  pinMode(DONE, INPUT);
  pinMode(FAULT, INPUT);
  pinMode(CHRG, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33,OUTPUT);

  timer = timerBegin(0, 80, true); 
  timerAttachInterrupt(timer, &stopPulse, true); 
}

void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
  
    int commaPos = inputString.indexOf(',');
    
    if (commaPos != -1) {
      String dataString = inputString.substring(0, commaPos);
      String sliderString = inputString.substring(commaPos + 1);
      
      int data = dataString.toInt();
      int charge = sliderString.toInt();

      gpioPin = getPin(data);
      action(gpioPin, charge);
      
    }
    else {
      Serial.println("Error: Invalid input format.");
    }
  }
}

/* setting pin for chipping/kicking */
int getPin(int data){
  if(data == 1){
    gpioPin = GPIO_PIN_KICK;
  }
  else if (data == 2){
    gpioPin = GPIO_PIN_CHIP;
  }
  else{
    gpioPin = -1;
    Serial.println("Error");
  }

  return gpioPin;
}

/* Kicking/Chipping */
void action(int gpioPin, int pulse_width){
    Serial.print("Charging to kick at: ");
    Serial.println(pulse_width);

//  if (pulse_width > 4000)
//  {
//    Serial.println("Pulse width is greater than 4000");
//    return;
//  }

    digitalWrite(CHRG, HIGH);
  //delay(1000);
  //digitalWrite(CHRG, LOW);
  
    Serial.println("Going to kick in 3 seconds, standback.");

    digitalWrite(gpioPin, HIGH);
    //delay(5000);
    delay(pulse_width);

    //oneShotPulse(gpioPin, pulse_width);
    Serial.println("Done.");

    digitalWrite(gpioPin, HIGH);
}