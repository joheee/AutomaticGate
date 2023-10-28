#include <config/config.h>
#include <Firebase.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

void firebaseSetupInit(FirebaseData *fbdo, FirebaseAuth *auth, FirebaseConfig *config){
    config->api_key = API_KEY;
    config->database_url = DATABASE_URL;
    auth->user.email = USER_EMAIL;
    auth->user.password = USER_PASSWORD;
    config->token_status_callback = tokenStatusCallback;
    Firebase.begin(config, auth);
    Firebase.reconnectWiFi(true);
}