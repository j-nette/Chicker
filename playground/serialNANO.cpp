#include <Arduino.h>

#define KICK 1
#define CHIP 2
#define DRIBBLE 3

int checkAction(void);
void kick(int);
void chip(int);
void dribble(void);

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
}

void loop() {
 if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
  
    int commaPos = inputString.indexOf(',');
    
    if (commaPos != -1) {
      // Extract the substrings before and after the comma
      String actionString = inputString.substring(0, commaPos);
      String sliderString = inputString.substring(commaPos + 1);
      
      int action = actionString.toInt();
      int slider = sliderString.toInt();

      switch(action){
      case 1:
        kick(slider);
        break;
      case 2:
        chip(slider);
        break;
      case 3:
        dribble();
        break;
      }
    }
    else {
      Serial.println("Error: Invalid input format");
    }
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

void kick(int slider){
  /*do something*/
  Serial.println("I kicked :)");

  digitalWrite(13, HIGH);
  delay(slider);
  digitalWrite(13, LOW);
}
void chip(int slider){
  /*do something*/
  Serial.println("I chipped :)");

  digitalWrite(13, HIGH);
  delay(slider);
  digitalWrite(13, LOW);
  delay(slider);
  digitalWrite(13, HIGH);
  delay(slider);
  digitalWrite(13, LOW);
}
void dribble(){
  /*do something*/
  Serial.println("I dribbled :)");
}