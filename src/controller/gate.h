#include <config/config.h>
#include <Servo.h>
#include <Arduino.h>

void gateController(Servo myservo, int cm, int timeDelay) {
   if(cm < 15) {
      myservo.write(180);
      delay(timeDelay);
   } else {
      myservo.write(0);
      delay(timeDelay);
   }
}