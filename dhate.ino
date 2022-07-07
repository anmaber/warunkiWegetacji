#include "DHT.h"
#include <SoftwareSerial.h>

//UART programowy
SoftwareSerial mySerial(8,9); //RX TX
#define DHT11_PIN 4

DHT dht;
String values;

int convertMoistureToPercent(int value);
int convertLightToPercent(int value);
String getTemperature();
String getHumidity();
String getMoisture();
String getLight();

void setup()
{
  //Serial.begin(9600);
  mySerial.begin(115200);
  dht.setup(DHT11_PIN);
}

void loop()
{
  String humidity = ("hum:" + getHumidity());
  String temperature = ("temp:" +getTemperature());
  String light = ("light:" + getLight());
  String moisture = ("moist:" + getMoisture());

  mySerial.flush();
  mySerial.write(humidity.c_str());
  delay(4000);

  //mySerial.flush();
  mySerial.write(temperature.c_str());
  delay(4000);

  //mySer4ial.flush();
  mySerial.write(light.c_str());
  delay(4000);

  //mySerial.flush();
  mySerial.write(moisture.c_str());
  delay(4000);
    
//  values = (getHumidity() + ',' + getTemperature() + ',' + getLight()+','+ getMoisture());
//  delay(1000);
//  // removed any buffered previous serial data.
//  mySerial.flush();
//  // sent sensors data to serial (sent sensors data to ESP8266)
//  mySerial.print(values);
//  delay(2000);

//  Serial.print(getHumidity());
//  Serial.print("%RH | ");
//
//  Serial.print(getTemperature());
//  Serial.print("*C | light: ");
//
//  Serial.print(getLight());
//  Serial.print("% | moist: ");
//
//  Serial.print(getMoisture());
//  Serial.println("%");
}

String getTemperature()
{
  int temperature = dht.getTemperature();
  return String(temperature);
}

String getHumidity()
{
  int humidity = dht.getHumidity();
  return String(humidity);
}

String getMoisture()
{
  int moisture = convertMoistureToPercent(analogRead(A0));
  return String(moisture);
}

String getLight()
{
  int light = convertLightToPercent(analogRead(A1));
  return String(light);
}

int convertMoistureToPercent(int value) {   // function to convert moisture analog values to percent values
  int percentMoistureValue = 0;
  percentMoistureValue = map(value, 1023, 350, 0, 100);
  if (percentMoistureValue > 100)
    percentMoistureValue = 100;
  if (percentMoistureValue < 0)
    percentMoistureValue = 0;
  return percentMoistureValue;
}

int convertLightToPercent(int value) {   // function to convert moisture analog values to percent values
  int percentLightValue = 0;
  percentLightValue = map(value, 50, 900, 0, 100);
  if (percentLightValue > 100)
    percentLightValue = 100;
  if (percentLightValue < 0)
    percentLightValue = 0;
  return percentLightValue;
}
