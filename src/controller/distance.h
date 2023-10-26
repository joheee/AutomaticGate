#include <config/config.h>
#include <Arduino.h>

int getDistance() {
   digitalWrite(PIN_TRIGGER,LOW);
   delayMicroseconds(2);

   digitalWrite(PIN_TRIGGER, HIGH);
   delayMicroseconds(10);

   digitalWrite(PIN_TRIGGER, LOW);
   int pulse = pulseIn(PIN_ECHO, HIGH);
   return pulse * 0.034 / 2;
}