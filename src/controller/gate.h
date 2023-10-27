#include <config/config.h>
#include <Servo.h>
#include <Arduino.h>

bool isGateOpened(Servo myservo, int cm, int timeStartDelay, int timeEndDelay) {
   if(cm < 15) {
      myservo.write(175);
      delay(timeStartDelay);
      return true; 
   } 
   myservo.write(5);
   delay(timeEndDelay);
   return false;
}