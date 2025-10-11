#include <Arduino.h>
//definiçao pino 
void setup() {
  pinMode(13, OUTPUT); // Define o pino 13 como saída
}

void loop() {
  digitalWrite(13, HIGH); // Acende o LED
  delay(500);             // Espera 500 milissegundos
  digitalWrite(13, LOW);  // Apaga o LED
  delay(500);             // Espera novamente
}