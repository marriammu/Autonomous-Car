
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
const char *server_url = "**************/DetectAngle";
WiFiClient client;
HTTPClient http;
String FromApp;

void setup() {
      pinMode(D7,OUTPUT);
      pinMode(D8,OUTPUT);
      delay(1000);
     Serial.begin(9600);    
     WiFi.begin("STUDBME2","BME2Stud");

     while (WiFi.status() != WL_CONNECTED) {
         digitalWrite(D7,0);
         digitalWrite(D8,0);
      delay(500);
     
      Serial.print(".");
     }
     Serial.println("WiFi connected");
   
  // put your setup code here, to run once:

}

void loop() {
   http.begin(client, server_url);
   http.setTimeout(60000);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.GET();
    Serial.print(httpCode);
        if(httpCode > 0){
          String payload = http.getString();
          Serial.print("Response: ");
          Serial.println(payload);
          FromApp =String(payload);
          if (FromApp == "F")
           {
            digitalWrite(D7,1);
            digitalWrite(D8,1);
            }
          else if (FromApp  == "R"){
              digitalWrite(D7,0);
            digitalWrite(D8,1);
          }
          else if (FromApp == "L"){
            digitalWrite(D7,1);
            digitalWrite(D8,0);
          }
          else if (FromApp == "S"){
           digitalWrite(D7,0);
            digitalWrite(D8,0);
        }
    }
    else
    {
         Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
         Serial.println();
         digitalWrite(D7,0);
         digitalWrite(D8,0);
    }
    http.end();
    delay(50);

}
