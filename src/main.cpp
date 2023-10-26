#include <Arduino.h>
#include <Servo.h>
#include <controller/distance.h>
#include <controller/gate.h>

Servo myservo;

void setup() {
   pinMode(PIN_TRIGGER, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
   Serial.begin(115200);
   myservo.attach(PIN_SERVO);
}

void loop(){
   int cm = getDistance();
   bool isOpen = isGateOpened(myservo, cm, 2000);

   Serial.print("Jarak (cm) : ");
   Serial.println(cm);
   Serial.print("Gate Kebuka : ");
   Serial.println(isOpen);
} 