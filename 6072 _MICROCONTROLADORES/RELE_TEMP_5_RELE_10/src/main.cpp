#include <Arduino.h>
//estrutura temporizador
struct Temporizador
{
  unsigned long int tempo_anterior;
  unsigned long int intervalo;
  
};
//estrutura rele 
struct rele
{
  int valor;//valor do rele
  int periferico;//pino do rele
  Temporizador temporizador;//estrutura temporizador
};
rele rele1;
rele rele2;


void setup()
{
  Serial.begin(9600);
  rele1.temporizador.intervalo = 5000; // INTERVALO DE 5 EM 5 SEGUNDOS
  rele2.temporizador.intervalo = 10000;//INTERVALO DE 10 EM 10 SEGUNDOS
  
  rele1.temporizador.tempo_anterior = millis(); //INCIA O TEMPO ANTERIO COM TEMPO ATUAL
  rele2.temporizador.tempo_anterior = millis();
// PINOS RELE 1 E 2 
  rele1.periferico = 7;
  rele2.periferico = 8;
  // DEFINIDO COMO PINOS DE SAIDA 
  pinMode(rele1.periferico, OUTPUT);
  pinMode(rele2.periferico, OUTPUT);
  // OS RELES COMEÇAM DESLIGADOR 
  digitalWrite(rele1.periferico, LOW);
  digitalWrite(rele2.periferico, LOW);
}

void loop()
{
  if (millis() - rele1.temporizador.tempo_anterior > rele1.temporizador.intervalo)
  {
    Serial.println("RELE 1 LIGADO");
    // alterna o estado do rele1
    if (digitalRead(rele1.periferico) == LOW)
    {
      digitalWrite(rele1.periferico, HIGH);
    }
    else
    {
      digitalWrite(rele1.periferico, LOW);
    }
    rele1.temporizador.tempo_anterior = millis();
  }

  if (millis() - rele2.temporizador.tempo_anterior > rele2.temporizador.intervalo)
  {
    Serial.println("RELE 2 LIGADO");
   
    if (digitalRead(rele2.periferico) == LOW)
    {
      digitalWrite(rele2.periferico, HIGH);
    }
    else
    {
      digitalWrite(rele2.periferico, LOW);
    }
    rele2.temporizador.tempo_anterior = millis();
  }
}
