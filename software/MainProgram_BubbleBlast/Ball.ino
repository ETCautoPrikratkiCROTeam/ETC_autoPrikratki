void readBall() {
  float ballBearing = map(analogRead(A1), 10, 890, 0, 360) ;
  int distance = map(analogRead(A9), 100, 500, 0, 100);
  float offsetAngle = calculateOffsetAngle2(ballBearing, distance);
  
  int smjer = map(analogRead(A1),10, 1024, 0, 11);
  int smjer2 = map(analogRead(A1), 10, 1024, 0, 360);
  Serial.print(offsetAngle);
  Serial.print(" ");
  //Serial.println(smjer2);
  if (smjer == 11) {
    //go(0, 0, 0, 0);
  } else {
    if (distance < 15) {
      int angle = ballBearing;
      if (angle > 180) {
        angle = angle +30  - 360;
      }
      go(BRZINA, angle * -1, rotationToMaintainHeading(headingToMaintain), BRZINA);
      //Serial.println(angle * -1);
    } else {

      int angle = ballBearing + offsetAngle;
      if (angle > 180) {
        angle = angle + 30 - 360;
      }
      go(BRZINA, angle * -1, rotationToMaintainHeading(headingToMaintain), BRZINA);
      Serial.println(angle*-1);
    }
  }
}
float calculateOffsetAngle(float ballBearing) {
  float offsetAngle;
  if (ballBearing > 360) {
    ballBearing = 360;
  }

  if (ballBearing >= 0 && ballBearing <= 180) {
    offsetAngle = min(ballBearing * n - 20, 90);
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
    offsetAngle = max((ballBearing - 360) * n2, -90);
  }

  return offsetAngle ;
}
void readBall2() {
  int rawBearing = analogRead(A1);
  int rawDistance = analogRead(A9);

  // Map sensor readings
  float ballBearing = map(rawBearing, 10, 890, 0, 360);
  int distance = map(rawDistance, 100, 500, 0, 100);

  // Normalize bearing to [-180, 180]
  if (ballBearing > 180) {
    ballBearing -= 360;
  }

  // Determine if ball is in front (±30° is a good range)
  bool ballInFront = abs(ballBearing) <= 30;

  if (distance < -30) {
    // Stop if ball is too close
    go(0, 0, rotationToMaintainHeading(headingToMaintain), 0);
  } else if (ballInFront) {
    // Go straight when ball is in front
    go(40, 0, rotationToMaintainHeading(headingToMaintain), 40);
  } else {
    // Steer toward the ball, keeping it centered
    float moveAngle = ballBearing;

    // You can tweak this offset logic if needed:
    moveAngle += calculateOffsetAngle(ballBearing);

    // Clamp angle to prevent wild strafing
    if (moveAngle > 180) moveAngle -= 360;
    if (moveAngle < -180) moveAngle += 360;

    go(BRZINA, moveAngle *-1, rotationToMaintainHeading(headingToMaintain), BRZINA);
  }

  Serial.print("Bearing: ");
  Serial.print(ballBearing);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print(" | Move angle: ");
  Serial.println(ballBearing);
}
