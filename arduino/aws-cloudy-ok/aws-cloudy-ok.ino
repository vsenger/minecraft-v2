#include <Wire.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>

#include "secrets.h"

#define hostName "play02"

const char* ssid = "surfing-iot";
const char* password = "iotiotiot";

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_SENSORS   "playground/sensors"
#define AWS_IOT_PUBLISH_BUTTON   "playground/control"
#define AWS_IOT_SUBSCRIBE_TOPIC "control/lamp"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

#define SECRET
#define THINGNAME "play02"

#define IO_BUTTON 12
#define IO_RELAY 13

Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_MPU6050 mpu;

float Xacc;
float Yacc;
float Zacc;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Wire.begin();
  inicializaAcelerometro();
  if (!htu.begin()) {
    Serial.println("Couldn't find HTU temperature / humidity sensor!");
    while (1);
  }
  //button setup

  pinMode(IO_BUTTON, INPUT_PULLUP);   //enable user button pull-up
  //relay
  pinMode(IO_RELAY, OUTPUT);

  // Default settings: 
  //  - Heater off
  //  - 14 bit Temperature and Humidity Measurement Resolutions
  attachInterrupt(IO_BUTTON, buttonISR, FALLING);
  connectWIFI();
  connectAWS();
}

double temperature, humidity;
unsigned long lastSensorsSending=0;
int volatile lastButtonTimeStamp=0, sendMessage=0;

void loop() {
  client.loop();

  if(millis() - lastSensorsSending>1000) {
    leAcelerometro();
    sensors();
    lastSensorsSending = millis();
  }
  if(sendMessage) {
    sendMQTTButtonMessage();
  }

}

void buttonISR() {
  if(millis() - lastButtonTimeStamp>400) {
    Serial.println("publishing...");
    sendMessage=1;
    lastButtonTimeStamp=millis();
  }
}

void sendMQTTButtonMessage() {
    StaticJsonDocument<200> doc;    
    doc["device_time"] = millis();
    doc["device_name"] = THINGNAME;
    char jsonBuffer[128];
    serializeJson(doc, jsonBuffer); // print to client
    client.publish(AWS_IOT_PUBLISH_BUTTON, jsonBuffer);
    sendMessage=0;
}

void sensors() {
  StaticJsonDocument<200> doc;
  doc["device_time"] = millis();
  doc["device_name"] = THINGNAME;
  doc["humidity"] = htu.readHumidity();
  doc["temperature"] = htu.readTemperature();
  doc["X"] = Xacc;
  doc["Y"] = Yacc;
  doc["Z"] = Zacc;
  char jsonBuffer[255];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish(AWS_IOT_PUBLISH_SENSORS, jsonBuffer);
}

void connectWIFI() {
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
