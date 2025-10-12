#include <Arduino.h>
// Definição dos pinos dos botões
int botaoesq = A4; // pino BOTAO ESQUERDO 
int botaodir = A5; // Pino do BOTAO DIREITO
int botaocima = A0; // Pino do botao 1 aquecimento
int botaobaixo = A1; // Pino do botão 2 resfriamento
int estado = 0; // variável de estado

void setup() {
// CONFIGURACAO DOS BOTOES
  pinMode(botaoesq, INPUT_PULLUP);
  pinMode(botaodir, INPUT_PULLUP);
  pinMode(botaocima, INPUT_PULLUP);
  pinMode(botaobaixo, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // LEITURA DOS BOTOES
  int a = digitalRead(botaoesq);
  int b = digitalRead(botaodir);
  int c = digitalRead(botaocima);
  int d = digitalRead(botaobaixo);
// LOGICA DE FUNCIONAMENTO
  if (a == HIGH && b == HIGH && c == HIGH && d == HIGH) {
    estado = 0; // QUANDO NENHUM BOTAO FOR PRESSIONADO
  } else if (a == LOW && b == HIGH && c == HIGH && d == HIGH) {
    estado = 1; // QUANDO O BOTAO ESQUERDO FOR PRESSIONADO
  } else if (a == HIGH && b == LOW && c == HIGH && d == HIGH) {
    estado = 2; // QUANDO O BOTAO DIREITO FOR PRESSIONADO
  } else if (a == HIGH && b == HIGH && c == LOW && d == HIGH) {
    estado = 3; // QUANDO O BOTAO CIMA FOR PRESSIONADO
  } else if (a == HIGH && b == HIGH && c == HIGH && d == LOW) {
    estado = 4; // QUANDO O BOTAO BAIXO FOR PRESSIONADO
  } else {
  // SE MAIS DE UM BOTAO FOR PRESSIONADO
    estado = 0;
  }
// AÇÕES DE CADA ESTADO
  switch (estado) {
    case 0:
      Serial.println("nenhum botao pressionado");
      break; // QUANDO NENHUM BOTAO FOR PRESSIONADO
    case 1:
      Serial.println("botao esquerdo pressionado");
      break; // QUANDO O BOTAO ESQUERDO FOR PRESSIONADO
    case 2:
      Serial.println("botao direito pressionado");
      break; // QUANDO O BOTAO DIREITO FOR PRESSIONADO
    case 3:
      Serial.println("botao cima pressionado");
      break; // QUANDO O BOTAO CIMA FOR PRESSIONADO
    case 4:
      Serial.println("botao baixo pressionado");
      break; // QUANDO O BOTAO BAIXO FOR PRESSIONADO
  }
// PEQUENO DELAY PARA EVITAR LEITURAS RAPIDAS DEMAIS
  delay(150); 
}