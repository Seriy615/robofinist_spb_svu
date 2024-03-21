#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

char message[32];
char response[32] = "Hello from the receiver!";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  radio.setAutoAck(true);
  radio.setPayloadSize(32);
}

void loop() {
  if (radio.available()) {
    while (radio.available()) {
      radio.read(&message, sizeof(message));
      Serial.print("Message received: ");
      Serial.println(message);

      radio.writeAckPayload(1, response, sizeof(response));
    }
    delay(1000);
  }
}