#include <Arduino.h>

int led = 5;      // Pino do LED
int botao1 = A0;  // Botão 1 (aquecimento)
int botao2 = A1;  // Botão 2 (resfriamento)

void setup() {
  pinMode(led, OUTPUT);
  pinMode(botao1, INPUT); // usaR UM resistor interno
  pinMode(botao2, INPUT); // usaR UM resistor interno
  Serial.begin(9600);
}

void loop() {
  int estado = 0; // 0 = nenhum, 1 = aquecimento, 2 = resfriamento

  if (digitalRead(botao1) == LOW) estado = 1; // botão 1 pressionado
  if (digitalRead(botao2) == LOW) estado = 2; // botão 2 pressionado

  switch (estado) {
    case 1: // aquecimento
      digitalWrite(led, HIGH);
      Serial.println("QUE FRIO! BEBIDA QUENTE SEMPRE BOM AQUECENDO ");
      break;

    case 2: // resfriamento
      digitalWrite(led, HIGH);
      Serial.println("AGUA FRESQUINHA SAINDO");
      break;

    default:
      digitalWrite(led, LOW);
      Serial.println("Nenhum botão pressionado");
      break;
  }

  delay(1500); // 1,5 segundos
}
