void Loop(){
  int button1 = digitalRead(36);
  int button2 = digitalRead(37);
  
  /*if (Serial8.available()) {
    String received = Serial8.readStringUntil('\n');
    Serial.print("From ESP32: ");
    Serial.println(received);
  }
    Serial8.println("1");
    delay(2);*/

  //readBall();
  //Serial.println(barijera);
  if(button1){
    digitalWrite(LED_BUILTIN,HIGH);
    myOtos.setPosition(resetPose);
    currentPos();
    int timer = millis();
    while(true){
       go(40,0,rotationToMaintainHeading(0),40);
       if(millis()- timer > 500){
        break;
       }
    }
    
    currentPos();

      digitalWrite(LED_BUILTIN,LOW);
  }
  
  if(button2){
    while(true){
      int barijera = analogRead(A15);
       readBall();
       LineSensor();
       Serial8.println("1");
       //corner();
  if(barijera > 970){
    int startTimer= millis();
    while(true){
       go(30,0,aimTowardsGoal(),30);
        if(millis() - startTimer > 200){
        break;
      }
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
      readBall();
      //corner();
      LineSensor();
    }
  }
    }
  }

}