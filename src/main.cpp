#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI librar
// #include <Wire.h>


// Definições dos pinos do display ST7789
#define TFT_DC 9    // DC (data/command)
#define TFT_RST 8   // RST (reset)
#define TFT_MOSI 11 // MOSI (SPI data pin)
#define TFT_SCLK 13 // SCLK (SPI sclk pin)
#define TFT_CS 10   // CHIP SELECT
#define PD5_PIN (1 << PD5)
#define KEYWORD_MAX_LENGTH 4 // Comprimento máximo da sequência de tons DTMF

// MODULO DTMF MT8870 PINOUT
#define Q1      PC0   // Saída do primeiro dígito DTMF      - Pino A0 do Arduino Uno (Porta C, Bit 0) 
#define Q2      PC1   // Saída do segundo dígito DTMF       - Pino A1 do Arduino Uno (Porta C, Bit 1)
#define Q3      PC2   // Saída do terceiro dígito DTMF      - Pino A2 do Arduino Uno (Porta C, Bit 2)
#define Q4      PC3   // Saída do quarto dígito DTMF        - Pino A3 do Arduino Uno (Porta C, Bit 3)
#define STQ     PC4   // Saída de Estado (Output State)     - Pino A4 do Arduino Uno (Porta C, Bit 4)

// DUAL TONE CHARACTERE DEFINES
#define DTMF_1          0x01        //  1 - (frequências: 697 Hz e 1336 Hz)
#define DTMF_2          0x02        //  2 - (frequências: 697 Hz e 1477 Hz)
#define DTMF_3          0x03        //  3 - (frequências: 770 Hz e 1209 Hz)
#define DTMF_4          0x04        //  4 - (frequências: 770 Hz e 1336 Hz)
#define DTMF_5          0x05        //  5 - (frequências: 770 Hz e 1477 Hz)
#define DTMF_6          0x06        //  6 - (frequências: 852 Hz e 1209 Hz)
#define DTMF_7          0x07        //  7 - (frequências: 852 Hz e 1336 Hz)
#define DTMF_8          0x08        //  8 - (frequências: 852 Hz e 1477 Hz)
#define DTMF_9          0x09        //  9 - (frequências: 941 Hz e 1209 Hz)
#define DTMF_0          0x0A        //  0 - (frequências: 697 Hz e 1209 Hz)
#define DTMF_HASH       0x0B        //  # - (frequências: 941 Hz e 1477 Hz)
#define DTMF_ASTERISK   0x0C        // .* - (frequências: 941 Hz e 1209 Hz)

// Instância da Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


bool check_password(uint8_t *password);
void loading(void);
void reading();
uint8_t disp_asterisk(bool x);
uint8_t active(bool x);


uint8_t TEST_password_A1[] = {DTMF_1, DTMF_8, DTMF_2, DTMF_6};        // ATIVAÇÃO RELÉ A1
uint8_t password_A1[]      = {DTMF_1, DTMF_8, DTMF_2, DTMF_6};         // ATIVAÇÃO RELÉ A1


uint8_t password_A2[] = {DTMF_5, DTMF_HASH, DTMF_3}; // ATIVAÇÃO RELÉ A2
uint8_t TEST_password_A2[] = {DTMF_5, DTMF_HASH, DTMF_3}; // ATIVAÇÃO RELÉ A2

uint8_t trigger_hash =  DTMF_HASH;

uint8_t keyword_read[KEYWORD_MAX_LENGTH];
uint8_t keyword_sequence = 0;
uint8_t keyword;
uint8_t cursor_posX = 20;
uint8_t cursor_posY = 30;
int i = 0;
uint8_t pinos = 0;

volatile uint8_t interrupt_flag = 0;

void loading(void);
void reading(void);
uint8_t dtmf_dispChar (uint8_t keyword_value);

void setup(void)
{

  DDRB    &= ~0x1F;   // define os pinos PB0 à PB4 como entrada sem alterar o estado dos outros
  PORTC   &= ~0xFF;   // Garante que os pinos PINC6 a PINC0 iniciem em zero;
  UCSR0B  &= ~0x18;   // desabilita RX (bit4) e TX(bit3) para trabalho com os pinos do PORTD no Arduino
  PORTD   &= ~0x10;   // garante que o PD5  PCINT21  pino 5 arduino esteja em LOW

  PCICR   |= (1 << PCIE2);     // Habilita a interrupção via PORTD (PCINT16-23)
  PCMSK2  |= (1 << PCINT21);   // habilita interrupção para PCINT21 (PD5) (pino 5 arduino)
  SREG    |= 0x80;             // Habilitar interrupções globais bit (I = 1)


  PCMSK2 |= (1 << PCINT21);


  Serial.begin(9600);
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  bool x = 1;

  loading();
  disp_asterisk(true);
  _delay_ms(3000);

  

  while (true) // LOOP INFINITO
  {


   
    PORTC |= (1<<STQ);
    bool signal = (PINC |= (1 << STQ)); // Lê o estado do STQ: BIT0 do PC0 (PINO A4)

    if (signal && !interrupt_flag) // / Se Houver sinal do STQ e o tom  for diferente de #
    {
     

      pinos =  (TEST_password_A1[i]) ;
      keyword = (pinos) ; // key recebe Q1 Q2 Q3 Q4, e descarta os outros bits. 0b0000xxxx

      if (keyword != DTMF_ASTERISK && keyword_sequence < KEYWORD_MAX_LENGTH)
      {

        keyword_read[keyword_sequence++] = keyword; // adiciona o tone à sequencia;
        dtmf_dispChar(keyword);
        cursor_posX+= 50;
        i++;

        
      }//fim if

      else if (!interrupt_flag)
      {

      PORTD |= (1 << PD5); // ATIVA INTERRUPÇÃO  
      tft.fillScreen(ST77XX_BLACK);
            reading();
      
      }// fim else
    }
    _delay_ms(300);
  } // fim if
} // fim main

