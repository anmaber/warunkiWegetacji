#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>

#define FIREBASE_HOST "kwiatuchy-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zvf5pfv15rDvb4PLDmyibJvSooxULXecmfJgKleL"
#define WIFI_SSID "Ania"
#define WIFI_PASSWORD "Ania1998"

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(1000);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{
  String measuredValue ="";
  String valueToParse="";

  bool Sr = false;
  while(Serial.available())
  {
        measuredValue = Serial.readString(); 
        Sr=true;  
  }
  delay(1000);

  if(Sr)
  {
      valueToParse = measuredValue;
      int colonIndex = valueToParse.indexOf(':');
      String dbPath = ("kwiatki/"+valueToParse.substring(0,colonIndex));
      String value = valueToParse.substring(colonIndex+1);
      
      Firebase.setString(dbPath,value);
      delay(10);
      if (Firebase.failed())
      {  
         return;
      }
      
//    valuesToParse = measuredValues;
//
//    int fristCommaIndex = valuesToParse.indexOf(',');
//    int secondCommaIndex = valuesToParse.indexOf(',', fristCommaIndex+1);
//    int thirdCommaIndex = valuesToParse.indexOf(',', secondCommaIndex + 1);
//    int fourthCommaIndex = valuesToParse.indexOf(',', thirdCommaIndex + 1);
//
//    String humidity = valuesToParse.substring(0, fristCommaIndex);
//    String temperature = valuesToParse.substring(fristCommaIndex+1, secondCommaIndex);
//    String light = valuesToParse.substring(secondCommaIndex+1, thirdCommaIndex);
//    String moisture = valuesToParse.substring(thirdCommaIndex+1);
//
//    Firebase.setString("kwiatki/hum1",humidity);
//    delay(10);
//    Firebase.setString("kwiatki/temp1",temperature);
//    delay(10);
//    Firebase.setString("kwiatki/light1",light);
//    delay(10);
//    Firebase.setString("kwiatki/moist",moisture);
//    delay(1000);
//  
//    if (Firebase.failed())
//    {  
//       return;
//    }
  }


//
//  // set value
//  Firebase.setInt("dupaTest", kwiatuch);
//  // handle error
//  if (Firebase.failed()) {
//      Serial.print("setting dupatest failed:");
//      Serial.println(Firebase.error());
//        delay(1000);  
//      return;
//  }
//  else{
//    Serial.println("setting dupatest success AYYYYYY");
//  }
//  kwiatuch++;
//  delay(1000);

}
