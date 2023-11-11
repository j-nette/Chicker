#include <Arduino.h>

#include "kick.h"

#define KICK 1
#define CHIP 2
#define DRIBBLE 3

int HV_SENSE = 36;
int FAULT = 27;
int DONE = 26;
int CHRG = 25;

hw_timer_t * timer = NULL; 

const int GPIO_PIN_KICK = 32; //kicking pin
const int GPIO_PIN_CHIP = 33; //chipping pin
int gpioPin;

int checkAction();
int getPin();
void action(int);

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

  Serial.println("1 for kick - 2 for chip - 3 for dribble");
}

void loop() {
  //int action = checkAction(); if you want to use checkAction
  int data = Serial.readString().toInt();
  gpioPin = getPin();
  switch(data){
  case 1:
    gpioPin = GPIO_PIN_KICK;
    action(gpioPin);
    break;
  case 2:
    gpioPin = GPIO_PIN_CHIP;
    break;
  case 3:
    /* do someting */
    break;
  }
}

/* This is used if you want to type directly into the serial monitor */
int checkAction() { 
  int data = 0;
  int waiting = 1;
  do{
    while(Serial.available() == 0){} //waiting for user input
    data = Serial.parseInt(); // reading user input from serial monitor
    if(data == CHIP || data == KICK || data == DRIBBLE){
      waiting = 0;
    }
    else{
      Serial.println("Error: not a valid input. 1 for kick - 2 for chip - 3 for dribble");
    }
  }while(waiting);

  return data;
}

/* Kicking/Chipping */
void action(int gpioPin){
    int pulse_width = 0;
    Serial.println("Please enter a pulse width:");

    do {
        pulse_width = Serial.parseInt();
        delay(50);
    } while (pulse_width == 0);

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
  
    Serial.println("Going to kick in 3 seconds, standback");
    delay(5000);
    oneShotPulse(gpioPin, pulse_width);
    Serial.println("Kicked");
}