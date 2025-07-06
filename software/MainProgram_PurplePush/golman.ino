void followLineWithCompass(float KpMove, int maxSpeed, int maxRotation){
  const int leftSensors[12] =  { 42, 43, 46, 47, 18, 17, 19, 16, 45, 44, 41, 40};
  const int rightSensors[12] = { 14, 15, 34, 35, 38, 37, 39, 36, 33, 32, 13, 12};
  const int frontSensors[10] = { 0, 2, 1, 3, 4, 6, 5, 7, 8, 10 };
  const int rearSensors[12]  = { 31, 29, 30, 28, 27, 25, 26, 24, 23, 21, 22, 20 };

  const int leftY[12]  =  { -29, -23, -17, -11, -5, 0, 0, 5, 11, 17, 23, 29 };
  const int rightY[12] =  { -29, -23, -17, -11, -5, 0, 0, 5, 11, 17, 23, 29 };

  // Izračun za bočno praćenje linije
  float numeratorY = 0;
  float denominatorY = 0;

  for (int i = 0; i < 12; i++) {
    int lVal = lin[leftSensors[i]];
    int rVal = lin[rightSensors[i]];

    if (lVal > 80) {
      numeratorY += leftY[i] * lVal;
      denominatorY += lVal;
    }

    if (rVal > 80) {
      numeratorY += rightY[i] * rVal;
      denominatorY += rVal;
    }
  }


  float lineY = numeratorY / denominatorY;
  float moveCorrection = KpMove * lineY;
  moveCorrection = constrain(moveCorrection, -maxSpeed, maxSpeed);

  float sideMoveAngle = (moveCorrection >= 0) ? 0 : 180;
  float rotation = constrain((rotationToMaintainHeading(0) / 180.0) * maxRotation, -maxRotation, maxRotation);

  if (nazad1 && napred1) {
    // Ako su i prednji i stražnji senzori na liniji – robot staje
    go(0, 0, 0, 0);
  } 
  else if (nazad1) {
    // Pomak unazad jer stražnji senzori imaju prioritet
    go(20, 180, rotationToMaintainHeading(0), 30);  // brzina, smjer (270 = nazad), rotacija
  } 
  else if (napred1) {
    // Pomak naprijed
    go(25, 0, rotationToMaintainHeading(0), 30);  // brzina, smjer (90 = naprijed), rotacija
  }
  else{
    go(abs(moveCorrection), sideMoveAngle, rotationToMaintainHeading(0), 30);
  }

}

void holdLineAndSlideSafe(float direction, float KpLine = 0.4, int maxSideSpeed = 25, int maxRotation = 30) {
  const int leftSensors[12]  = { 42, 43, 46, 47, 18, 17, 19, 16, 45, 44, 41, 40 };
  const int rightSensors[12] = { 14, 15, 34, 35, 38, 37, 39, 36, 33, 32, 13, 12 };
  const int leftY[12]  =      { -29, -23, -17, -11, -5, 0, 0, 5, 11, 17, 23, 29 };
  const int rightY[12] =      { -29, -23, -17, -11, -5, 0, 0, 5, 11, 17, 23, 29 };

  const int frontSensors[10] = { 0, 2, 1, 3, 4, 6, 5, 7, 8, 10 };
  const int rearSensors[12]  = { 31, 29, 30, 28, 27, 25, 26, 24, 23, 21, 22, 20 };


  // --- Praćenje linije u Y-smjeru ---
  float numeratorY = 0;
  float denominatorY = 0;

  for (int i = 0; i < 12; i++) {
    int lVal = lin[leftSensors[i]];
    int rVal = lin[rightSensors[i]];

    if (lVal > 80) {
      numeratorY += leftY[i] * lVal;
      denominatorY += lVal;
    }

    if (rVal > 80) {
      numeratorY += rightY[i] * rVal;
      denominatorY += rVal;
    }
  }

  /*if (denominatorY == 0) {
    go(0, 0, rotationToMaintainHeading(0), 0);  // safety: ne vidi liniju
    return;
  }*/

  float lineY = numeratorY / denominatorY;
  float correctionY = constrain(KpLine * lineY, -10, 10);

  // --- Izračun translacijskog kuta ---
  float moveAngle;
  if (direction > 0.1) moveAngle = 90;
  else if (direction < -0.1) moveAngle = -90;
  else moveAngle = (correctionY >= 0) ? 0 : 180;

  float moveSpeed = abs(direction) * maxSideSpeed + abs(correctionY);
  float rotation = constrain((rotationToMaintainHeading(0) / 180.0) * maxRotation, -maxRotation, maxRotation);

  // --- Sigurnosna logika ---
  if (napred1 && nazad1) {
    go(0, 0, 0, 0);  // oboje aktivni → stani
  }
  else if (nazad1) {
    go(20, 180, rotationToMaintainHeading(0), 25);  // idi naprijed da se vratiš
  }
  else if (napred1) {
    go(20, 0, rotationToMaintainHeading(0), 25);  // idi unazad da se vratiš
  }
  else {
    go(moveSpeed, moveAngle, rotationToMaintainHeading(0), 30);  // normalno kretanje
  }
}

