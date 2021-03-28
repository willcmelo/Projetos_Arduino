#include <SoftwareSerial.h>
#include <Servo.h>

Servo servoPPM;
int pos = 10 ; // inicia em 0º
int ldrPin = A0; //pino do ldr
int ldrValor ; //valor lido do LDR
SoftwareSerial bluetooth (10, 11);
String setLDR = "";


void setup (){
  bluetooth.begin(38400);
  Serial.begin(38400);
  servoPPM.attach(9);
  servoPPM.write(pos);
}

void loop()
{
 if(bluetooth.available()>0)  
  {
    setLDR = bluetooth.readString(); // ler a string na tela do celular, que será o valor setado do iluminamento
  }
 
  ldrValor = analogRead(ldrPin); //Atribui a leitura do pino A0(ldr) na variavel ldrValor
  ldrValor = map(ldrValor, 0, 1023, 180, 0); //Mudança de escala
 
   if (ldrValor  > setLDR.toInt())
  {
    servoPPM.write( pos = pos - 2);
    if (pos<0)
    {
    pos=0;
    }
  }
  if (ldrValor  < setLDR.toInt())  
  {
    servoPPM.write( pos = pos + 2 ); 
     if (pos>130)
     {
     pos=130;
     }

    }
 bluetooth.print("*A" + String(pos)+"*" ); //Mostra na tela do celular o valor da posição do motor    
 bluetooth.print("*L" + String(ldrValor)+"*" ); //mostra noa tela do celular o valor do LDR
 bluetooth.print("*B" + String (setLDR)+"*" ); 
 delay(500);
}
