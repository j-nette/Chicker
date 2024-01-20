#include <Arduino.h>

#define KICK 1
#define CHIP 2
#define CHARGE 3

const int HV_SENSE = 36;
const int FAULT = 27;
const int DONE = 26;
const int CHRG = 25;

void oneShotPulse(int gpioPin, int duration);
void IRAM_ATTR stopPulse();
bool ChargeCap(int CHRG, int FAULT, int DONE, int HV_SENSE);

const int GPIO_PIN_KICK = 32; //kicking pin
const int GPIO_PIN_CHIP = 33; //chipping pin
int gpioPin;

int checkAction(void);
void kick(int);
void chip(int);
void charge(int);

hw_timer_t * timer = NULL; 

void setup() {
  Serial.begin(115200);

  pinMode(HV_SENSE, INPUT);
  pinMode(DONE, INPUT);
  pinMode(FAULT, INPUT);
  pinMode(CHRG, OUTPUT);

  pinMode(GPIO_PIN_KICK, OUTPUT);
  pinMode(GPIO_PIN_CHIP,OUTPUT);

  timer = timerBegin(0, 80, true); 
  timerAttachInterrupt(timer, &stopPulse, true); 
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
        charge(slider);
        break;
      }
    }
    else {
      Serial.println("Error: Invalid input format");
    }
  }
}

void kick(int slider){
  /*do something*/
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  Serial.println("I kicked :)");
}
void chip(int slider){
  /*do something*/
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(200);
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  Serial.println("I chipped :)");
}
void charge(int slider){
  /*do something*/
  Serial.println("I charged :)");
}


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
void IRAM_ATTR stopPulse() { 
    digitalWrite(GPIO_PIN_KICK, LOW);
    digitalWrite(GPIO_PIN_CHIP, LOW);
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