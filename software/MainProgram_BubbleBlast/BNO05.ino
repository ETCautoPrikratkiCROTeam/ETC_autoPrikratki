float getHeading(){
 sensors_event_t event;
  bno.getEvent(&event);
  float heading = event.orientation.x;
  if (heading < 0) {
    heading += 360;
  }
  //delay(1);
  return heading;
}

float normalized(float angle) {
  angle = fmod((angle + 180), 360);
  if (angle < 0) {
    angle += 360;
  }
  return angle - 180;
}

/*float rotationToMaintainHeading(float headingToMaintain) {
  float currentHeading = getHeading();
  float rotation = map(normalized(headingToMaintain - currentHeading), -180, 180, -150, 150);
  unsigned long now = millis();
  //Serial.println(rotation);
 if (rotation < 0) {
    rotation = rotation * 0.7;  
  } else {
    rotation = rotation * 0.7; 
  }
  return rotation;
}*/
float rotationToMaintainHeading(float headingToMaintain) {
  float currentHeading = getHeading();
  unsigned long now = millis();
  double deltaTime = (now - lastTime) / 1000.0; // Convert to seconds
  lastTime = now;

  // Compute PID
  greska = normalized(headingToMaintain - currentHeading);
  integral += greska * deltaTime;
  derivative = (greska - lastError) / deltaTime;
  output = (Kp * greska) + (Ki * integral) + (Kd * derivative);
  lastError = greska;

  // Constrain output (Adjust motor range if needed)
  output = constrain(output, -150, 150);


  return output;
}