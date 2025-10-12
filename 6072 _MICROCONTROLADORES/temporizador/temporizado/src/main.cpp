#include <Arduino.h>

unsigned long tempoAnterior = 0;
unsigned long intervalo = 1000; //"unsigned" para tirar numeros negativos LONG para extender o tamanho do numero
unsigned long tempoAtual = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

    tempoAtual = millis();
 
  if (tempoAtual - tempoAnterior >= 1000) {
   
    Serial.println("Passou 1 segundo!");

    // Atualiza o tempo anterior.
    tempoAnterior = millis();
   
  }

}
