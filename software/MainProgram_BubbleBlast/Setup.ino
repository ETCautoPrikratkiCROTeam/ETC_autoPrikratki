void Setup(){
  Serial.begin(115200);
  //Serial8.begin(115200);
  //delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A15, INPUT);
  digitalWrite(12,LOW);
  Wire1.begin();
  delay(100);
  if (!bno.begin()) {
    Serial.print("No BNO055 detected... Check your wiring or I2C Address!");
    while (1);
  }
  while (myOtos.begin(Wire1) == false)
    {
        Serial.println("OTOS not connected, check your wiring and I2C address!");
        delay(1000);
    }

  delay(1000);
  bno.setExtCrystalUse(true);
  bool setPosition(float x, float y);
  bno.setMode(OPERATION_MODE_NDOF);
  myOtos.setLinearScalar(0.822);
  
  resetPose.x = 0.0;
  resetPose.y = 0.0;

  // Apply reset
  myOtos.setPosition(resetPose);
  headingToMaintain = 0;
  loadThresholdsFromEEPROM();

  Serial.begin(9600);
  Serial8.begin(115200);
  delay(1000);
  
}