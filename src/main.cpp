#include <Arduino.h>
#include <config/config.h>
#include <Servo.h>
#include <controller/distance.h>
#include <controller/gate.h>
#include <Firebase.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <ESP8266WiFi.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
Servo myservo;

void setup() {
   //  initialize pin
   pinMode(PIN_TRIGGER, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
   myservo.attach(PIN_SERVO);
   Serial.begin(74880);

   // connect wifi
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting to Wi-Fi");
   while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(300);
   }
   Serial.println();
   Serial.print("Connected with IP: ");
   Serial.println(WiFi.localIP());
   Serial.println();

   // assign firebase cred
   config.api_key = API_KEY;
   config.database_url = DATABASE_URL;
   auth.user.email = USER_EMAIL;
   auth.user.password = USER_PASSWORD;
   config.token_status_callback = tokenStatusCallback;
   Firebase.begin(&config, &auth);
   Firebase.reconnectWiFi(true);
}

int count = 0;

void loop(){
   if (Firebase.ready()){
      if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
         Serial.println("PASSED");
         Serial.println("PATH: " + fbdo.dataPath());
         Serial.println("TYPE: " + fbdo.dataType());
      }
      else {
         Serial.println("FAILED");
         Serial.println("REASON: " + fbdo.errorReason());
      }
      count++;
   }

   int cm = getDistance();
   bool isOpen = isGateOpened(myservo, cm, 2000);

   Serial.print("Firebase Status : ");
   Serial.println(Firebase.ready());
   Serial.print("Jarak (cm) : ");
   Serial.println(cm);
   Serial.print("Gate Kebuka : ");
   Serial.println(isOpen);
} 