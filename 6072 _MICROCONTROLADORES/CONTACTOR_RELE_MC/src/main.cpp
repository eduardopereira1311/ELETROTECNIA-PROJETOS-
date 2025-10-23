#include <Arduino.h>

int PINO_BOTAO = A3;
int PINO_RELE  = 3;
int PINO_ESTADO_CONTATOR = A2;  // Pino para leitura do estado real

int estadoRele = 0;             // 0 = desligado, 1 = ligado
int ultimoEstadoBotao = HIGH;
int aguardandoAtraso = 0;       // 0 = não aguardando, 1 = aguardando
unsigned long tempoAcionamento = 0;
unsigned long atrasoAtual = 0;

unsigned long atrasoLiga = 5000;
unsigned long atrasoDesliga = 2000;

void setup() {
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_RELE, OUTPUT);
  pinMode(PINO_ESTADO_CONTATOR, INPUT_PULLUP);  // Leitura do contato auxiliar

  digitalWrite(PINO_RELE, LOW);

  Serial.begin(9600);
  Serial.println("Sistema iniciado: Relé DESLIGADO.");
}

void loop() {
  int leituraBotao = digitalRead(PINO_BOTAO);
  int leituraContator = digitalRead(PINO_ESTADO_CONTATOR);  // Leitura do estado real

  // Atualiza estado real do contator
  estadoRele = (leituraContator == LOW) ? 1 : 0;  // LOW = contator ligado

  // Detecta clique no botão
  if (leituraBotao == LOW && ultimoEstadoBotao == HIGH && aguardandoAtraso == 0) {
    if (estadoRele == 0) {
      atrasoAtual = atrasoLiga;
      Serial.println("Botão pressionado! Relé será LIGADO em 5 segundos...");
    } else {
      atrasoAtual = atrasoDesliga;
      Serial.println("Botão pressionado! Relé será DESLIGADO em 2 segundos...");
    }

    tempoAcionamento = millis();
    aguardandoAtraso = 1;
  }

  // Verifica se o tempo de atraso passou
  if (aguardandoAtraso == 1 && (millis() - tempoAcionamento >= atrasoAtual)) {
    if (estadoRele == 0) {
      digitalWrite(PINO_RELE, HIGH);
      Serial.println("Relé LIGADO - aguardando confirmação do contator...");
    } else {
      digitalWrite(PINO_RELE, LOW);
      Serial.println("Relé DESLIGADO - aguardando confirmação do contator...");
    }

    aguardandoAtraso = 0;
  }

  ultimoEstadoBotao = leituraBotao;

  // Exibe estado real do contator
  if (estadoRele == 1) {
    Serial.println("Estado real: CONTATOR LIGADO");
  } else {
    Serial.println("Estado real: CONTATOR DESLIGADO");
  }

  delay(500);  // Pequeno atraso para evitar flooding no Serial
}