#include <Arduino.h>


void setup() {
  pinMode(A0, INPUT_PULLUP); // botão entre A0 e GND
  pinMode(13, OUTPUT);       // LED no pino 13
}

void loop() {
  if (digitalRead(A0) == LOW) {   // se apertar o botão
    digitalWrite(13, HIGH);       // liga o LED
  } else {
    digitalWrite(13, LOW);        // desliga o LED
  }
}