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
void getCurrentPosition(float &x, float &y) {
    sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);

    x = myPosition.x;
    y = myPosition.y;
}

float calculateAngle(float x_target, float y_target) {
    float x_current, y_current;
    getCurrentPosition(x_current, y_current);

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

float moveToPosition(float x_target, float y_target) {
    float targetAngle = calculateAngle(x_target, y_target);

    /*Serial.println("Moving to Target:");
    Serial.print("Target X: "); Serial.println(x_target);
    Serial.print("Target Y: "); Serial.println(y_target);
    Serial.print("Calculated Angle: "); Serial.println(targetAngle);*/

    go(35, targetAngle, rotationToMaintainHeading(headingToMaintain), 35);
    return targetAngle;

}

void corner(){
  float x_current, y_current;
  getCurrentPosition(x_current, y_current);
  //y_current = y_current -20;

  if(y_current > 0){
    //updateOffset('y');
    while(y_current > 0){
    int starTimer = millis();
        while (millis() - starTimer < 500) {
          getCurrentPosition(x_current, y_current);
            go(40, 180, rotationToMaintainHeading(headingToMaintain), 40);
        }
      getCurrentPosition(x_current, y_current);
      //Serial.println(y_current);
    }
  }
}

float aimTowoardsGoal(){
  float x_current, y_current;
  getCurrentPosition(x_current, y_current);
  float heading = getHeading();

  if(y_current > 0){
    float TargetAngle = calculateAngle(0,40);
    float DeltaTheta =  TargetAngle - heading;

    return DeltaTheta;

  }
}