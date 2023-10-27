#include <Arduino.h>
#include <config/config.h>
#include <Servo.h>
#include <controller/firebase_setup.h>
#include <controller/wifi_setup.h>
#include <controller/distance.h>
#include <controller/gate.h>
#include <Firebase.h>

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
   firebaseSetupInit(fbdo, auth, config);
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
   bool isOpen = isGateOpened(myservo, cm, 500,1000);

   Serial.print("Firebase Status : ");
   Serial.println(Firebase.ready());
   Serial.print("Jarak (cm) : ");
   Serial.println(cm);
   Serial.print("Gate Kebuka : ");
   Serial.println(isOpen);
} 