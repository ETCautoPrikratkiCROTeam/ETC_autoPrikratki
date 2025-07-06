int motorPins[5][3] = { {77, 8, 3,  }, {77, 7, 2}, {77, 6, 1 }, {77, 5, 0 }, {77, 9, 4 } }; // {77, 7, 2,  }, {77, 8, 3 }, {77, 5, 0 }, {77, 6, 1 }, {77, 9, 4 }
int reverse[4] = {0, 0, 1, 0 };
int speedLevel[4] = { 0, 0, 0, 0 };

void setupMotors() {

  // Motor 1
  pinMode(77, OUTPUT);  //SLP
  pinMode(7, OUTPUT);   //PWM
  pinMode(2, OUTPUT);   //DIR

  // Motor 2
  pinMode(77, OUTPUT);  //SLP
  pinMode(8, OUTPUT);   //PWM
  pinMode(3, OUTPUT);   //DIR

  // Motor 3
  pinMode(77, OUTPUT);  //SLP
  pinMode(5, OUTPUT);   //PWM
  pinMode(0, OUTPUT);   //DIR

  // Motor 4
  pinMode(77, OUTPUT);  //SLP
  pinMode(6, OUTPUT);   //PWM
  pinMode(1, OUTPUT);   //DIR

  //Motor 5
  pinMode(77, OUTPUT);  //SLP
  pinMode(9, OUTPUT);  // PWM
  pinMode(4, OUTPUT);  // DIR


  Serial.println("Motors....OK");
}

void motorsOn() {
  digitalWrite(77, HIGH);
  digitalWrite(77, HIGH);
  digitalWrite(77, HIGH);
  digitalWrite(77, HIGH);
}

void motorsOff() {
  digitalWrite(77, LOW);
  digitalWrite(77, LOW);
  digitalWrite(77, LOW);
  digitalWrite(77, LOW);
  digitalWrite(77, LOW);
}


void motorSetSpeed(int n, int speed) {
  speed = int(speed * 2.55);
  if (speed < 0) {
    digitalWrite(motorPins[n][2], 1 - reverse[n]);
  } else {
    digitalWrite(motorPins[n][2], 0 + reverse[n]);
  }
  analogWrite(motorPins[n][1], abs(speed) - int((speedLevel[n] * abs(speed) / 10)));
}

void go(float speed, float angle, float rotation, int speedLimit = 10) {
  delayMicroseconds(10);
  angle += 135;
  angle *= -1;
  angle = toRad(angle);
  float si = sin(angle);
  float co = cos(angle);
  float motorSpeed[4];

  motorSpeed[0] = -speed * si - rotation;
  motorSpeed[1] = -speed * co - rotation;
  motorSpeed[2] = speed * si - rotation;
  motorSpeed[3] = speed * co - rotation;

  float maxMotorSpeed = abs(motorSpeed[0]);
  for (int i = 0; i < 4; i++) {
    if (abs(motorSpeed[i]) > maxMotorSpeed)
      maxMotorSpeed = abs(motorSpeed[i]);
  }
  for (int i = 0; i < 4; i++) {

    if (speedLimit == 0)
      motorSetSpeed(i, 0);
    else if (maxMotorSpeed > speedLimit)
      motorSetSpeed(i, motorSpeed[i] / maxMotorSpeed * speedLimit);
    else
      motorSetSpeed(i, motorSpeed[i]);
  }
}
