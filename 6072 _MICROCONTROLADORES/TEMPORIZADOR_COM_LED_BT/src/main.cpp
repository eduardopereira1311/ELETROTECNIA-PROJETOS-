#include <Arduino.h>
// inicio definir variáveis e constantes e pinos
int led = 13, botao = A0;// pinos do LED e do botão
unsigned long tempoInicio;// registra o tempo em que o botão foi pressionado
bool ledLigado = 0, esperando = 0;   // registra estado do LED e se está esperando

//configuração pinos de entrada e saída e inicialização da serial 
void setup() {
  pinMode(led, OUTPUT); //pino de saída para o LED
  pinMode(botao, INPUT_PULLUP);//pino de entrada com resistor de pull-up
  Serial.begin(9600);
}
// definição do loop principal e sua lógica de funcionamento
void loop() {
  unsigned long agora = millis();// tempo atual em ms

  // verifica se o botão foi pressionado
  if (!digitalRead(botao)) { // botão pressionado (ativo em LOW)
    if (ledLigado) { 
      digitalWrite(led, LOW); // desliga o LED
      ledLigado = 0; //
      Serial.println("LED desligado");

    // se o LED está desligado e não está esperando, inicia a contagem
    } else if (!esperando) {
      esperando = 1;
      tempoInicio = agora;
      Serial.println("Esperando 2s...");
    }
    delay(200); // simples antirruído
  }

  // verifica se já passou 2s desde que o botão foi pressionado
  if (esperando && agora - tempoInicio >= 2000) {
    digitalWrite(led, HIGH);// liga o LED
    ledLigado = 1;
    esperando = 0;
    Serial.println("LED ligado após 2s");
  }
}