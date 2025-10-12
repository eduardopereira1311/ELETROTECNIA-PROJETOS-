#include <Arduino.h>
typedef struct sensor_temperatura
{
int valor;
int periferico;
unsigned long int tempo_anterior;
unsigned long int intervalo;
};
sensor_temperatura sensor1;
sensor_temperatura sensor2;


void setup()
{
Serial.begin(9600);
sensor1.intervalo = 2000;
sensor2.intervalo = 5000;
sensor1.tempo_anterior = millis();
sensor2.tempo_anterior = millis();

}
void loop()
{
  if(millis()-sensor1.tempo_anterior >sensor1.intervalo)
  {
    Serial.println("sensor 1 lendo temperatura");
    sensor1.tempo_anterior=millis();
    
  }

  if(millis()-sensor2.tempo_anterior > sensor2.intervalo)
  {
    Serial.println("agora e minha vez sensor 2 lendo temperatura");
    sensor2.tempo_anterior=millis();
  }
 
  } 
