#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
const uint64_t address = 0xF0F0F0F0E1LL;
bool confirmed = false;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(0x60);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, address);
  radio.setAutoAck(true);
  radio.startListening();
}
char confirm;
char response = "Ack";
void loop() {
  if (radio.available()) {
    char message;
    radio.read(&message, sizeof(message));
    Serial.print("Received message from gun: ");
    Serial.println(message);
    radio.stopListening();
    radio.write(&response, sizeof(response));
    radio.startListening();
    Serial.println("Sent response to gun.");
    while (radio.available()) {
      radio.read(&confirm, sizeof(confirm));
      if (confirm == "Confirm") {
        Serial.println("Received confirmation from gun.");
        confirmed = true;
      }
        if (!confirmed) {
        radio.stopListening();
        radio.write(&response, sizeof(response));
        radio.startListening();
        Serial.println("Sent continuous response to gun.");
      }
    }
  }




  delay(100);
}
