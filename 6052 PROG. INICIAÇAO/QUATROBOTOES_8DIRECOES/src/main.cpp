#include <Arduino.h>

int botaoesq = A1; // pino BOTAO ESQUERDO 
int botaodir = A2; // Pino do BOTAO DIREITO
int botaocima = A3; // Pino do botao 
int botaobaixo = A4; // Pino do botão 2 resfriamento
int estado = 0; // variável de estado

void setup() {

  pinMode(botaoesq, INPUT_PULLUP);
  pinMode(botaodir, INPUT_PULLUP);
  pinMode(botaocima, INPUT_PULLUP);
  pinMode(botaobaixo, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  int esq = digitalRead(botaoesq);
  int dir = digitalRead(botaodir);
  int cima = digitalRead(botaocima);
  int baixo = digitalRead(botaobaixo);

  if (esq == HIGH && dir == HIGH && cima == HIGH && baixo == HIGH) {
    estado = 0; // nenhum pressionado
  }
   if (esq == LOW && dir == HIGH && cima == HIGH && baixo == HIGH) {
    estado = 1; // esquerdo
  }
   if (esq == HIGH && dir == LOW && cima == HIGH && baixo == HIGH) {
    estado = 2; // direito
  } 
   if (esq == HIGH && dir == HIGH && cima == LOW && baixo == HIGH) {
    estado = 3; // cima
  }
   if (esq == HIGH && dir == HIGH && cima == HIGH && baixo == LOW) {
    estado = 4; // baixo
  } 
   if (esq == LOW && dir == HIGH && cima == HIGH && baixo == LOW) {
    estado = 5; // DIAGONAL BAIXO ESQUERDO
  } 
  if (esq == LOW && dir == HIGH && cima == LOW && baixo == HIGH) {
    estado = 6; // DIAGONAL CIMA ESQUERDO
  } if (esq == HIGH && dir == LOW && cima == HIGH && baixo == LOW) {
    estado = 7; // DIAGONAL BAIXO DIREITO
  }
   if (esq == HIGH && dir == LOW && cima == LOW && baixo == HIGH) {
    estado = 8; // DIAGONAL CIMA DIREITO

    
  }

  switch (estado) {
    case 0:
      Serial.println("nenhum botao pressionado");
      break;
    case 1:
      Serial.println("botao esquerdo pressionado");
      break;
    case 2:
      Serial.println("botao direito pressionado");
      break;
    case 3:
      Serial.println("botao cima pressionado");
      break;
    case 4:
      Serial.println("botao baixo pressionado");

      break;
    case 5:
      Serial.println("botao diagonal baixo esquerdo pressionado");
      break;
    case 6:
      Serial.println("botao diagonal cima esquerdo pressionado");
      break;
    case 7:
      Serial.println("botao diagonal baixo direito pressionado");
      break;
    case 8:
      Serial.println("botao diagonal cima direito pressionado");
      break;
  }

  delay(1000); 
}