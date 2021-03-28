#include <HCSR04.h>
#include <SoftwareSerial.h>
#include <Stepper.h> 
 
  // Aqui vamos definir o pino de Echo e Trigger do HC-SR04
  int angulo;
  const int stepsPerRevolution = 64;
  SoftwareSerial bluetooth (5, 6);
  Stepper myStepper(stepsPerRevolution, 8,10,9,11);
  HCSR04 hc(12,13);//initialisation class HCSR04 (trig pin , echo pin)
  const int giro = 1024;
  void setup() {
  myStepper.setSpeed(120);
  //bluetooth.begin(9600);
  Serial.begin(9600);
 
  }
 
  void loop(){
 
   
   Serial.println( hc.dist() ); 
   Serial.println((0,175781)*(-giro));
   myStepper.step(-giro); // 180  graus
   
   Serial.println( hc.dist() ); 
   Serial.println((0,175781)*(giro));
   myStepper.step(giro); // 180 graus
   

   
   }
  
  
   
    
   

 
