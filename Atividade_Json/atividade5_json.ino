
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Define o endereço do LCD no barramento I2C e o
// número de colunas e linhas (16x2)
LiquidCrystal_I2C lcd(0x27,16,2);
//Vetor para receber um caractere customizado
uint8_t custom_char[8];
//vetor para arazenar o pacote Json recebido pela serial
char buf[100];
//Objetos de entrada
char inputserial[] = "";
String inputString = "";        
bool stringComplete = false;  
int i = 0;
const char input[] = "{\"dispositivo\":\"display\",\"posicao\":[1],\"dados\":[14,31,21,31,17,31,14]}";
void setup()
{
Serial.begin(9600);
while (!Serial);

lcd.init(); // Inicializa LCD
lcd.backlight(); // Liga luz do LCD
lcd.print("custom Chars"); //escreve no lcd
lcd.setCursor(0,0);
      
Serial.println("Olá sou a interface inteligente para LCD");
Serial.println("Crie caracteres personalizados enviando string JSON");
Serial.println("\"{dispositivo:nome,posição:valor,dados:[b0,b1,b2,b3,b4,b5,b6,b7]}\"");
// reserve 200 bytes for the inputString:
inputString.reserve(200);
}

void loop()
{

 if (Serial.available())  //verifica se tem dados diponíveis para leitura
  {
  
    ////// Pacote a ser enviado pela Serial {"disp":"display","pos":1,"dados":[14,31,21,31,17,31,14]}
    ////// Será mostrado no display o caractere personalizado/////////
   
    // lê 1 byte da serial
    char inputserial = (char)Serial.read();
    // adiciona o byte para variável inChar
    inputString += inputserial;
    //incrementa a string
    if (inputserial == '\n') 
    {  
          stringComplete = true;  
    }   
    
     if (stringComplete) {
        
        Serial.print("String = ");
        Serial.println(inputString);
        inputString.toCharArray(buf, 100);
        
        Serial.print("buf = ");
        Serial.println(buf);
        
        JSONVar myObject = JSON.parse(buf);
        JSONVar value = myObject["dados"];
        if(myObject.hasOwnProperty("disp")) 
           {
             Serial.print("myObject[\"disp\"] = ");
             Serial.println(myObject["disp"]);
           } 
        
        if(myObject.hasOwnProperty("pos")) 
           {
             Serial.print("myObject[\"pos\"] = ");
             Serial.println((int)myObject["pos"]);
           }
        Serial.print("JSON.typeof(dados) =  ");
        Serial.println(JSON.typeof("dados"));      
        Serial.print("myObject[\"dados\"] = ");
        Serial.println((int)myObject["dados"]);    
        Serial.print("JSON.typeof(myObject[\"dados\"] = ");  
        Serial.println(JSON.typeof(value));                  
        Serial.print("JSON.length(myObject[\"dados\"] = ");  
        Serial.println(value.length());
        Serial.print("JSON.(myObject[\"dados\"] = ");        
        
        for(int i = 0; i < value.length(); i++)
          {
            Serial.print("dados[0] = ");
            Serial.println((int)value[i]);   //valor dos dados
            custom_char[i] = (int)value[i];
          }         
        
        // Limpa a String
        inputString = "";
        stringComplete = false;
  }  
      //envia para o display o caractere personalizado
      lcd.createChar(1,custom_char);
      lcd.setCursor(8,1);
      lcd.write(1);  
      
  
  }
}
