#include <FirebaseESP32.h>
#include  <WiFi.h>

#define FIREBASE_HOST "luzon-81e62-default-rtdb.asia-southeast1.firebasedatabase.app"
#define WIFI_SSID "Harish" // Change the name of your WIFI
#define WIFI_PASSWORD "patchwork" // Change the password of your WIFI
#define FIREBASE_Authorization_key "AIzaSyAyYu_StJn1rNUWbTMuR_RuQiTgJsLl1FY"


#define RXp2 16
#define TXp2 17


FirebaseData firebaseData;

void setup() {

 // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  
}

void loop() {

/////// Gettung alue FronM aRDUINO 
    Serial.println(Serial2.readString());
  float hum = Serial2.readString();  
  
   if (isnan(hum) ){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Pressure: ");
  Serial.print(hum);
  Serial.println();
  
  Firebase.setFloat(firebaseData, "/p", hum);
   delay(200);
}r
