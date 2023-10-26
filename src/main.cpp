#include <Arduino.h>
#include <Servo.h>
#include <controller/distance.h>
#include <controller/gate.h>

// #include <Firebase.h>

// //Provide the token generation process info.
// #include "addons/TokenHelper.h"
// //Provide the RTDB payload printing info and other helper functions.
// #include "addons/RTDBHelper.h"

// // Insert your network credentials
// #define WIFI_SSID "REPLACE_WITH_YOUR_SSID"
// #define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"

// // Insert Firebase project API Key
// #define API_KEY "REPLACE_WITH_YOUR_FIREBASE_PROJECT_API_KEY"

// // Insert RTDB URLefine the RTDB URL */
// #define DATABASE_URL "REPLACE_WITH_YOUR_FIREBASE_DATABASE_URL" 

// //Define Firebase Data object
// FirebaseData fbdo;

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