// ============================== INTERUPTION FUNCTION ======================
ISR(PCINT2_vect){

  if(PIND & (1 << PD5)){

  check_password(password_A1);
  active(true);
  _delay_ms(2000);
  active(false);

  }else{
  
  tft.setTextSize(3); // Tamanho da fonte grande
  tft.setCursor(35, 130);
  tft.println("INVALID");
  tft.setCursor(35, 150);
  tft.println("PASSWORD");

  }
  _delay_ms(200);

  i = 0;
  interrupt_flag = 1;
}

/* PASSWORD CHECK */
bool check_password(uint8_t *password) // Função para verificar se a sequência de tons corresponde a uma senha
{
  for (uint8_t i = 0; i < KEYWORD_MAX_LENGTH; i++)
  {
    if (keyword_read[i] != password[i]) // Verifica cada elemento da sequência com a senha
      return false;                     // Se houver uma diferença, retorna falso
  }
  return true; // Se a sequência corresponder à senha, retorna verdadeiro
} //fim check_password

/* TFT DISPLAY CHARACTER */
uint8_t dtmf_dispChar (uint8_t keyword_value){


  extern uint8_t cursor_posX;
  extern uint8_t cursor_posY;

  tft.setTextSize(3);
  tft.setCursor(cursor_posX, cursor_posY);
  tft.setTextColor(ST77XX_BLACK);
  tft.println(" * ");
  tft.setTextColor(ST77XX_YELLOW);




  switch (keyword_value)
  {

  case DTMF_1:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 1 ");   break;

  case DTMF_2:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 2 ");   break;

  case DTMF_3:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 3 ");   break;

  case DTMF_4:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 4 ");   break;

  case DTMF_5:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 5 ");   break;

  case DTMF_6:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 6 ");   break;

  case DTMF_7:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 7 ");   break;

  case DTMF_8:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 8 ");   break;

  case DTMF_9:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 9 ");   break;

  case DTMF_0:            tft.setCursor(cursor_posX, cursor_posY); tft.println(" 0 ");   break;

  case DTMF_HASH:         tft.setCursor(cursor_posX, cursor_posY); tft.println(" # ");   break;

  case DTMF_ASTERISK:     tft.setCursor(cursor_posX, cursor_posY); tft.println(" # ");   break;

  default:  tft.println("ERROR");
  break;
  }
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(cursor_posX, cursor_posY);


}

/* PASSWORD ASTERISK */
uint8_t disp_asterisk(bool x){



  uint8_t set_cursor = cursor_posX;
  
  tft.setCursor(set_cursor, cursor_posY);

  tft.setTextSize(3);
  tft.setTextColor(ST77XX_RED);
  

  if(x){

  for (int i = 0; i < KEYWORD_MAX_LENGTH; i++)
  {

  tft.setCursor(set_cursor, cursor_posY);
  tft.println(" * ");
  set_cursor += 50;
  }


  }
  else{
  
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(cursor_posX, cursor_posY);
  tft.println(" * ");
  }
}


  uint8_t active(bool x){
  

  if(x)
  {

  tft.setTextColor(ST77XX_GREEN); 
  tft.setTextSize(6); // Tamanho da fonte grande
  tft.setCursor(83, 100);
  tft.println("A1 ");

  tft.setTextSize(3); // Tamanho da fonte grande
  tft.setCursor(35, 150);
  tft.println("ATIVACTED");
  }
  else
  {
  tft.setTextColor(ST77XX_BLACK); 
  tft.setTextSize(6); // Tamanho da fonte grande
  tft.setCursor(83, 100);
  tft.println("A1 ");

  tft.setTextSize(3); // Tamanho da fonte grande
  tft.setCursor(35, 150);
  tft.println("ATIVACTED");
  
  }
}