void border(){
  float x, y;
  getCurrentPosition(x, y);
  bool levo; bool desno; bool napred; bool nazad;
  lineGolman(levo, desno, napred, nazad);

  if((y <= -3.5 || (napred && !nazad)) && abs(x) < 9.3){
    while(!nazad){
      go(20, 0, rotationToMaintainHeading(0), 20);
      lineGolman(levo, desno, napred, nazad);
    }
  }
  else if(nazad && napred && abs(x) < 9.3){
    while(napred){
      go(20, 0, rotationToMaintainHeading(0), 20);
      lineGolman(levo, desno, napred, nazad);
    }
  }
  else if((!nazad && !napred && abs(x < 9.3)) || y > 5){
    while(!nazad){
      go(20, 180, rotationToMaintainHeading(headingToMaintain), 20);
      lineGolman(levo, desno, napred, nazad);
    }
  }
  
  else{go(0,0,0,0);}
}

void followBall(float baseSpeed, float deadZone = 1) {
  float ballBearing = map(analogRead(A1), 10, 890, 0, 360);
  int smjer = map(analogRead(A1),10, 1024, 0, 11);
  float movementAngle;

  // Ako je lopta unutar "mrtve zone" oko 180° → robot stoji
  if(smjer == 11){
    go(0, 0, 0, 0);
  }
  else{
    if (ballBearing > (180 - deadZone) && ballBearing < (180 + deadZone)) {
      go(0, 0, 0, 0);  // Stani
    }

    if (ballBearing > 0 && ballBearing < 180) {
      movementAngle = -90;  // idi lijevo
    } 
    else if(ballBearing < 360 && ballBearing > 180){
      movementAngle = 90;   // idi desno
    }

    go(baseSpeed, movementAngle, 0, 30); // bez rotacije
  }
}


void align(){
  bool corner = false;
  float ballBearing = map(analogRead(A1), 10, 890, 0, 360);
  //Serial.println(ballBearing);
  float x, y;
  ballBearing > 260 ? ballBearing -= 2 : ballBearing = ballBearing;
  bool levo; bool desno; bool napred; bool nazad;
  lineGolman(levo, desno, napred, nazad);
  getCurrentPosition(x, y);
  if(nazad){
    if(ballBearing <= 360 && ballBearing >= 190 && x > 12){
      Corner('R');
    }
    else if(ballBearing >= 0 && ballBearing <= 190 && x < -12){
      Corner('L');
    }
    else{
      getCurrentPosition(x, y);
      if(ballBearing >= 0 && ballBearing <= 180 && x > -12.5){
        go(30, -85, rotationToMaintainHeading(headingToMaintain), 30);
      }
      else if(ballBearing <= 360 && ballBearing >= 180 && x < 12.5){
        go(30, 93.5, rotationToMaintainHeading(headingToMaintain), 30);
      }
      else{
        go(0, 0, 0, 0);
      }
    }
  }
  else{border();}
}

