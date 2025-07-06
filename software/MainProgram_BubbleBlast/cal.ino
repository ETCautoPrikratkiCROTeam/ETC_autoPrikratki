int sensorCount = 32;    
int sensorMin[32];   
int sensorMax[32];  
int sensorThreshold[32];      

void readLineSensors2() {
  int counter = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {

          digitalWrite(30, i);
          digitalWrite(31, j);
          digitalWrite(32, k);
          digitalWrite(33, l);

          delay(1);

          lin[counter] = analogRead(A3);
          lin[counter + 16] = analogRead(A6);
          counter++;
        }
      }
    }
  }
}

void calibrateSensors() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 0; i < sensorCount; i++) {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
  }
  unsigned long startTime = millis();
  while (millis() - startTime < 10000) {
    readLineSensors2();  
    for (int i = 0; i < sensorCount; i++) {
      if (lin[i] < sensorMin[i]) {
        sensorMin[i] = lin[i];
      }
      if (lin[i] > sensorMax[i]) {
        sensorMax[i] = lin[i];
      }
    }
  }
  for (int i = 0; i < sensorCount; i++) {
    treshold[i] = sensorMin[i] + (sensorMax[i] - sensorMin[i]) * 0.70; 
    EEPROM.write(i * 2, treshold[i] >> 8);
    EEPROM.write(i * 2 + 1, treshold[i] & 0xFF);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" Min: ");
    Serial.print(sensorMin[i]);
    Serial.print(" Max: ");
    Serial.print(sensorMax[i]);
    Serial.print(" Threshold: ");
    Serial.println(treshold[i]);
  }
  Serial.println("Calibration complete.");
  digitalWrite(LED_BUILTIN, LOW);
}
void loadThresholdsFromEEPROM() {
  for (int i = 0; i < sensorCount; i++) {
    int highByte = EEPROM.read(i * 2);
    int lowByte = EEPROM.read(i * 2 + 1);
    treshold[i] = (highByte << 8) + lowByte;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" Threshold from EEPROM: ");
    Serial.println(treshold[i]);
  }
}