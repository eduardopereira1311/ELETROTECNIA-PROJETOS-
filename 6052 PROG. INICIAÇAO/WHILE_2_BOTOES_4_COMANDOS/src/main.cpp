#include <Arduino.h>

int led = 5;      // Pino do LED
int botao1 = A0;  // Botão 1 (aquecimento)
int botao2 = A1;  // Botão 2 (resfriamento)

void setup() {
  pinMode(led, OUTPUT);
  pinMode(botao1, INPUT_PULLUP); // usa resistor interno
  pinMode(botao2, INPUT_PULLUP); // usa resistor interno
  Serial.begin(9600);
}

void loop() {
  int b1 = digitalRead(botao1);
  int b2 = digitalRead(botao2);

  // Caso 1: somente o botão 1 pressionado
  while (b1 == LOW && b2 == HIGH) {
    digitalWrite(led, HIGH);
    Serial.println("OK DEIXAREI A AGUA BEM QUENTE");
    delay(1500);
    break;
  }

  // Caso 2: somente o botão 2 pressionado
  while (b1 == HIGH && b2 == LOW) {
    digitalWrite(led, HIGH);
    Serial.println("OK DEIXAREI A AGUA MAIS FRIA");
    delay(1500);
    break;
  }

  // Caso 3: os dois botões pressionados
  while (b1 == LOW && b2 == LOW) {
    digitalWrite(led, HIGH);
    Serial.println("OK DEIXANDO A AGUA NA TEMPERATURA PERFEITA 20ºC");
    delay(1500);
    break;
  }

  // Caso 4: nenhum botão pressionado
  while (b1 == HIGH && b2 == HIGH) {
    digitalWrite(led, LOW);
    Serial.println("EM QUE POSSO LHE AJUDAR");
    delay(1500);
    break;
  }
}