float sensorOffset = 15;  // Korekcija kuta
bool offsetSet = false;

float lastFilteredMovementAngle = 0;  // Za low-pass filter

void trackBallSmoothly() {
  int rawAngle = analogRead(A1);
  int rawDistance = analogRead(A9);

  float ballBearing = rawAngle * 360.0 / 1023.0;
  ballBearing = fmod(ballBearing + sensorOffset + 360.0, 360.0);

  float distance = map(rawDistance, 100, 500, 0, 100);

  float heading = getHeading();
  float desiredHeading = headingToMaintain;

  float globalBallAngle = fmod(ballBearing + heading, 360.0);
  float movementAngle = fmod(globalBallAngle - desiredHeading + 360.0, 360.0);

  if (movementAngle > 180) {
    movementAngle -= 360;
  }

  float delta = movementAngle - lastFilteredMovementAngle;
  if (abs(delta) > 300) {
    movementAngle = lastFilteredMovementAngle;
  }

  movementAngle = 0.7 * lastFilteredMovementAngle + 0.3 * movementAngle;
  lastFilteredMovementAngle = movementAngle;

  float orbitOffset = 25; //BILO NA 35 Lijeva strana
  float orbitOffset2 = 20; //Desna strana


  if (abs(movementAngle) < 20) {
    movementAngle = 0;
  } else if (abs(movementAngle) > 150) {
    movementAngle = (movementAngle > 0) ? 135 : -135;
  } else {
    if (movementAngle > 0) {
      movementAngle += orbitOffset;
    } else {
      movementAngle -= orbitOffset2;
    }
  }
  float angleForGo = -movementAngle;
  float dNorm = constrain(distance / 100.0, 0.0, 1.0);
  float speed = 35 + (10 * dNorm * dNorm);

  go(speed, angleForGo, rotationToMaintainHeading(headingToMaintain), 45);
}
void calibrateBall() {
  float rawBallBearing = analogRead(A1) * 360.0 / 1023.0;
  float heading = getHeading();
  float estimatedGlobalBallAngle = fmod(rawBallBearing + heading, 360.0);
  float angleToFront = fmod(estimatedGlobalBallAngle - heading + 360.0, 360.0);

  if (angleToFront > 180) angleToFront -= 360;

  sensorOffset = angleToFront;
  offsetSet = true;

  Serial.print("Sensor offset set to: ");
  Serial.println(sensorOffset);
}
