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
                    counter++;
                    Serial.print("index:");
                    Serial.print(counter);
                    Serial.print(" ");
                    Serial.print(lin[counter]);
                    Serial.print(" ");
                    Serial.print("index:");
                    Serial.print(counter+16);
                    Serial.print(" ");
                    Serial.print(lin[counter + 16]);
                    Serial.print(" ");
                    Serial.println("index:");
                    Serial.print(counter+32);
                    Serial.print(" ");
                    Serial.print(lin[counter + 32]);
                    Serial.print(" ");
                }
            }
        }
    }
    bool nazad = false, napred = false, levo = false, desno = false;

    // Check Left Sensors
    for (int s : {42, 44, 40, 47, 41, 45, 17, 43, 46, 18, 16, 19}) {
        if (lin[s] > 170) {
          Serial.println("levo");
            levo = true;
            break;
        }
    }

    // Check Right Sensors
    for (int s : {39, 37, 34, 32, 13, 14, 38, 33, 15, 36, 35, 27}) {
        if (lin[s] > 170) {
          Serial.println("desno");
            desno = true;
            break;
        }
    }

    // Check Front Sensors
    for (int s : {0, 3, 2, 5, 10, 1, 8, 7, 4, 11, 6,9}) {
        if (lin[s] > 170) {
          Serial.println("napred");
            napred = true;
            break;
        }
    }

    // Check Back Sensors
    for (int s : {12, 20 ,21 ,22 ,23 ,24 ,25, 26, 28 ,29 ,30, 31 }) {
        if (lin[s] > 170) {
          Serial.println("nazad");
            nazad = true;
            break;
        }
    }
    if(napred || nazad || levo || desno){
      int barijera = analogRead(A15);
      if(barijera > 970){
        go(0,0,0,0);
        delay(2000);
      }
      float ballBearing = map(analogRead(A1), 10, 890, 0, 360) ;
      if(levo && (ballBearing > 180 && ballBearing < 270)){
        int timer1 = millis();
        while(true){
          moveToPosition(0, 0);
          if(millis()-timer1 > 500){
            break;
          }
        }
        
      }
      else if(desno && (ballBearing > 180 && ballBearing < 270)){
        int timer2 = millis();
        while(true){
          moveToPosition(0, 0);
          if(millis()-timer2 > 500){
            break;
          }
        }
      }
      //brakeAllMotors(50);
      while(true){
      refreshLineSensors();
      
      if(!napred1 && !nazad1 && !levo1 && !desno1){
        break;
      }
      else{
        moveToPosition(0, 0);
      }
      
      }
    }

    // Movement Decision Logic
    /*if (napred || (levo && desno)) {
       
        StarTimer = millis();
        while (millis() - StarTimer < 100) {
            go(40, 180, rotationToMaintainHeading(0), 40);
        }
    }else if(napred && levo){
      StarTimer = millis();
        while (millis() - StarTimer < 100) {
            go(40, 180, rotationToMaintainHeading(0), 40);
        }
    } 
    else if(napred && desno){
      StarTimer = millis();
        while (millis() - StarTimer < 100) {
            go(40, 180, rotationToMaintainHeading(0), 40);
        }
    } 
    else if (nazad) {
        
        StarTimer = millis();
        while (millis() - StarTimer < 100) {
            go(40, 0, rotationToMaintainHeading(0), 40);
        }
    } else if (levo) {
        
        StarTimer = millis();
        while (millis() - StarTimer < 200) {
            go(40, 90, rotationToMaintainHeading(0), 40);
        }
    } else if (desno) {
        
        StarTimer = millis();
        while (millis() - StarTimer < 200) {
            go(40, -90, rotationToMaintainHeading(0), 40);
        }
    }*/
    
    
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
    //delay(2000);

    // Check Left Sensors
    for (int s : {1, 4, 7, 10, 26, 29, 32, 35, 38, 41, 44, 47}) {
        if (lin[s] > 170) {
            levo1 = true;
            break;
        }
        else{
          levo1 = false;
        }
    }

    // Check Right Senso2rs
    for (int s : {2, 5, 8, 11, 14, 17, 20, 23, 36, 39, 42, 45}) {
        if (lin[s] > 170) {
            desno1 = true;
            break;
        }
        else{
          desno1 = false;
        }
    }

    // Check Front Sensors
    for (int s : {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33}) {
        if (lin[s] > 170) {
            napred1 = true;
            break;
        }
        else{
          napred1 = false;
        }
    }

    // Check Back Sensors
    for (int s : {13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46}) {
        if (lin[s] > 170) {
            nazad1 = true;
          break;
        }
        else{
          nazad1 = false;
        }
    }
    

  
}
