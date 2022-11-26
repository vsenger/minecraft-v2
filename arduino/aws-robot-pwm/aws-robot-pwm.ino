#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>

#include <WiFiClientSecure.h>
#include <MQTTClient.h>

#include "secrets.h"

#include <ArduinoJson.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define led1 5
#define led2 4
#define led3 12
#define led4 15
#define delayLeds 100
bool direcao = false;
int userButtonState = 1;


// Motor A (Right)
int motor1_IA = 13; 
int motor1_IB = 14; 

// Motor B (Left)
int motor2_IA = 18; 
int motor2_IB = 19; 

double AN_36_voltage;
double AN_35_voltage;
double AN_34_voltage;
double AN_33_voltage;

double batteryVoltage;
bool batteryChargeStatus ;  //(1-CHARGED)
int batteryStatusPerCent;

#define batteryStatusPin 25

float Xacc;
float Yacc;
float Zacc;
int robot_state = 0;

#define hostName "robot01"

const char* ssid = "surfing-iot";
const char* password = "iotiotiot";

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_SENSORS   "robot/sensors"
#define AWS_IOT_PUBLISH_BUTTON   "robot/button"
#define AWS_IOT_SUBSCRIBE_TOPIC "robot/control"
#define AWS_IOT_SUBSCRIBE_TOPIC_FULL "robot/fullcontrol"
#define AWS_IOT_SUBSCRIBE_MODE "playground/control" //botao playground
#define AWS_IOT_SUBSCRIBE_SENSORS "playground/sensors"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(512);

#define SECRET
#define THINGNAME "robot01"

#define IO_BUTTON 23
#define IO_RELAY 27
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(27,OUTPUT);       //power ON sensors and OLED display
  digitalWrite(27,HIGH);
  pinMode(25,INPUT);       //encoder? 
  delay(2000);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(motor1_IA, OUTPUT);
  pinMode(motor1_IB, OUTPUT);
  pinMode(motor2_IA, OUTPUT);
  pinMode(motor2_IB, OUTPUT);
  digitalWrite(motor1_IA,LOW);
  digitalWrite(motor1_IB,LOW);
  digitalWrite(motor2_IA,LOW);
  digitalWrite(motor2_IB,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);

  //button setup
  pinMode(IO_BUTTON, INPUT_PULLUP);   //enable user button pull-up
  //relay
  pinMode(IO_RELAY, OUTPUT);

  // Default settings: 
  //  - Heater off
  //  - 14 bit Temperature and Humidity Measurement Resolutions
  attachInterrupt(IO_BUTTON, buttonISR, FALLING);
  Wire.begin();  
  delay(3000);
  inicializaAcelerometro();
  delay(2000);
  connectWIFI();
  connectAWS();
}

double temperature, humidity;
unsigned long lastSensorsSending=0;
int volatile lastButtonTimeStamp=0, sendMessage=0;

void loop() {
  client.loop();
  /*Serial.print("T=");
  Serial.print(hdc1080.readTemperature());
  Serial.print("C, RH=");
  Serial.print(hdc1080.readHumidity());
  Serial.println("%");
  Serial.print("Button=");
  Serial.println(digitalRead(23) ? "on" : "off");*/
  //sensors();
  
  if(millis() - lastSensorsSending>1000) {
    leAcelerometro();
    le_voltagem_bateria();
    le_battery_status();
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
    doc["id"] = 10;
    char jsonBuffer[128];
    serializeJson(doc, jsonBuffer); // print to client
    client.publish(AWS_IOT_PUBLISH_BUTTON, jsonBuffer);
    sendMessage=0;
}

void sensors() {
  StaticJsonDocument<200> doc;
  doc["device_time"] = millis();
  doc["device_name"] = THINGNAME;
  doc["humidity"] = humidity;
  doc["temperature"] = temperature;
  doc["battery"] = batteryVoltage;
  doc["battery_status"] = batteryStatusPerCent;
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
