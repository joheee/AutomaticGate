#include <controller/firebase_setup.h>
#include <controller/time_format.h>
#include <controller/wifi_setup.h>
#include <controller/distance.h>
#include <controller/gate.h>
#include <config/config.h>
#include <Firebase.h>
#include <Arduino.h>
#include <Servo.h>
#include <chrono>

Servo myservo;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
   // initialize pin
   pinMode(PIN_TRIGGER, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
   myservo.attach(PIN_SERVO);
   Serial.begin(74880);

   // initialize wifi
   wifiSetupInit();

   // assign firebase cred
   firebaseSetupInit(&fbdo, &auth, &config);
}

void loop(){
   if (Firebase.ready()){
      int cm = getDistance();
      bool isOpen = isGateOpened(myservo, cm, 500,1000);
      int64_t timestamp = getCurrentWIBTimestamp();
      
      Serial.print("Jarak (cm) : ");
      Serial.println(cm);
      Serial.print("Gate Kebuka : ");
      Serial.println(isOpen);
      Serial.print("header : ");
      Serial.println(timestamp);

      if (  Firebase.RTDB.setInt(&fbdo, std::to_string(timestamp) + "/distance", cm) && 
            Firebase.RTDB.setBool(&fbdo, std::to_string(timestamp) + "/opened", isOpen ? true : false)){
         Serial.println("success push data");
      }
   }
}