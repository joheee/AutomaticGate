#include <config/config.h>
#include <Servo.h>
#include <Arduino.h>

bool isGateOpened(Servo myservo, int cm, int timeDelay) {
   if(cm < 15) {
      myservo.write(180);
      delay(timeDelay);
      return true;
   } 
    myservo.write(0);
    delay(timeDelay);
    return false;
}