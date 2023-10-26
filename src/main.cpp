#include <Arduino.h>
#include <Servo.h>

#define PIN_TRIGGER 9
#define PIN_ECHO 8
#define PIN_SERVO 10

Servo myservo;
int pos = 0;

void setup() {
   pinMode(PIN_TRIGGER, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
   Serial.begin(115200);
   myservo.attach(PIN_SERVO);
}

int getDistance() {
   digitalWrite(PIN_TRIGGER,LOW);
   delayMicroseconds(2);

   digitalWrite(PIN_TRIGGER, HIGH);
   delayMicroseconds(10);

   digitalWrite(PIN_TRIGGER, LOW);
   int pulse = pulseIn(PIN_ECHO, HIGH);
   return pulse * 0.034 / 2;
}

void gateController(int cm, int timeDelay) {
   if(cm < 15) {
      myservo.write(180);
      delay(timeDelay);
   } else {
      myservo.write(0);
      delay(timeDelay);
   }

}

void loop(){

   int cm = getDistance();
   gateController(cm, 2000);
   Serial.print("Jarak (cm) : ");
   Serial.println(cm);

} 