/* ANIMATION LOADING */
void loading(void)
{

  const int centerX = 120;
  const int centerY = 120;
  const int barWidth = 20;
  const int barHeight = 10;

  tft.setTextColor(ST77XX_BLUE);
  tft.setCursor(20, 200);
  tft.setTextSize(2);
  tft.println("Created by: Yasser");

  // Define a cor da barra de progresso
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(4); // Tamanho da fonte

  tft.setCursor(40, 10);
  tft.println("LOADING");


  // Desenha a barra de progresso
  for (int i = 0; i <= 100; i += 4)
  {
    int barLength = map(i, 0, 100, 0, 2 * centerX - barWidth);
    tft.fillRect(centerX - barLength / 2, centerY - barHeight / 2, barLength, barHeight, ST77XX_WHITE);
    delay(50); // Ajuste o tempo conforme necessário para a velocidade da animação
    tft.fillRect(centerX - barLength / 2, centerY - barHeight / 2, barLength, barHeight, ST77XX_BLACK);
  }
  tft.fillScreen(ST77XX_BLACK);
}

/* ANIMATION READING */
void reading(void)
{

  const int centerX = 120;      // coordenada x do centro da animação
  const int centerY = 120 + 30; // coordenada y do centro da animação
  const int radius = 40;        // raio da animação
  const int numDots = 200;      // número de pontos na animação
  const int dotSize = 6;        // tamanho dos pontos

  // Define a cor do texto como azul
  tft.setTextColor(ST77XX_BLUE);

  // Define o tamanho dos pontos
  tft.setTextSize(dotSize);
  // Define a cor dos pontos

  uint16_t dotColor = ST77XX_BLUE;

  tft.setTextSize(3);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(45, 20);
  tft.println("RECIVING");
  tft.setCursor(35, 45);
  tft.println("DUAL-TONE");

  // Loop para desenhar os pontos em um círculo
  while (true)
  {

    int i = 0;
    int j = 1;
    // Vamos repetir a animação algumas vezes para criar o efeito de loop

    for (int i = 0; i < numDots; ++i)
    {
      // Calcula as coordenadas do ponto no círculo
      int x = centerX + int(radius * cos(i * 2 * PI / numDots));
      int y = centerY + int(radius * sin(i * 2 * PI / numDots));

      // Desenha o ponto na tela
      tft.fillCircle(x, y, dotSize / 2, dotColor); // Desenha um círculo preenchido no lugar do po
    }
    for (i = 0; i < numDots; ++i)
    {

      // Calcula as coordenadas do ponto no círculo
      int x0 = centerX + int(radius * cos(i * 2 * PI / numDots));
      int y0 = centerY + int(radius * sin(i * 2 * PI / numDots));

      int x1 = centerX + int(radius * cos(j) * 2 * PI / numDots);
      int y1 = centerY + int(radius * sin(j) * 2 * PI / numDots);

      // Desenha o ponto na tela
      tft.fillCircle(x0, y0, dotSize / 2, ST77XX_YELLOW);

      _delay_ms(10);
      tft.fillCircle(x1, y1, dotSize / 2, dotColor);
      j++;
    }

  } // fim while
}

/*
void reading(void){



  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLUE);
  tft.setCursor(30, 10);
  tft.println("READING");

  tft.setTextSize(4);
  tft.setCursor(50, 100);
  tft.println(".");
  _delay_ms(500);

  tft.setCursor(55, 100);
  tft.println(".");
  _delay_ms(500);

  tft.setCursor(60, 100);
  tft.println(".");
  _delay_ms(500);

  tft.setCursor(65, 100);
  tft.println(".");
  _delay_ms(500);
}
/*
bool password_display(bool test){


  if(test) {

  tft.fillScreen(ST77XX_BLACK);

  // Imprime "PASSWORD CORRECT" em verde e centralizado na tela
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(4); // Tamanho da fonte

  tft.setCursor(60, 40);
  tft.println("VALID");
  tft.setCursor(30, 110);
  tft.println("PASSWORD");
  _delay_ms(1000);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(8); // Tamanho da fonte grande
  tft.setCursor(80, 50);
  tft.println("A1 ");

  tft.setTextSize(3); // Tamanho da fonte grande
  tft.setCursor(35, 130);
  tft.println("ATIVACTED");


  } else {

    tft.fillScreen(ST77XX_BLACK);

    // Imprime "PASSWORD CORRECT" em verde e centralizado na tela
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(4); // Tamanho da fonte

    tft.setCursor(40, 40);
    tft.println("INVALID");
    tft.setCursor(30, 110);
    tft.println("PASSWORD");


  }

  return test;

}

/*
void testlines(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color)
{
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5)
  {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5)
  {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6)
  {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = radius; x < tft.width(); x += radius * 2)
  {
    for (int16_t y = radius; y < tft.height(); y += radius * 2)
    {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
  {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
    {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles()
{
  tft.fillScreen(ST77XX_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0; t <= 15; t++)
  {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects()
{
  tft.fillScreen(ST77XX_BLACK);
  int color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1)
  {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0; i <= 16; i += 1)
    {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest()
{
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons()
{
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
} */