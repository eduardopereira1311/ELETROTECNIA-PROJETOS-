#include <Arduino.h>


// Definição dos pinos
int led = 5;     // Pino do LED
int botao = A0;   // Pino do botão 1
int botao2 = A1;  // Pino do botão 2

//CONFIGURACAO PINOS
void setup() {
  pinMode(led, OUTPUT);      // Define LED como saída
  pinMode(botao, INPUT);    // Define botão 1 como entrada
  pinMode(botao2, INPUT);   // Define botão 2 como entrada
  Serial.begin(9600);     // Inicializa a comunicação serial
}
// LOOP PRINCIPAL
void loop() {
  // || para as duas situacoes 
  // Enquanto qualquer botão estiver pressionado, mantém o LED aceso
  while (digitalRead(botao) == LOW || digitalRead(botao2) == LOW) {
    digitalWrite(led, HIGH);
    if (digitalRead(botao) == LOW) {
      Serial.println("Botão 1 direita pressionado");
    }
    if (digitalRead(botao2) == LOW) {
      Serial.println("Botão 2 esquerda pressionado");
    }
    delay(500); // Pequeno atraso para evitar leitura instável
  }
  // Quando nenhum botão está pressionado, apaga o LED
  digitalWrite(led, LOW);
  Serial.println("quando nenhum botão está pressionado");
 
  delay(500);// Pequeno atraso para evitar leitura instável
}
