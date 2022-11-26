void connectAWS()
{
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);
  StaticJsonDocument<200> doc;
  doc["device_time"] = millis();
  doc["device_name"] = THINGNAME;
  doc["device_status"] = "disconnected";
  char jsonBuffer[128];
  serializeJson(doc, jsonBuffer); // print to client
  client.setWill(AWS_IOT_CONNECTION, jsonBuffer, false, 1);
  client.onMessage(messageHandler);
  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  // Create a message handler

  Serial.println("AWS IoT Connected!");
  sendBirthMessage();
}

void sendBirthMessage() {
    StaticJsonDocument<200> doc;    
    doc["device_time"] = millis();
    doc["device_name"] = THINGNAME;
    doc["device_status"] = "connected";
    char jsonBuffer[128];
    serializeJson(doc, jsonBuffer); // print to client
    client.publish(AWS_IOT_CONNECTION, jsonBuffer);
}
void messageHandler(String &topic, String &payload) {
  Serial.println("receiving MQTT message");
  Serial.println("incoming: " + topic + " - " + payload);
  int i = payload.toInt();
  digitalWrite(IO_RELAY,i);
}
