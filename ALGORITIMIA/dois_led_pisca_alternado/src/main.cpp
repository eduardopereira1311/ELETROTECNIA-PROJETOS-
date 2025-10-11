#include <Arduino.h>

// Configuração dos pinos 13 e 12 como saída
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

// Loop principal que alterna os dois LEDs
void loop() {
  digitalWrite(13, HIGH); // Acende o LED do pino 13
  digitalWrite(12, LOW);  // Apaga o LED do pino 12
  delay(200);

  digitalWrite(13, LOW);  // Apaga o LED do pino 13
  digitalWrite(12, HIGH); // Acende o LED do pino 12
  delay(200);
}