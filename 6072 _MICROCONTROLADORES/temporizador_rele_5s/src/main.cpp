#include <Arduino.h>
//estrutura temporizador
typedef struct Temporizador
{
  unsigned long int tempo_anterior;
  unsigned long int intervalo;
  
};
//estrutura rele 
typedef struct rele
{
  int valor;//valor do rele
  int periferico;//pino do rele
  Temporizador temporizador;//estrutura temporizador
};
rele rele1;// 1 rele

//
void setup()
{
Serial.begin(9600);
rele1.temporizador.intervalo = 2000;
rele1.temporizador.tempo_anterior = millis();
rele1.periferico = 7;
pinMode(rele1.periferico, OUTPUT);

}
void loop()// if temporizador liga desliga atualizar tempo anterior
{
  if(millis()-rele1.temporizador.tempo_anterior > rele1.temporizador.intervalo)
  {
    Serial.println("executar");
   if (digitalRead(rele1.periferico))
    {
      digitalWrite(rele1.periferico, LOW);
      rele1.temporizador.tempo_anterior = millis();
    }
    else
    {
      digitalWrite(rele1.periferico, HIGH);
      rele1.temporizador.tempo_anterior = millis();
    }
  

  }

 
  } 