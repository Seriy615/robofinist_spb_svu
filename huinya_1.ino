#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const uint64_t address = 0xE8E8F0F0E1LL;

char message[] = "Hello from the transmitter!";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  radio.stopListening();
  radio.write(&message, sizeof(message));
  delay(1000);

  if (radio.isAckPayloadAvailable()) {
    char ackMessage[32] = "";
    radio.read(&ackMessage, sizeof(ackMessage));
    Serial.print("Acknowledge received: ");
    Serial.println(ackMessage);
  }
}