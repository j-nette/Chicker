#include <Arduino.h>

#define KICK 1
#define CHIP 2
#define DRIBBLE 3

int checkAction(void);

void kick(void);
void chip(void);
void dribble(void);

void setup() {
  Serial.begin(9600);

  Serial.println("1 for kick - 2 for chip - 3 for dribble");
}

void loop() {
  //int action = checkAction(); if you want to use checkAction
    int action = Serial.readString().toInt();

  switch(action){
  case 1:
    kick();
    break;
  case 2:
    chip();
    break;
  case 3:
    dribble();
    break;
  }
}

/* This is used if you want to type directly into the serial monitor */
int checkAction() { 
  int action = 0;
  int waiting = 1;
  do{
    while(Serial.available() == 0){} //waiting for user input
    action = Serial.parseInt(); // reading user input from serial monitor
    if(action == CHIP || action == KICK || action == DRIBBLE){
      waiting = 0;
    }
    else{
      Serial.println("Error: not a valid input. 1 for kick - 2 for chip - 3 for dribble");
    }
  }while(waiting);

  return action;
}

void kick(){
  /*do something*/
  Serial.println("I kicked :)");
}

void chip(){
  /*do something*/
  Serial.println("I chipped :)");
}

void dribble(){
  /*do something*/
  Serial.println("I dribbled :)");
}