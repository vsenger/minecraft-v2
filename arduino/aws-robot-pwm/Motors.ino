void motor_left_Forward(){
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Left Motor Forward");
  analogWrite(motor1_IA, 127);
  analogWrite(motor1_IB, 255); 
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
}

void motor_left_Stop(){
  // Stop the DC motor
  Serial.println("Left Motor  stopped");
  analogWrite(motor1_IA, 0);
  analogWrite(motor1_IB, 0);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
}

void motor_left_Backwards(){
  // Move DC motor backwards at maximum speed
  Serial.println("Moving Left Motor Backwards");
  analogWrite(motor1_IA, 255);
  analogWrite(motor1_IB, 127); 
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
}


void motor_right_Forward(){
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Right Motor Forward");
  analogWrite(motor2_IA, 127);
  analogWrite(motor2_IB, 255); 
  digitalWrite(led3,HIGH);
  digitalWrite(led4,LOW);
}

void motor_right_Stop(){
  // Stop the DC motor
  Serial.println("Right Motor stopped");
  
  analogWrite(motor2_IA, 0);
  analogWrite(motor2_IB, 0);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}

void motor_right_Backwards(){
  // Move DC motor backwards at maximum speed
  Serial.println("Moving Right Motor Backwards");
  digitalWrite(motor2_IA, HIGH);
  analogWrite(motor2_IB, 127); 
  digitalWrite(led3,LOW);
  digitalWrite(led4,HIGH);
}
