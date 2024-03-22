#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define buttonPin 2

RF24 radio(CE_PIN, CSN_PIN);
const uint64_t address = 0xF0F0F0F0E1LL;
bool gotResponse = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(0x60);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    char message = "Fire";
    radio.stopListening();
    radio.write(&message, sizeof(message));
    radio.startListening();
    Serial.println("Sent signal to drone.");
    delay(1000);
    gotResponse = false;
  }

  if (radio.available()) {
    char response;
    radio.read(&response, sizeof(response));
    Serial.print("Received response from drone: ");
    Serial.println(response);
    gotResponse = true;
  }

  if (gotResponse) {
    char confirm = "Confirm";
    radio.stopListening();
    radio.write(&confirm, sizeof(confirm));
    radio.startListening();
    Serial.println("Sent confirmation to drone.");
    gotResponse = false;  // Сброс флага после отправки подтверждения
  }
  
  delay(100);
}
