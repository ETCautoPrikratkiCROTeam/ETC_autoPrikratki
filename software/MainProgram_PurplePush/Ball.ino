void readBall() {
  float ballBearing = map(analogRead(A1), 20, 910, 0, 360) ;
  float offsetAngle = calculateOffsetAngle(ballBearing);
  int distance = map(analogRead(A9), 100, 500, 0, 100);
  int smjer = map(analogRead(A1),10, 1024, 0, 11);
  int smjer2 = map(analogRead(A1), 10, 1024, 0, 360);
  //Serial.println(offsetAngle * -1);

  if (smjer == 11) {
    int StarTimer;
    float angle = moveToPosition(0, 0);
    int c= 0;
    while(smjer == 11){
      if(angle < 2 && angle > -2){
        StarTimer = millis();
        while (millis() - StarTimer < 250 && c== 0) {
          go(35,angle + 180,rotationToMaintainHeading(headingToMaintain), 35);
          c++;
        }
        go(0,0,rotationToMaintainHeading(headingToMaintain),30);
      }
      else{
        moveToPosition(0, 0);
        angle = moveToPosition(0, 0);
      }
      smjer = map(analogRead(A1),10, 1024, 0, 11);
      if(smjer != 11){
        break;
      }
    }
  } else if (smjer2 > 312 && smjer2 <320 ) {
   // Serial.println(smjer2);
    go(40, 0, rotationToMaintainHeading(headingToMaintain), 40);
  } else {
    if (distance < 35) {
      int angle = ballBearing;
      if (angle > 180) {
        angle = angle +10 - 360;
      }
      go(30, angle * -1, rotationToMaintainHeading(headingToMaintain), 30);
      //Serial.println(angle * -1);
    } else {

      int angle = ballBearing; // + offsetAngle
      if (angle > 180) {
        angle = angle -60 - 360;
      }
      if ((angle > 135 && angle < 180) || (angle < -135 && angle > -180)) {
        k = 0;
      }
      go(30, angle * -1, rotationToMaintainHeading(headingToMaintain), 30);
      Serial.println(angle * -1);
    }
  }
}
float calculateOffsetAngle(float ballBearing) {
  float offsetAngle;
  if (ballBearing > 360) {
    ballBearing = 360;
  }

  if (ballBearing >= 0 && ballBearing <= 180) {
    offsetAngle = min(ballBearing * n, 90);
  } else if (ballBearing > 180 && ballBearing < 360) {

    offsetAngle = max((ballBearing - 360) * n2, -90);
  }

  return offsetAngle;
}

float calculateOffsetAngle2(float ballBearing, int distance) {
  float offsetAngle = 0;

  // Normalize ballBearing to be within [0, 360]
  ballBearing = constrain(ballBearing, 0, 360);

  if (ballBearing >= 0 && ballBearing <= 180) {
    offsetAngle = min(ballBearing * n , 90);
  } else if (ballBearing > 180 && ballBearing < 360) {
    offsetAngle = max((ballBearing - 360 + 5) * n2, -90);
  }

  return offsetAngle ;
}

void readBall2() {
  float ballBearing = map(analogRead(A1), 10, 890, 0, 360) ;
  float offsetAngle = calculateOffsetAngle(ballBearing);
  int distance = map(analogRead(A9), 100, 500, 0, 100);
  int smjer = map(analogRead(A1),10, 1024, 0, 11);
  int smjer2 = map(analogRead(A1), 10, 1024, 0, 360);
  //Serial.println(smjer2);

  if (smjer == 11) {/*
    int StarTimer;
    float angle = moveToPosition(0, 0);
    int c= 0;
    while(smjer == 11){
      if(angle < 2 && angle > -2){
        StarTimer = millis();
        while (millis() - StarTimer < 250 && c== 0) {
          go(35,angle + 180,rotationToMaintainHeading(headingToMaintain), 35);
          c++;
        }
        go(0,0,rotationToMaintainHeading(headingToMaintain),30);
      }
      else{
        moveToPosition(0, -20);
        angle = moveToPosition(0, -20);
      }
      smjer = map(analogRead(A1),10, 1024, 0, 11);
      if(smjer != 11){
        break;
      }
    }*/
    go(0,0,rotationToMaintainHeading(headingToMaintain),30);
  } else if (smjer2 > 312 && smjer2 <320 ) {
   // Serial.println(smjer2);
    go(40, 0, rotationToMaintainHeading(headingToMaintain), 40);
  } else {
    if (distance < 35) {
      int angle = ballBearing;
      if (angle > 180) {
        angle = angle +10 - 360;
      }
      go(35, angle * -1, rotationToMaintainHeading(headingToMaintain), 35);
     // Serial.println(angle * -1);
    } else {

      int angle = ballBearing + offsetAngle; // + offsetAngle
      if (angle > 180) {
        angle = angle -60 - 360;
      }
      if ((angle > 135 && angle < 180) || (angle < -135 && angle > -180)) {
        k = 0;
      }
      go(35, angle * -1, rotationToMaintainHeading(headingToMaintain), 35);
      Serial.println(angle * -1);
    }
  }
}