#include <Arduino.h>
// DEFININDO VARIAVEIS E PINOS
int rele = A0;      // Pino do relé
int botao = 2;      // Pino do botão
unsigned long tempoAnterior = 0;
int intervalo = 3000;
// CONF. VARIAVEIS DE ENTRADA E SAIDA 
void setup() {
  pinMode(rele, OUTPUT);
  pinMode(botao, INPUT_PULLUP);  // Botão entre pino 2 e GND
  digitalWrite(rele, LOW);       // Relé começa desligado
}
// CONFIG. ACOES 
void loop() {
  if (digitalRead(botao) == LOW) {
    intervalo = 2000;   // Pisca rápido enquanto o botão é pressionado
  } else {
    intervalo = 5000;  // Pisca devagar quando o botão está solto
  }

  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    digitalWrite(rele, !digitalRead(rele)); // Alterna o estado do relé
  }
}