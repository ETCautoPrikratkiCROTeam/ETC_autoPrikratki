void Setup(){
  Serial.begin(115200);
  //Serial1.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A15, INPUT);
  digitalWrite(12,LOW);
  delay(100);
  if (!bno.begin()) {
    Serial.print("No BNO055 detected... Check your wiring or I2C Address!");
    while (1);
  }

   while (myOtos.begin() == false)
    {
        Serial.println("OTOS not connected, check your wiring and I2C address!");
        delay(1000);
    }
    while (Serial.available())
        Serial.read();

  Serial.println("OTOS connected!");

  delay(1000);
  //loadThresholdsFromEEPROM();
  bno.setExtCrystalUse(true);
  bno.setMode(OPERATION_MODE_NDOF);
  myOtos.calibrateImu();
  myOtos.setLinearScalar(0.842);
  myOtos.resetTracking();
  headingToMaintain = 0;

  Serial.begin(9600);     // USB Serial to PC
  Serial8.begin(115200);  // UART to ESP32
  delay(1000);
  Serial.println("Teensy ready.");

}