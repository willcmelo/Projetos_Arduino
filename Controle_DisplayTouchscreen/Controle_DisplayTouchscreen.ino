#include "Adafruit_GFX.h" // Biblioteca Gráfica Adafruit
#include <MCUFRIEND_kbv.h> // Bibllioteca para controle do lcd 
#include "TouchScreen.h"

#define YP A3 // Y+ is on Analog1 (use A3 para o 9341)
#define XM A2 // X- is on Analog2 (use A2 para o 9341)
#define YM 9 // Y- is on Digital7 (use 9 para o 9341)
#define XP 8 // X+ is on Digital6 (use 8 para o 9341)
  
#define TS_MINX 150 // Use 150 para o 9341
#define TS_MINY 120 // Use 120 para o 9341
#define TS_MAXX 920
#define TS_MAXY 940  
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Cores que iremos utilizar em nosso projeto
#define PRETO   0x0000
#define VERMELHO     0xF800
#define VERDE   0x07E0
#define BRANCO 0xFFFF

//Definicao de cores
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

// Armazena o estado dos botões
bool valor_botao1 = 0;
bool valor_botao2 = 0;
bool valor_botao3 = 0;
bool valor_botao4 = 0;
//---------------------------------------------//
MCUFRIEND_kbv tft; // Objeto  de comunicação com  display
void setup() {
  uint16_t ID = tft.readID(); // Leitura do código de identificação do controlador
  tft.begin(ID); // Inicialização da tela
  telaInicial(); // Chamada da função responsável por renderizar o nosso painel de acesso
}
void telaInicial(){
  tft.setRotation(1); // Display é rotacionado para modo paisagem
  tft.fillScreen(BRANCO); // Tela  é preenchida pela cor Branca
  escreveTexto(50,10,"Controle do Carrinho",2,PRETO); // Texto é escrito na posição (50,0)
  criarBotao(110,50,90,30," UP",VERMELHO); // Criação do botão 3 do sistema
  criarBotao(60,100,100,30,"LEFT",VERMELHO); // Criação do botão 7 do sistema
  criarBotao(160,100,100,30,"RIGHT",VERMELHO); // Criação do botão 9 do sistema
  criarBotao(110,150,100,30,"DOWN",VERMELHO); // Criação do botão Apagar
  
}

void escreveTexto(int posx,int posy, String texto,int tamanho,int cor){ // Função criada para facilitar escrita de texto
  tft.setCursor(posx,posy); // Cursor é deslocado para posição passada como parâmetro
  tft.setTextColor(cor); // Cor a ser escrita é alterada conforme valor recebido como parâmetro
  tft.setTextSize(tamanho); // Tamanho da fonte é  alterado conforme parâmetro recebido
  tft.print(texto); // Texto passado por parâmetro é escrito na tela
}
void criarBotao(int posx,int posy, int largura, int altura,String texto,int cor) //
{
    //Create Red Button
  tft.fillRect(posx,posy, largura, altura, cor); // um quadrado começando em (posx,posy) é renderizado conforme parâmetros passados
  tft.drawRect(posx,posy, largura, altura,PRETO); // um quadrado de cor preta é desenhado ao redor do quadrado vermelho 
  tft.setCursor(posx+8,posy+4); // Cursor é deslocado para o pixel de posição (posx+8,posy+4)
  tft.setTextColor(BRANCO); // Cor do texto é alterada para Branco
  tft.setTextSize(3); // Fonte é alterada para tamanho 3
  tft.print(texto); // Texto é escrito em posição determinada
}


void loop() { // Cada uma das três telas que compõem o sistema é chamada a cada dois segundos

  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = tft.width() - (map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height() - (map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
  
      //Testa botao UP
      if ((p.x > 210 & p.x < 260)&& (p.y > 70 & p.y < 140))
      {
        if (valor_botao1 == 0)
        {
          
          criarBotao(110,50,90,30," UP",VERDE);
          delay(200);
          valor_botao1 = !valor_botao1;
        }
        else
        {
          
          criarBotao(110,50,90,30," UP",VERMELHO);
          delay(200);
          valor_botao1 = !valor_botao1;
        }
      }
  
      //Testa botao DOWN
      if ((p.x > 60 & p.x < 110)&& (p.y > 70 & p.y < 150))
      {
        if (valor_botao2 == 0)
        {
          criarBotao(110,150,100,30,"DOWN",VERDE); // Criação do botão Apagar
          delay(200);
          valor_botao2 = !valor_botao2;
        }
        else
        {
          
          criarBotao(110,150,100,30,"DOWN",VERMELHO);
          delay(200);
          valor_botao2 = !valor_botao2;
  
        }
      }
  
      //Testa botao LEFT
      if ((p.x > 140 & p.x < 180)&& (p.y >20 & p.y < 99))
      {
        if (valor_botao3 == 0)
        {
          criarBotao(60,100,100,30,"LEFT",VERDE); // Criação do botão Apagar
          delay(200);
          valor_botao3 = !valor_botao3;
        }
        else
        {
          criarBotao(60,100,100,30,"LEFT",VERMELHO); // Criação do botão Apagar
          delay(200);
          valor_botao3 = !valor_botao3;
        }
      }
  
      //Testa botao RIGHT
      if ((p.x > 140 & p.x < 180)&& (p.y > 100 & p.y < 190))
      {
        if (valor_botao4 == 0)
        {
          criarBotao(160,100,100,30,"RIGHT",VERDE); // Criação do botão Apagar
          delay(200);
          valor_botao4 = !valor_botao4;
        }
        else
        {
          criarBotao(160,100,100,30,"RIGHT",VERMELHO); // Criação do botão Apagar
          delay(200);
          valor_botao4 = !valor_botao4;
        }
      }
    
  }

}
