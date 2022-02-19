
#include "SPI.h"

int pino_led = 7;     // Pino onde o led está conectado
char dados;           // Variável p/ armazenar os dados recebidos
volatile boolean flag_recebimento;   // flag de recebimento de dado

void setup() {
  Serial.begin(9600);
  // Inicializa o display
  // inicia a SPI no modo escravo
  SPCR |= bit (SPE);
  
  // configura o pino MISO como saida
  pinMode(MISO, OUTPUT);
  
  // prepara o flag de recebimento para interrupcao
  flag_recebimento = false;
  
  // liga as interrupcoes
  SPI.attachInterrupt();

  pinMode(pino_led, OUTPUT);  // configura o pino do LED como saida

  
}

void loop() {
  
  // Caso a flag de recebimento seja verdadeira, então
  
  if (flag_recebimento){
    
    // se o byte recebido for igual a 0, apaga o LED
    if (dados == 0) {
      digitalWrite(pino_led, LOW);
        
    }

    // se o byte recebido for igual a 1 acende o LED
    if (dados == 1) {
      digitalWrite(pino_led, HIGH);
      
    }

    // limpa o flag de recebimento
    flag_recebimento = false;
  }
}

// Rotina de interrupcao do SPI
ISR (SPI_STC_vect) {
  
  // le e salva o byte do Registrador de dados da SPI
  dados = SPDR; 

  // seta o flag de recebimento para que o dado recebido 
  // seja processado no proximo loop
  flag_recebimento = true;
}
