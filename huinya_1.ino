#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";
bool messageSent = false;

const int buttonPin = 2;
bool buttonState = LOW;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
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
  if (!messageSent) {
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState == LOW) {
          const char text[] = "Hello, Receiver!";
          radio.stopListening();
          radio.write(&text, sizeof(text));
          radio.startListening();
          messageSent = true;
        }
      }
    }
    lastButtonState = reading;
  } else {
    if (radio.available()) {
      char receivedText[32] = "";
      radio.read(&receivedText, sizeof(receivedText));
      Serial.println(receivedText);
      messageSent = false;
    }
  }
}
