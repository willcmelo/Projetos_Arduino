#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
char UART2_rxBuffer [ 8 ] ;
String  txt = "";

// ARDUINO UNO 2 - PLACA ESCRAVO

void setup()
{
  Serial.begin(9600);
  // Inicializa o display
  display.begin(SSD1306_SWITCHCAPVCC);
  // Apaga o display
  display.clearDisplay();
   //INICIALIZAÇÃO DO BARRAMENTO COM O ESCRAVO
  //NESSE CASO, HÁ ARGUMENTO QUE É O PRÓPRIO END. DO ESCRAVO
    Wire.begin(10);
  
  //FUNÇÃO QUE INDICA UMA FUNÇÃO QUE TRABALHA A MENSAGEM DO MESTRE
    Wire.onReceive(RecebeMsg);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(1,1);
    display.print("Rede I2C");
    display.display();      
   
}

void loop()
{
  //NESSE CASO, ESCRAVO APENAS RECEBE A INFORMAÇÃO DO MESTRE

}

void RecebeMsg(int howMany)
{
  
    //FUNÇÃO QUE INDICA QUANDO O BARRAMENTO ESTÁ DISPONÍVEL
  while(Wire.available())
    {
     
      UART2_rxBuffer [0]= Wire.read();
      UART2_rxBuffer [1]= Wire.read();
      UART2_rxBuffer [2]= Wire.read();
      UART2_rxBuffer [3]= Wire.read();
      UART2_rxBuffer [4]= Wire.read();
      UART2_rxBuffer [5]= Wire.read();
      UART2_rxBuffer [6]= Wire.read();
      UART2_rxBuffer [7]= Wire.read();

      for (int x = 0; x<8 ; x++)
          {
            txt+=UART2_rxBuffer[x];
          }
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(2);
            display.setCursor(1,1);
            display.print(txt);
            display.display();

    }
}
