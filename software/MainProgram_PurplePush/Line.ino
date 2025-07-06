  int StarTimer;
   bool nazad1 = false, napred1 = false, levo1 = false, desno1 = false;
 void LineSensor() {
    int counter = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    digitalWrite(30, i);
                    digitalWrite(31, j);
                    digitalWrite(32, k);
                    digitalWrite(33, l);

                    delay(1); // Small delay for stability

                    lin[counter] = analogRead(A8);    // First multiplexer
                    lin[counter + 16] = analogRead(A6);  // Second multiplexer
                    lin[counter + 32] = analogRead(A7);  // Third multiplexer
                    Serial.print("in: ");
                    Serial.print(counter);
                    Serial.print(": ");
                    Serial.print(lin[counter]);
                    Serial.print(" ");
                    Serial.print("in: ");
                    Serial.print(counter+16);
                    Serial.print(": ");
                    Serial.print(lin[counter + 16]);
                    Serial.print(" ");
                    Serial.print("in: ");
                    Serial.print(counter+32);
                    Serial.print(": ");
                    Serial.print(lin[counter + 32]);
                    Serial.print(" ");
                    counter++;


                }
            }
        }
    }
    Serial.println();
    //delay(180);

    bool nazad = false, napred = false, levo = false, desno = false;

    // Check Left Sensors
    for (int s : {42,43,46,47,18,17,19,16,45,44,41,40}) {     //1, 4, 7, 10, 26, 29, 32, 35, 38, 41, 44, 47
        if (lin[s] > 150) {   //70
            //updateOffset('x');
            levo = true;
            break;
        }
    }

    // Check Right Sensors
    for (int s : {14,15,34,35,38,37,39,36,33,32,13,12}) {     //2, 5, 8, 11, 14, 17, 20, 23, 36, 39, 42, 45
        if (lin[s] > 150) {
            //updateOffset('x');
            desno = true;
            break;
        }
    }

    // Check Front Sensors
    for (int s : {0, 2, 1, 3, 4, 6, 5, 7, 8, 10, 9, 11}) {      //0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33
        if (lin[s] > 150) {
            //updateOffset('y');
            napred = true;
            break;
        }
    }

    // Check Back Sensors
    for (int s : {31, 29, 30, 28, 27, 25, 26, 24, 23, 21, 22, 20}) {      //13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46
        if (lin[s] > 150) {
            //updateOffset('y');
            nazad = true;
            break;
        }
    }
    
    
    /*if(napred || levo || desno || nazad){
      
      while(true){
        int timer = millis();
      refreshLineSensors();
      if(!napred1 && !levo1 && !desno1 && !nazad1){
        break;
      }
      else{
        moveToPosition(0, 0);
      }
      if(millis() - timer > 3000){
        timer = millis();
        if(millis - timer > 3000){
          break;
        }
        else{moveToPosition(0,0);}
      }
      }
    }*/

    // Movement Decision Logic
    if(nazad && levo){
      go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, 45, rotationToMaintainHeading(0), 35);
        }
    }
    else if(nazad && desno){
      go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, -45, rotationToMaintainHeading(0), 35);
        }
    }
    else if(napred && levo){
      go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, 135, rotationToMaintainHeading(0), 35);
        }
    }
    else if(napred && levo){
      go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, -135, rotationToMaintainHeading(0), 35);
        }
    }
    else if (napred || (levo && desno)) {
        go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, 180, rotationToMaintainHeading(0), 35);
        }
    } else if (nazad) {
        go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, 0, rotationToMaintainHeading(0), 35);
        }
    } else if (levo) {
        go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, 90, rotationToMaintainHeading(0), 35);
        }
    } else if (desno) {
        go(0, 0, rotationToMaintainHeading(0), 20);
        delay(100);
        StarTimer = millis();
        while (millis() - StarTimer < 400) {
            go(35, -90, rotationToMaintainHeading(0), 35);
        }
    }
    
}



void refreshLineSensors(){
    int counter = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    digitalWrite(30, i);
                    digitalWrite(31, j);
                    digitalWrite(32, k);
                    digitalWrite(33, l);

                    delay(1); // Small delay for stability

                    lin[counter] = analogRead(A8);    // First multiplexer
                    lin[counter + 16] = analogRead(A6);  // Second multiplexer
                    lin[counter + 32] = analogRead(A7);  // Third multiplexer

                   Serial.print("in: ");
                    Serial.print(counter);
                    Serial.print(": ");
                    Serial.print(lin[counter]);
                    Serial.print(" ");
                    Serial.print("in: ");
                    Serial.print(counter+16);
                    Serial.print(": ");
                    Serial.print(lin[counter + 16]);
                    Serial.print(" ");
                    Serial.print("in: ");
                    Serial.print(counter+32);
                    Serial.print(": ");
                    Serial.print(lin[counter + 32]);
                    Serial.print(" ");
                    counter++;
                }
            }
        }
    }
    Serial.println();
    //delay(2000);

    // Check Left Sensors
    for (int s : {42,43,46,47,18,17,19,16,45,44,41,40}) {
        if (lin[s] > 70) {
            levo1 = true;
            break;
        }
        else{
          levo1 = false;
        }
    }

    // Check Right Sensors
    for (int s : {14,15,34,35,38,37,39,36,33,32,13,12}) {
        if (lin[s] > 70) {
            desno1 = true;
            break;
        }
        else{
          desno1 = false;
        }
    }

    // Check Front Sensors
    for (int s : {0, 2, 1, 3, 4, 6, 5, 7, 8, 10, 9, 11}) {
        if (lin[s] > 70) {
            napred1 = true;
            break;
        }
        else{
          napred1 = false;
        }
    }

    // Check Back Sensors
    for (int s : {31, 29, 30, 28, 27, 25, 26, 24, 23, 21, 22, 20}) {
        if (lin[s] > 70) {
            nazad1 = true;
          break;
        }
        else{
          nazad1 = false;
        }
    }
    

  
}
void calibrateSensors() {
  digitalWrite(LED_BUILTIN, HIGH);

  // Update sensor count to 48
  int sensorCount = 48;
  int sensorMin[sensorCount];
  int sensorMax[sensorCount];

  // Initialize min/max values
  for (int i = 0; i < sensorCount; i++) {
    sensorMin[i] = 1023;  // Max ADC value
    sensorMax[i] = 0;      // Min ADC value
  }

  unsigned long startTime = millis();
  while (millis() - startTime < 10000) {  // Run calibration for 10 seconds
    LineSensor();

    for (int i = 0; i < sensorCount; i++) {
      if (lin[i] < sensorMin[i]) {
        sensorMin[i] = lin[i];
      }
      if (lin[i] > sensorMax[i]) {
        sensorMax[i] = lin[i];
      }
    }
  }

  // Calculate thresholds and store them in EEPROM
  for (int i = 0; i < sensorCount; i++) {
    treshold[i] = sensorMin[i] + (sensorMax[i] - sensorMin[i]) * 0.95;  

    // Save threshold to EEPROM (Each value takes 2 bytes)
    EEPROM.write(i * 2, treshold[i] >> 8);    // High byte
    EEPROM.write(i * 2 + 1, treshold[i] & 0xFF);  // Low byte

    // Debugging output
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

