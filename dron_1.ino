#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char receivedText[32] = "";
    radio.read(&receivedText, sizeof(receivedText));
    Serial.println(receivedText);
    
    const char responseText[] = "Hello, Sender!";
    radio.stopListening();
    radio.write(&responseText, sizeof(responseText));
    radio.startListening();
  }
}
