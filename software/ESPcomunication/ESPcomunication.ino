#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>

HardwareSerial SerialPort(1);  // UART1
String Data;
String recived;
bool espNowSendOK = true;  // prati je li zadnje slanje bilo uspješno

typedef struct struct_message {
  char message[32];
} struct_message;

struct_message incomingData;
struct_message outgoingData;

// MAC adresa drugog ESP32
uint8_t peerMAC[] = {0xE4, 0xB0, 0x63, 0x41, 0x53, 0xD0};

// Callback - kada primi poruku
void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&incomingData, data, sizeof(incomingData));

  Serial.println("---------------");
  Serial.print("Primljena poruka: ");
  Serial.println(incomingData.message);

  recived = incomingData.message;

  delay(1);  // Pauza između primanja i slanja

  // Pošalji vlastitu poruku natrag
  strncpy(outgoingData.message, Data.c_str(), sizeof(outgoingData.message));
  esp_now_send(info->src_addr, (uint8_t *)&outgoingData, sizeof(outgoingData));

  Serial.print("Poslana poruka: ");
  Serial.println(outgoingData.message);
  Serial.println("---------------");
}

// Callback - kada se poruka pošalje
void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Status slanja: Uspješno");
    espNowSendOK = true;
  } else {
    Serial.println("Status slanja: Neuspješno");
    espNowSendOK = false;
  }

  // Resetiraj poruku
  Data = "";
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  SerialPort.begin(115200, SERIAL_8N1, 17, 16); // UART1 (RX=17, TX=16)
  delay(1000);
  Serial.println("ESP32 ready.");

  Serial.print("Moja MAC adresa: ");
  Serial.println(WiFi.macAddress());

  // Inicijalizacija ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW inicijalizacija neuspješna.");
    return;
  }

  esp_now_register_recv_cb(onReceive);
  esp_now_register_send_cb(onSent);

  // Dodaj peer uređaj
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, peerMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_is_peer_exist(peerMAC)) {
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Greška pri dodavanju peer-a.");
      return;
    }
  }

  Serial.println("ESP-NOW spreman.");

  // Pošalji prvu poruku
  strncpy(outgoingData.message, "test", sizeof(outgoingData.message));
  esp_now_send(peerMAC, (uint8_t *)&outgoingData, sizeof(outgoingData));
  Serial.print("Poslana početna poruka: ");
  Serial.println(outgoingData.message);
}

void loop() {
  // Prima podatke s Teensy-a
  if (SerialPort.available()) {
    Data = SerialPort.readStringUntil('\n');
    Serial.print("From Teensy: ");
    Serial.println(Data);
  }

  // Samo šalji Teensy-u ako je zadnje ESP-NOW slanje bilo uspješno
  if (espNowSendOK) {
    SerialPort.println(recived);
  }
}
