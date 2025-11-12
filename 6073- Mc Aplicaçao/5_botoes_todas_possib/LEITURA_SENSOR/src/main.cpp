#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Cria o sensor DHT22 no pino A0
DHT sensor(A0, DHT22);

// Cria o display LCD (endereço 0x27, 16 colunas e 2 linhas)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variáveis para controlar o tempo com millis()
unsigned long tempoAnterior = 0;
const unsigned long intervaloLeitura = 2000; // 2 segundos

void setup() {
  Serial.begin(9600);    // Inicia o monitor serial
  sensor.begin();        // Inicia o sensor DHT22
  lcd.init();            // Inicia o LCD
  lcd.backlight();       // Liga a luz do LCD

  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);           // Só pra mostrar "Iniciando" uma vez
}

void loop() {
  unsigned long tempoAtual = millis(); // Lê o tempo atual do Arduino

  // Faz a leitura a cada 2 segundos
  if (tempoAtual - tempoAnterior >= intervaloLeitura) {
    tempoAnterior = tempoAtual; // Atualiza o tempo da última leitura

    // Lê os valores do sensor
    float temperatura = sensor.readTemperature();
    float umidade = sensor.readHumidity();

    // Se der erro na leitura
    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("Erro ao ler o sensor!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Erro no sensor!");
      return;
    }

    // Mostra no Serial Monitor
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" °C  |  Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    // Mostra no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Umid: ");
    lcd.print(umidade);
    lcd.print(" %");
  }

  // Aqui o Arduino pode fazer outras coisas enquanto espera os 2s
}