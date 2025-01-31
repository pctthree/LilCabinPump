#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

DHTesp dht;
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "lilcabinpump.local";
int        port     = 1883;
const char topic[]  = "lilcabinpump";
const char wifiHostname[] = "pumptempesp";

const long SampleInterval = 900000;
// const long SampleInterval = 60*60*1000UL;
unsigned long previousMillis = 0;

int count = 0;
int ledPin = D2; //esp8266
int engagedPin = D3;
const int signalPin = 13;
int state;



void setup()
{
  delay (60000);
  ConnectToWifi();
  ConnectToMqttBroker();
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(engagedPin, OUTPUT);
  pinMode(signalPin, INPUT);

  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  dht.setup(13, DHTesp::DHT11);

}

void loop() 
{
    digitalWrite(ledPin, HIGH);
    digitalWrite(engagedPin, LOW);

    delay(dht.getMinimumSamplingPeriod());

    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
    Serial.print(dht.toFahrenheit(temperature), 1);
    Serial.print("\t\t");
    Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
    Serial.print("\t\t");
    Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);

    if (!mqttClient.connect(broker, port)) {
       Serial.print("MQTT connection failed! Error code = ");
       Serial.println(mqttClient.connectError());

       while (1);
     }

     mqttClient.poll();
     String Rvalue = "Lil cabin spring house (Temp/Hum): ";
     mqttClient.beginMessage(topic);
     mqttClient.print(Rvalue);
     mqttClient.print(temperature);
     mqttClient.print("c - ");
     mqttClient.print(humidity);
     mqttClient.endMessage();
     count = count + 1;
     delay(SampleInterval);
}

