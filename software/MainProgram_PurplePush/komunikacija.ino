unsigned long lastReceivedTime = 0;
unsigned long timeout = 10;  // 2 sekunde bez poruke = ESP je "otišao"

bool getReadingFromESP() {
  if (Serial8.available()) {
    String received = Serial8.readStringUntil('\n');
    Serial.print("From ESP32: ");
    Serial.println(received);
    lastReceivedTime = millis();
    return true;
  }

  if (millis() - lastReceivedTime > timeout) {
    return false;
  }

  return true;
}