void Corner(char side){
  float start_X, start_Y;
  int timer;
  float ballBearing = map(analogRead(A1), 10, 890, 0, 360);
  //Serial.println(ballBearing);
  float x, y;
  bool levo; bool desno; bool napred; bool nazad;
  switch(side){
    case 'R': while(true){
                lineGolman(levo, desno, napred, nazad);
                while(nazad){
                  go(20, 93.5, rotationToMaintainHeading(headingToMaintain), 20);
                  lineGolman(levo, desno, napred, nazad);
                }
                getCurrentPosition(start_X, start_Y);
                getCurrentPosition(x, y);
                ballBearing = map(analogRead(A1), 10, 890, 0, 360);
                if(ballBearing >= 200 && ballBearing <= 250){
                  do{
                    ballBearing = map(analogRead(A1), 10, 890, 0, 360);
                    if(abs(x-start_X) > 1.75 || abs(y + start_Y) > 1.75){
                      go(20, calculateAngle(start_X +1.25, start_Y -6.5), rotationToMaintainHeading(0), 20);
                    }
                    else{
                      go(0, 0, rotationToMaintainHeading(0), 0);
                    }
                  }while(ballBearing > 180 && ballBearing <= 360);
                  getCurrentPosition(x, y);
                  while(y < start_Y-1){
                    getCurrentPosition(x, y);
                    moveToPosition(start_X, start_Y);
                  }
                  while(x > 9.5){
                    getCurrentPosition(x, y);
                    moveToPosition(0, 0.5);
                  }
                }
                else if(ballBearing < 180){
                  getCurrentPosition(x, y);
                  while(x > 9.5){
                    getCurrentPosition(x, y);
                    moveToPosition(0, 0.5);
                  }
                  break;
                }
                else{go(0,0,0,0);}
              }    
              break;
    case 'L': while(true){
                lineGolman(levo, desno, napred, nazad);
                while(nazad){
                  go(20, -85, rotationToMaintainHeading(headingToMaintain), 20);
                  lineGolman(levo, desno, napred, nazad);
                }
                getCurrentPosition(start_X, start_Y);
                getCurrentPosition(x, y);
                ballBearing = map(analogRead(A1), 10, 890, 0, 360);
                if(ballBearing > 110 && ballBearing <= 200){
                  do{
                    ballBearing = map(analogRead(A1), 10, 890, 0, 360);
                    if(abs(x-start_X) > 1.75 || abs(y + start_Y) > 1.75){
                      go(20, calculateAngle(start_X -1.25, start_Y -5.75), rotationToMaintainHeading(0), 20);
                    }
                    else{
                      go(0, 0, rotationToMaintainHeading(0), 0);
                    }
                  }while(ballBearing > 0 && ballBearing <= 180);
                  getCurrentPosition(x, y);
                  while(y < start_Y-1){
                    getCurrentPosition(x, y);
                    moveToPosition(start_X, start_Y);
                  }
                  while(x < -9.5){
                    getCurrentPosition(x, y);
                    moveToPosition(0, 0.5);
                  }
                }
                else if(ballBearing > 180){
                  getCurrentPosition(x, y);
                  while(x < -9.5){
                    getCurrentPosition(x, y);
                    moveToPosition(0, 0.5);
                  }
                  break;
                }
                else{go(0,0,0,0);}
              }
              break;
  }
}

void lineGolman(bool &levo, bool &desno, bool &napred, bool &nazad){
    int counter = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    digitalWrite(30, i);
                    digitalWrite(31, j);
                    digitalWrite(32, k);
                    digitalWrite(33, l);

                    delayMicroseconds(10); // Small delay for stability

                    lin[counter] = analogRead(A8);    // First multiplexer
                    lin[counter + 16] = analogRead(A6);  // Second multiplexer
                    lin[counter + 32] = analogRead(A7);  // Third multiplexer

                    Serial.print(lin[counter]);
                    Serial.print(" ");
                    Serial.print(lin[counter + 16]);
                    Serial.print(" ");
                    Serial.print(lin[counter + 32]);
                    Serial.print(" ");
                    counter++;


                }
            }
        }
    }
    Serial.println();
    nazad = false, napred = false, levo = false, desno = false;

    // Check Left Sensors
    for (int s : {1, 4, 7, 10, 26, 29, 32, 35, 38, 41, 44, 47}) {
        if (lin[s] > 90) {
            //updateOffset('x');
            levo = true;
            break;
        }
    }

    // Check Right Sensors
    for (int s : {2, 5, 8, 11, 14, 17, 20, 23, 36, 39, 42, 45}) {
        if (lin[s] > 90) {
            //updateOffset('x');
            desno = true;
            break;
        }
    }

    // Check Front Sensors
    for (int s : {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33}) {
        if (lin[s] > 860) {
            //updateOffset('y');
            napred = true;
            break;
        }
    }

    // Check Back Sensors
    for (int s : {13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46}) {
        if (lin[s] > 780) {
            //updateOffset('y');
            nazad = true;
            break;
        }
    }
}

int sensorCount = 48;    
int sensorMin[48];   
int sensorMax[48];  
int sensorThreshold[48];      

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

                    delayMicroseconds(10); // Small delay for stability

                    lin[counter] = analogRead(A8);    // First multiplexer
                    lin[counter + 16] = analogRead(A6);  // Second multiplexer
                    lin[counter + 32] = analogRead(A7);  // Third multiplexer
          counter++;
        }
      }
    }
  }
}

void CalibrateSensors() {
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