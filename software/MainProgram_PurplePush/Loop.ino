void Loop(){ 
  /*if (getReadingFromESP()) {
    //Serial.println("stoji");
    //moveToPosition(0, 0);
    //align();
  } else {
    //Serial.println("igra");
    readBall();
    LineSensor();
  }*/
  /*while(true){
  int button1 = digitalRead(36);
  int button2 = digitalRead(37);
    if(button1){
      /*digitalWrite(LED_BUILTIN,HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN,LOW);
      while(true){
        readBall();
        LineSensor();
        corner();
      }
      CalibrateSensors();
    
  }
  if(button2){
     digitalWrite(LED_BUILTIN,HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN,LOW);
      delay(200);
    while(true){
        readBall2();
        LineSensor();
      }
  }*/
  

  //currentPos();
  //moveToPosition(-15, 25);
  //bool levo; bool desno; bool napred; bool nazad;
  //LineSensor();             // Prvo pročitaj senzore
  /*refreshLineSensors();
  float ballBearing = map(analogRead(A1), 10, 890, 0, 360);
  //Serial.println(ballBearing);
  
  if(ballBearing < 360 && ballBearing > 180){
    holdLineAndSlideSafe(1);    // Zatim pozovi ovu funkciju
    Serial.println("desna");
  }
  else{
    holdLineAndSlideSafe(-1); // Zatim pozovi ovu funkciju
    Serial.println("Lijeva");
  }*/


  
  //Corner('R');
  //border();
  //align();
  //go(15, 90, rotationToMaintainHeading(90), 15);
  //go(0, 0, rotationToMaintainHeading(headingToMaintain),0);
  //Serial.println(map(analogRead(A1), 10, 890, 0, 360));
  //Serial.println(rotationToMaintainHeading(headingToMaintain));
 //motorSetSpeed(3,30);

 // If Teensy gets data from ESP32
  

  /*String received = Serial8.readStringUntil('\n');
    Serial.print("From ESP32: ");
    Serial.println(received);
  // Send data to ESP32 every 2s
  Serial8.println("1");
  delay(2);
  */
  /*
  int barijera = analogRead(A15);
  Serial.println(barijera);
*/
int button2 = digitalRead(37);
int button1 = digitalRead(36);
Serial.println(map(analogRead(A1), 20, 910, 0, 360));
LineSensor();
//go(0, 180, rotationToMaintainHeading(headingToMaintain), 40);
if(button1){
  //calibrateBall();
  while(true){
      int barijera = analogRead(A15);
       //readBall2();
       readBall2();
       LineSensor();
      //LineSuperteams(); 

       Serial8.println("1");
       //corner();
  if(barijera > 900){
    int startTimer= millis();
    while(true){
       go(30,0,0,30);
        if(millis() - startTimer > 25){
        break;
      }
      LineSensor();
      //LineSuperteams();
    }
   
    
    digitalWrite(12,HIGH);
    delay(60);
    digitalWrite(12,LOW);
    delay(60);
    int StartTimer= millis();
    while(true){
      if(millis() - StartTimer > 1000){
        break;
      }
      //readBall();
      readBall2();
      //corner();
      LineSensor();
      //LineSuperteams();
    }
  }
    }
}

  if(button2){
    while(true){
      int barijera = analogRead(A15);
       //readBall2();
       trackBallSmoothly();
       LineSensor();
       //LineSuperteams();
       Serial8.println("1");
       //corner();
  if(barijera > 900){
    int startTimer= millis();
    while(true){
       go(30,0,0,30);
        if(millis() - startTimer > 25){
        break;
      }
      //LineSuperteams();
      LineSensor();
    }
   
    
    digitalWrite(12,HIGH);
    delay(60);
    digitalWrite(12,LOW);
    delay(60);
    int StartTimer= millis();
    while(true){
      if(millis() - StartTimer > 1000){
        break;
      }
      //readBall();
      trackBallSmoothly();
      //corner();
      LineSensor();
      //LineSuperteams();
    }
  }
    }
  }
}