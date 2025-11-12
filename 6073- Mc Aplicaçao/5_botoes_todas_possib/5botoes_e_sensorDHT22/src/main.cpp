#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Botões e LEDs ---
int opcao = 0;

typedef enum eBotoes {
  cima_b = 0,
  direita_b,
  baixo_b,
  esquerda_b,
  centro_b,
  total_b
} eBotoes;

typedef struct Botao {
  int estado;
  int pino;
} Botao;

Botao botoes[total_b];

typedef enum eLeds {
  cima_l = 0,
  direita_l,
  baixo_l,
  esquerda_l,
  centro_l,
  total_l
} eLeds;

typedef struct Led {
  int pino;
} Led;

Led leds[total_l];

const int BOTAO_CIMA     = 1 << cima_b;    
const int BOTAO_DIREITA  = 1 << direita_b;
const int BOTAO_BAIXO    = 1 << baixo_b;
const int BOTAO_ESQUERDA = 1 << esquerda_b;
const int BOTAO_CENTRO   = 1 << centro_b;

// --- Novo bit para o sensor ---
const int SENSOR_DHT = 1 << 6; // bit 6 = 64

unsigned long ultimoTempo = 0;
const unsigned long intervalo = 500;

// --- DHT22 ---
#define DHTPIN  A0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// --- LCD I2C ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // Configura botões
  botoes[cima_b].pino     = 3;
  botoes[direita_b].pino  = 4;
  botoes[baixo_b].pino    = 5;
  botoes[esquerda_b].pino = 6;
  botoes[centro_b].pino   = 7;

  for(int i=0;i<total_b;i++){
    pinMode(botoes[i].pino, INPUT_PULLUP);
    botoes[i].estado = 0;
  }

  // Configura LEDs
  leds[cima_l].pino     = 9;
  leds[direita_l].pino  = 10;
  leds[baixo_l].pino    = 11;
  leds[esquerda_l].pino = 12;
  leds[centro_l].pino   = 13;

  for(int i=0;i<total_l;i++){
    pinMode(leds[i].pino, OUTPUT);
  }

  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sistema iniciado");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long agora = millis();
  if ((agora - ultimoTempo) >= intervalo) {
    ultimoTempo = agora;
    opcao = 0;

    // --- Leitura dos botões ---
    if (digitalRead(botoes[cima_b].pino) == LOW)     opcao |= BOTAO_CIMA;
    if (digitalRead(botoes[direita_b].pino) == LOW)  opcao |= BOTAO_DIREITA;
    if (digitalRead(botoes[baixo_b].pino) == LOW)    opcao |= BOTAO_BAIXO;
    if (digitalRead(botoes[esquerda_b].pino) == LOW) opcao |= BOTAO_ESQUERDA;
    if (digitalRead(botoes[centro_b].pino) == LOW)   opcao |= BOTAO_CENTRO;

    // --- Leitura do sensor ---
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    if (!isnan(temperatura) && !isnan(umidade)) {
      if (temperatura > 30.0) {
        opcao |= SENSOR_DHT;
      }
    }

    // --- Lógica dos LEDs ---
    switch(opcao) {
      case 0b00000:
        for(int n=0;n<total_l;n++) digitalWrite(leds[n].pino, LOW);
        break;

      case BOTAO_CIMA:
        digitalWrite(leds[cima_l].pino, HIGH);
        for(int n=1;n<total_l;n++) digitalWrite(leds[n].pino, LOW);
        break;

      case BOTAO_DIREITA:
        digitalWrite(leds[direita_l].pino, HIGH);
        for(int n=0;n<total_l;n++) if(n!=direita_l) digitalWrite(leds[n].pino, LOW);
        break;

      case BOTAO_BAIXO:
        digitalWrite(leds[baixo_l].pino, HIGH);
        for(int n=0;n<total_l;n++) if(n!=baixo_l) digitalWrite(leds[n].pino, LOW);
        break;

      case BOTAO_ESQUERDA:
        digitalWrite(leds[esquerda_l].pino, HIGH);
        for(int n=0;n<total_l;n++) if(n!=esquerda_l) digitalWrite(leds[n].pino, LOW);
        break;

      case BOTAO_CENTRO:
        digitalWrite(leds[centro_l].pino, HIGH);
        for(int n=0;n<total_l;n++) if(n!=centro_l) digitalWrite(leds[n].pino, LOW);
        break;

      case SENSOR_DHT:
        for(int n=0;n<total_l;n++) digitalWrite(leds[n].pino, LOW);
        digitalWrite(leds[centro_l].pino, HIGH);
        break;

      default:
        for(int n=0;n<total_l;n++){
          if(opcao & (1<<n)) digitalWrite(leds[n].pino, HIGH);
          else digitalWrite(leds[n].pino, LOW);
        }
        break;
    }

    // --- Atualiza LCD ---
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bts:"); // Alterado para Bts

    if(opcao & BOTAO_DIREITA) lcd.print("DIR ");
    if(opcao & BOTAO_ESQUERDA) lcd.print("ESQ ");
    if(opcao & BOTAO_CENTRO) lcd.print("CENT ");
    if(opcao & BOTAO_BAIXO) lcd.print("BAIX ");
    if(opcao & BOTAO_CIMA) lcd.print("CIMA ");

    lcd.setCursor(0,1);
    if (!isnan(temperatura) && !isnan(umidade)) {
      lcd.print("Temp:");
      lcd.print(temperatura,1);
      lcd.print("C ");
      lcd.print("H:");
      lcd.print(umidade,0);
      lcd.print("%");
    } else {
      lcd.print("Erro DHT22");
    }
  }
}