// ================== HEADERS ======================================

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>   



// Instância da Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


// =================== DISPLAY FUNCTIONS ========================= //



//====================  TELA DE CARREGAMENTO ======================
void loading(void)
{

  const int centerX = 120;
  const int centerY = 120;
  const int barWidth = 20;
  const int barHeight = 10;

  // Define a cor da barra de progresso
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(4); // Tamanho da fonte

  tft.setCursor(40, 1);
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

//===================================================================


//======================= TELA DE LEITURA ==========================
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
// =================================================================== //