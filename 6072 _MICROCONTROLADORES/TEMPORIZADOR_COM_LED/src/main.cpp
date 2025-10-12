#include <Arduino.h>

// VARIÁVEIS GLOBAIS E CONSTANTES 
unsigned long tempoatual= 0;
unsigned long tempoanterior= 1000; // inicializa com 1 segundo para evitar delay na primeira execução
// pinos dos LEDs
int ledPin = 13;// pino do LED embutido

//CONFIGURAR PINOS E SERIAL
void setup()
 {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
 
}
// LOOP PRINCIPAL
void loop(){
    // LÓGICA DE CONTROLE DOS LEDS
  tempoatual = millis();// Captura o tempo atual em milissegundos
  Serial.println(tempoatual); // Imprime o tempo atual no monitor serial
  if (tempoatual - tempoanterior > 1000) // SE O TEMPO ATUAL FOR MAIOR QUE 1 SEGUNDO (1000 ms)
  {
   Serial.print("tempo atual: ");// Imprime o tempo atual no monitor serial
   Serial.println(tempoatual);// Imprime o tempo atual no monitor serial

   Serial.print("tempo anterior: ");// Imprime o tempo anterior no monitor serial
   Serial.println(tempoanterior);// Imprime o tempo anterior no monitor serial
// Lógica para alternar o estado do LED
   if (digitalRead(ledPin) == LOW ) {
       digitalWrite(ledPin, HIGH); // Liga o LED
   }
   // Se o LED estiver ligado, desliga-o
   else {
       digitalWrite(ledPin, LOW); // Desliga o LED
   }
   // Atualiza o tempo anterior para o tempo atual
   tempoanterior = millis();
  } 
}