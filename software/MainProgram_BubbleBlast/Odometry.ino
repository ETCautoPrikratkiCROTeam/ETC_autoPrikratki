//float x_offset = 0; 
//float y_offset = 0;

void currentPos(){
  sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);

    // Print measurement
    Serial.println();
    Serial.println("Position:");
    Serial.print("X (Inches): ");
    Serial.println(myPosition.x);
    Serial.print("Y (Inches): ");
    Serial.println(myPosition.y);
    Serial.print("Heading (Degrees): ");
    Serial.println(myPosition.h);
    //delay(100);
}
void getCurrentPosition(float &x, float &y, float &heading) {
    sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);

    x = myPosition.x;
    y = myPosition.y;
    heading = getHeading();  // Heading sada dolazi iz BNO055
}
void getCurrentPosition2(float &x, float &y) {
    sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);

    // Get current heading (angle in degrees from IMU)
    float heading = getHeading(); // Implement this function to read the BNO IMU

    // Convert heading to radians
    float headingRad = heading * PI / 180.0;

    // Rotate the sensor position to align with the IMU heading
    float rotatedX = myPosition.x * cos(headingRad) - myPosition.y * sin(headingRad);
    float rotatedY = myPosition.x * sin(headingRad) + myPosition.y * cos(headingRad);

    // Assign corrected values
    x = rotatedX;
    y = rotatedY;
}



float calculateAngle(float x_target, float y_target) {
    float x_current, y_current,heading;
    getCurrentPosition(x_current, y_current,heading);

    float angle = atan2(x_target - x_current, y_target - y_current) * RAD_TO_DEG;

    // Normalize to [0, 360]
    if (angle < 0) {
        angle += 360;
    }
    if(angle > 180){
      angle = angle-360;
    }

    return angle;
}

float calculateAngle2(float x_target, float y_target) {
    float x_current, y_current, heading;
    getCurrentPosition(x_current, y_current, heading); // heading in degrees

    // Vector from robot to target (in world coordinates)
    float dx = x_target - x_current;
    float dy = y_target - y_current;

    // Global angle toward the target
    float targetAngle = atan2(dx, dy) * RAD_TO_DEG;

    // Relative movement angle from robot's perspective
    float movementAngle = targetAngle - heading;

    // Normalize to [-180, 180]
    if (movementAngle > 180) movementAngle -= 360;
    if (movementAngle < -180) movementAngle += 360;

    return movementAngle; // This is the angle you pass to drive system
}





float moveToPosition(float x_target, float y_target) {
    float targetAngle = calculateAngle2(x_target, y_target);

    Serial.println("Moving to Target:");
    Serial.print("Target X: "); Serial.println(x_target);
    Serial.print("Target Y: "); Serial.println(y_target);
    Serial.print("Calculated Angle: "); Serial.println(targetAngle);
    
    // Here you would add the logic to rotate the robot to targetAngle and move forward
    go(40, targetAngle, rotationToMaintainHeading(headingToMaintain), 40);
    return targetAngle;

}

void corner(){
  float x_current, y_current,heading;
  getCurrentPosition(x_current, y_current,heading);
  //y_current = y_current -20;

  if(y_current > 20){
    //updateOffset('y');
    while(y_current > 20){
     // moveToPosition(0, 0);
    int starTimer = millis();
        while (millis() - starTimer < 500) {
          LineSensor();
          getCurrentPosition(x_current, y_current,heading);
            go(40, 180, rotationToMaintainHeading(0), 40);
        }
      getCurrentPosition(x_current, y_current,heading);
      //Serial.println(y_current);
    }
  }
}


float aimTowardsGoal() {
    float x_current, y_current;
    float heading = getHeading();
    getCurrentPosition(x_current, y_current, heading);
    
    if (y_current > -20) {
        float targetAngle = calculateAngle(0, 40);
        float deltaTheta = targetAngle - heading;

        // Normalize deltaTheta to [-180, 180]
        while (deltaTheta > 180) deltaTheta -= 360;
        while (deltaTheta < -180) deltaTheta += 360;

        // Apply proportional scaling to smooth correction
        float correctionFactor = 0.1;  // Tweakable value (0.1 - 0.5 works well)
        float scaledCorrection = deltaTheta * correctionFactor;

        // Optional: Clamp correction to avoid sudden large adjustments
        if (scaledCorrection > 40) scaledCorrection = 40;
        if (scaledCorrection < -40) scaledCorrection = -40;

        return scaledCorrection;
    }

    return 0;  // No correction if robot hasn't crossed half-line
}


/*void updateOffset(char side){
  float x_current, y_current;
  getCurrentPosition(x_current, y_current);

  switch(side){
    case 'x':
        x_offset = abs(x_current) - 40;
        break;
    case 'y': 
        y_offset = abs(y_current) - 30;
        break;
    default:
        break;
  }
}*/