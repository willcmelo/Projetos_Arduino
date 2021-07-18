#include <SimpleModbusSlave_DUE.h>
#include <VarSpeedServo.h> // inclusão da bibliotecaa

//Cria objeto para controlar o servo base
VarSpeedServo servo_1;
VarSpeedServo servo_2;
VarSpeedServo servo_3;
VarSpeedServo servo_4;
VarSpeedServo servo_5;

int val_1;
int val_2; 
int val_3; 
int val_4; 
int val_5; 

#define CHAVE 12  
#define  LED 4
// Using the enum instruction allows for an easy method for adding and 
// removing registers. Doing it this way saves you #defining the size 
// of your slaves register array each time you want to add more registers
// and at a glimpse informs you of your slaves register layout.

//////////////// registers of your slave ///////////////////
enum 
{     
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  POT_VAL1,
  POT_VAL2,
  POT_VAL3,
  POT_VAL4,
  POT_VAL5,       
  VALOR_ELIPSE1,
  VALOR_ELIPSE2,
  VALOR_ELIPSE3,
  VALOR_ELIPSE4,
  VALOR_ELIPSE5,
  MAN_AUTO,
  HOLDING_REGS_SIZE // leave this one
  // total number of registers for function 3 and 16 share the same register array
  // i.e. the same address space
};

unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

void setup()
{
  servo_1.attach(5); 
  servo_2.attach(6); 
  servo_3.attach(9); 
  servo_4.attach(10); 
  servo_5.attach(11); 

  modbus_configure(&Serial, 9600, 1, 11, HOLDING_REGS_SIZE, holdingRegs);

  // modbus_update_comms(baud, id) is not needed but allows for easy update of the
  // port variables and slave id dynamically in any function.
  modbus_update_comms(9600, 1);
  pinMode(CHAVE, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  // modbus_update() is the only method used in loop(). It returns the total error
  // count since the slave started. You don't have to use it but it's useful
  // for fault finding by the modbus master.
  
  modbus_update();

  val_1 = analogRead(A0); 
  val_2 = analogRead(A1);
  val_3 = analogRead(A2);
  val_4 = analogRead(A3);
  val_5 = analogRead(A4);

  val_1 = map(val_1, 0, 1023, 1, 180); //Converte o valor lido para um valor em graus (1 a 180º)
  val_2 = map(val_2, 0, 1023, 1, 180); 
  val_3 = map(val_3, 0, 1023, 1, 180); 
  val_4 = map(val_4, 0, 1023, 1, 180); 
  val_5 = map(val_5, 0, 1023, 1, 180); 

  holdingRegs[POT_VAL1] = val_1; // update data to be read by the master to adjust the PWM
  holdingRegs[POT_VAL2] = val_2;
  holdingRegs[POT_VAL3] = val_3;
  holdingRegs[POT_VAL4] = val_4;
  holdingRegs[POT_VAL5] = val_5;

  holdingRegs[MAN_AUTO] = digitalRead(CHAVE);
  
  if(holdingRegs[MAN_AUTO]== 1) //botão modo manual
  { 
  digitalWrite(LED, LOW);   // turn the LED on (HIGH is the voltage level)
  servo_1.slowmove( holdingRegs[POT_VAL1], 60); //Movimenta o servo até a posição definida pelo potenciômetro
  servo_2.slowmove( holdingRegs[POT_VAL2], 60); 
  servo_3.slowmove( holdingRegs[POT_VAL3], 60); 
  servo_4.slowmove( holdingRegs[POT_VAL4], 60); 
  servo_5.slowmove( holdingRegs[POT_VAL5], 60); 

  }
  else if(holdingRegs[MAN_AUTO]== 0) //botão modo automático(via Elipse Scada)
  {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  servo_1.slowmove( holdingRegs[VALOR_ELIPSE1], 60); //Movimenta o servo até a posição definida pelo Elipse Scada
  servo_2.slowmove( holdingRegs[VALOR_ELIPSE2], 60); 
  servo_3.slowmove( holdingRegs[VALOR_ELIPSE3], 60); 
  servo_4.slowmove( holdingRegs[VALOR_ELIPSE4], 60); 
  servo_5.slowmove( holdingRegs[VALOR_ELIPSE5], 60); 
 }

}
