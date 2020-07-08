#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//----------- Enter you Wi-Fi Details---------//
const char* ssid     = "nelson";        
const char* password = "Quantify"; 
//-------------------------------------------//

WiFiClient  client;

unsigned long myChannelNumber = 1087323; // Channel ID here
const int FieldNumber = 1;
const int FieldNumber2 = 2;
const char * myWriteAPIKey = "D6ZWK4UWFCUIOJVP"; // Your Write API Key here
const char * readAPIKey = "G969BGPU8NPMGBQD";

String tempValue;
int analogValue;
int tempPin = A0;
float milliVolts;
float celcius;


void setup(){
Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
WiFi.begin(ssid,password);
Serial.println("");
Serial.println("Connecting");


//aConst = readTSData( myChannelNumber, aField );

/* If Wi-Fi hotspot is not found, show ..... in serial monitor */
while(WiFi.status()!=WL_CONNECTED){
delay(1000);
Serial.println(".");
}
/* If Wi-Fi hotspot is found, show IP address in serial monitor */
Serial.println("");
Serial.println("Connected to ");
Serial.println(ssid);
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
ThingSpeak.begin(client);
}
void loop()
{
  analogValue = analogRead(tempPin);
  milliVolts = (analogValue/1024.0)*3300;
  celcius = milliVolts/10;
  tempValue = String(celcius);
  String tempValue2, tempValue3 ;
  float readData;
  
  readData = ThingSpeak.readFloatField( myChannelNumber, FieldNumber2, readAPIKey );
  
  Serial.print("Temperature = ");
  Serial.print(tempValue);
  Serial.println(" *C");
  
  Serial.print("Read Data = ");
  Serial.print(readData);
  Serial.println(" ");
  
  //ThingSpeak.writeField(myChannelNumber, FieldNumber, tempValue, myWriteAPIKey);

  if (readData == 0){
    tempValue2 = "0";
    ThingSpeak.writeField(myChannelNumber, FieldNumber, tempValue2, myWriteAPIKey);
//    readData = 1;
  }
  else {
    tempValue3 = tempValue;
    ThingSpeak.writeField(myChannelNumber, FieldNumber, tempValue3, myWriteAPIKey);
  }
  
  delay(5000);//Thingpseak free cannot read multiple input within 15 seconds

  
}

/*Problem:
 * 
 * Thignspeak frequancy is 15mins, arduino hard to read axctly the interval, hence when nnot updated, 
 * value is zero, if use 3.0, it will always be zero as the interval not synchronized.
 */
