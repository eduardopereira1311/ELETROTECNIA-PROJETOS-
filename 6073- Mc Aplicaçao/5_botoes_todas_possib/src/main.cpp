#include <Arduino.h>

// Essa variável vai guardar qual botão foi apertado
int opcao = 0;

// Enum pra gente lembrar qual botão é qual
typedef enum eBotoes
{
  cima_b = 0,
  direita_b,
  baixo_b,
  esquerda_b,
  centro_b, // botão no meio
  total_b   // total de botões, pra contar direito
} eBotoes;

// Cada botão tem seu estado e o número do pino no Arduino
typedef struct Botao
{
  int estado; // guardo o estado, mas por enquanto não uso
  int pino;   // pino físico ligado ao botão
} Botao;

Botao botoes[total_b];

// Mesmo esquema pros LEDs
typedef enum eLeds
{
  cima_l = 0,
  direita_l,
  baixo_l,
  esquerda_l,
  centro_l,
  total_l // total de LEDs que a gente tem
} eLeds;

typedef struct Led
{
  int pino; // só o pino deles mesmo
} Led;

Led leds[total_l];

// Essas constantes ajudam a gente a entender qual botão é qual
const int BOTAO_CIMA     = 1 << cima_b;    
const int BOTAO_DIREITA  = 1 << direita_b;
const int BOTAO_BAIXO    = 1 << baixo_b;
const int BOTAO_ESQUERDA = 1 << esquerda_b;
const int BOTAO_CENTRO   = 1 << centro_b;

unsigned long ultimoTempo = 0;      // pra guardar o último momento que atualizamos
const unsigned long intervalo = 100; // intervalo de 100 milissegundos

void setup() {
  Serial.begin(9600); // começa a conversa com o computador

  // Aqui a gente fala qual pino cada botão tá ligado
  botoes[cima_b].pino     = 3;
  botoes[direita_b].pino  = 4;
  botoes[baixo_b].pino    = 5;
  botoes[esquerda_b].pino = 6;
  botoes[centro_b].pino   = 7;

  // Configuro os botões como entrada com pull-up, pra garantir a leitura certa
  int i = 0;
  while (i < total_b) {
    pinMode(botoes[i].pino, INPUT_PULLUP);
    botoes[i].estado = 0; // começo com tudo desligado, zerado
    i++;
  }

  // Agora os LEDs, dizendo qual pino cada um usa
  leds[cima_l].pino     = 9;
  leds[direita_l].pino  = 10;
  leds[baixo_l].pino    = 11;
  leds[esquerda_l].pino = 12;
  leds[centro_l].pino   = 13;

  // Configurando os LEDs como saída, pra gente poder ligar e desligar
  i = 0;
  while (i < total_l) {
    pinMode(leds[i].pino, OUTPUT);
    i++;
  }

  // Mostra no monitor serial que a configuração terminou
  Serial.println("Tudo certo! Aperta os botões pra ver o resultado.");
}

void loop() {
  unsigned long agora = millis();  // pega o tempo atual

  // Só vai atualizar a cada 100 milissegundos, pra não ficar zanzando demais
  if ((agora - ultimoTempo) >= intervalo) {
    ultimoTempo = agora; // atualizo o último tempo de atualização

    opcao = 0; // começa zerado, sem botão apertado

    // Checando cada botão, se apertado, marca no opcao
    if (digitalRead(botoes[cima_b].pino) == LOW)     opcao |= BOTAO_CIMA;
    if (digitalRead(botoes[direita_b].pino) == LOW)  opcao |= BOTAO_DIREITA;
    if (digitalRead(botoes[baixo_b].pino) == LOW)    opcao |= BOTAO_BAIXO;
    if (digitalRead(botoes[esquerda_b].pino) == LOW) opcao |= BOTAO_ESQUERDA;
    if (digitalRead(botoes[centro_b].pino) == LOW)   opcao |= BOTAO_CENTRO;

    // Aí a gente vê o que fazer dependente dos botões
    switch(opcao) {
      
      case 0b00000: { // nenhum botão aperta
        int n = 0;
        while (n < total_l) {
          digitalWrite(leds[n].pino, LOW); // apaga todos os leds
          n++;
        }
        Serial.println("Nenhum botão apertado, tudo desligado.");
        break;
      }
      
      case BOTAO_CIMA: { // só o botão cima
        digitalWrite(leds[cima_l].pino, HIGH); // liga só o led de cima
        int n = 1;
        while (n < total_l) {
          digitalWrite(leds[n].pino, LOW); // apaga os outros leds
          n++;
        }
        Serial.println("Você apertou o botão CIMA.");
        break;
      }
      
      case BOTAO_DIREITA: { // só o botão direita
        digitalWrite(leds[direita_l].pino, HIGH);
        int n = 0;
        while (n < total_l) {
          if (n != direita_l) digitalWrite(leds[n].pino, LOW);
          n++;
        }
        Serial.println("Você apertou o botão DIREITA.");
        break;
      }
      
      case BOTAO_BAIXO: { // só o botão baixo
        digitalWrite(leds[baixo_l].pino, HIGH);
        int n = 0;
        while (n < total_l) {
          if (n != baixo_l) digitalWrite(leds[n].pino, LOW);
          n++;
        }
        Serial.println("Você apertou o botão BAIXO.");
        break;
      }
      
      case BOTAO_ESQUERDA: { // só o botão esquerda
        digitalWrite(leds[esquerda_l].pino, HIGH);
        int n = 0;
        while (n < total_l) {
          if (n != esquerda_l) digitalWrite(leds[n].pino, LOW);
          n++;
        }
        Serial.println("Você apertou o botão ESQUERDA.");
        break;
      }
      
      case BOTAO_CENTRO: { // só o botão do centro
        digitalWrite(leds[centro_l].pino, HIGH);
        int n = 0;
        while (n < total_l) {
          if (n != centro_l) digitalWrite(leds[n].pino, LOW);
          n++;
        }
        Serial.println("Você apertou o botão CENTRO.");
        break;
      }
      
      case 0b11111: { // todos os botões juntos
        int n = 0;
        while (n < total_l) {
          digitalWrite(leds[n].pino, HIGH); // liga todo mundo
          n++;
        }
        Serial.println("Caramba, apertou todos os botões! Tá tudo ligado!");
        break;
      }
      
      default: {
         // pra qualquer outro aperto estranho ou combinação
        int n = 0;
        while (n < total_l) {
          if (opcao & (1 << n))
            digitalWrite(leds[n].pino, HIGH);
          else
            digitalWrite(leds[n].pino, LOW);
          n++;
        }
        Serial.print("Você apertou essa combinação (binário): ");
        Serial.println(opcao, BIN);
        break;
      }
    }
  }
}
