void connectAWS()
{
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);
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
  client.subscribe(AWS_IOT_SUBSCRIBE_MODE);  
  client.subscribe(AWS_IOT_SUBSCRIBE_SENSORS);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC_FULL);
  // Create a message handler

  Serial.println("AWS IoT Connected!");
}

void messageHandler(String &topic, String &payload) {
  Serial.println("receiving MQTT message");
  Serial.println("incoming: " + topic + " - " + payload);
  if(topic.equals(AWS_IOT_SUBSCRIBE_MODE)) {
    robot_state++;
    if(robot_state==1) {
      digitalWrite(led1, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
    else if(robot_state==2) {
      digitalWrite(led1, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
    }
    else if(robot_state==3) {
      digitalWrite(led1, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
    }
    else if(robot_state==4) {
      digitalWrite(led1, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      robot_state=0;
    }

  }
  else if(topic.equals(AWS_IOT_SUBSCRIBE_SENSORS) && robot_state==1) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    float X = doc["X"];
    float Y = doc["Y"];
    float Z = doc["Z"];
    //{"m1a" : 0, "m1b" : 255, "m2a" : 0, "m2b" : 255, "time": 1500} //frente
    //{"m1a" : 255, "m1b" : 0, "m2a" : 255, "m2b" : 0, "time": 1500} //traz
    //mandar comandos manualmente e depurar depois para esquerda e direita
    
    //para frente
    if(X<-3) {
      int pwm1 = map(X, -4, -9, 150, 255);
      int pwm2 = map(X, -4, -9, 120, 255);
      //para frente
      //para esquerda = -4 a -9
      if(Y>3) {
        analogWrite(motor1_IA, 0);
        analogWrite(motor1_IB, pwm2);
        analogWrite(motor2_IA, 0);
        analogWrite(motor2_IB, pwm1);
      }
      else if(Y<3) {
        analogWrite(motor1_IA, 0);
        analogWrite(motor1_IB, pwm1);
        analogWrite(motor2_IA, 0);
        analogWrite(motor2_IB, pwm2);
      }
      else {
        analogWrite(motor1_IA, 0);
        analogWrite(motor1_IB, pwm1);
        analogWrite(motor2_IA, 0);
        analogWrite(motor2_IB, pwm1);
      }

      //para direita
      
    } else if(X>3) { //backward
      int pwm1 = map(X, 4, 9, 150, 255);
      int pwm2 = map(X, 4, 9, 120, 255);
      //para frente
      //para esquerda = -4 a -9
      if(Y>3) {
        analogWrite(motor1_IA, pwm2);
        analogWrite(motor1_IB, 0);
        analogWrite(motor2_IA, pwm1);
        analogWrite(motor2_IB, 0);
      }
      else if(Y<3) {
        analogWrite(motor1_IA, pwm1);
        analogWrite(motor1_IB, 0);
        analogWrite(motor2_IA, pwm2);
        analogWrite(motor2_IB, 0);
      }
      else {
        analogWrite(motor1_IA, pwm1);
        analogWrite(motor1_IB, 0);
        analogWrite(motor2_IA, pwm1);
        analogWrite(motor2_IB, 0);
      }
    }
    else {
      analogWrite(motor1_IA, 0);
      analogWrite(motor1_IB, 0);
      analogWrite(motor2_IA, 0);
      analogWrite(motor2_IB, 0);           
    }
  }
  else if(topic.equals(AWS_IOT_SUBSCRIBE_TOPIC) && robot_state==0) {
    if(payload.equals("f")) {
      motor_left_Forward();
      motor_right_Forward();
    }
    else if(payload.equals("fl")) {
      motor_left_Forward();
    }
    else if(payload.equals("fr")) {
      motor_right_Forward();
    }
    else if(payload.equals("b")) {
      motor_left_Backwards();
      motor_right_Backwards();
    }
    else if(payload.equals("bl")) {
      motor_left_Backwards();
    }
    else if(payload.equals("br")) {
      motor_right_Backwards();
    }
  }
  else if(topic.equals(AWS_IOT_SUBSCRIBE_TOPIC_FULL) && robot_state==0) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    int m1a = doc["m1a"];
    int m1b = doc["m1b"];
    int m2a = doc["m2a"];
    int m2b = doc["m2b"];
    long time = doc["time"];
    analogWrite(motor1_IA, m1a);
    analogWrite(motor1_IB, m1b);
    analogWrite(motor2_IA, m2a);
    analogWrite(motor2_IB, m2b);
    if(time>0) {
      delay(time);
      analogWrite(motor1_IA, 0);
      analogWrite(motor1_IB, 0);
      analogWrite(motor2_IA, 0);
      analogWrite(motor2_IB, 0);
    }
  }
}
