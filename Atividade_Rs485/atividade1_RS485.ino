//RS-485 cru
//Comunicação bidirecional, half-duplex, do tipo mastre-escrevo
//Usar velocidade de 19200 bps na serial virtual (9600 bps falha)
/*Driver físico MAX485
 *Pinos:
 * 
 *  1 - R0 - Read data
 *  2 - RE' - Read enable
 *  3 - DE - Write enable
 *  4 - DI - Write data
 */
#include <SoftwareSerial.h>
#define PaP //Habilitar para comunicação ponto-a-ponto
#define RE  2
#define DE  3
#define RO  4
#define DI  5
#define ADR '9'
#define LIGA_DE     digitalWrite(RE, HIGH);digitalWrite(DE, HIGH)
#define DESLIGA_DE  digitalWrite(RE, LOW);digitalWrite(DE, LOW)
#define LIGA_RE     DESLIGA_DE
#define DESLIGA_RE  LIGA_DE
int TAM = 3;
int novotamanho;
SoftwareSerial mySerial(RO, DI); // RX, TX 
  
void setup() 
{
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  pinMode(RO, INPUT);
  pinMode(DI, OUTPUT);
  
  Serial.begin(19200);
  while(!Serial);

  mySerial.begin(19200);
  
  Serial.print("RS-485\nMódulo: ");
  Serial.println(ADR);

  RS485_tx("Teste RS-485", 12);
  Serial.println();

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  
}

void loop() 
{

int count;
char rx[TAM];  
#ifdef PaP
if(!Serial.available())
#else
if(!mySerial.available())
#endif
{
 count = 0; 
 novotamanho = 3;

while(count < novotamanho)
{
rx[count] = RS485_rx(); //recebe a mensagem byte a byte
count++;                //incrementa o contador 

 if( count == 2)  // byte(tamanho)
     {
      novotamanho = rx[1] - '0' + 3; //Atualiza o tamanho de bytes da mensagem
      
     }
  
}
///////////teste de endereço///////////
if(rx[novotamanho - 1] == ADR) 
            {
              Serial.println("PASSEI AQUI");
              trata_pacote(rx);
              rx[novotamanho-1] = 0;
              Serial.println();
              Serial.println(novotamanho);
            }                      
}

}

void RS485_tx(char men[], int size)
{
 int i = 0;
LIGA_DE;
while((men[i] != 0) && (size > i))
{
#ifdef PaP
Serial.write(men[i++]);
#else
mySerial.write(men[i++]);
#endif
}
DESLIGA_DE;
} 

void trata_pacote(char p[])
{
bool estado;
//Verificar o tipo de comando e excutar
switch (p[0])
{
case 'R':
//Lê a entrada
estado = digitalRead(p[2] - '0');
//Atualiza o pacote
p[0] = 'r';
if (estado == LOW)
p[3] = 'D';
else
p[3] = 'L';
//Envia a resposta
RS485_tx(p, novotamanho);
break;
case 'W':
//Escreve na saída
if (p[3] == 'L')
digitalWrite(p[2] - '0', HIGH);
else if (p[3] == 'D')
digitalWrite(p[2] - '0', LOW);
//Atualiza o pacote
p[0] = 'w';
//Envia a resposta
RS485_tx(p, novotamanho);
break;
}
}

char RS485_rx()
{
int i = 0;
LIGA_RE;
#ifdef PaP
while(!Serial.available());
return (char)Serial.read();
#else
while(!mySerial.available());
return (char)mySerial.read();
#endif
} 
