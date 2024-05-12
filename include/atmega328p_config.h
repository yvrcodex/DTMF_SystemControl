/* 
 * Arquivo: ATMEGA328P_CONFIG_H
 * Descrição: Este arquivo contém as definições iniciais para o microcontrolador ATmega328P.
 */

#ifndef ATMEGA328P_CONFIG_H
#define ATMEGA328P_CONFIG_H



// ================ INCLUSÃO DIRETIVAS =======================


#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI librar


// ================ DEFINIÇÃO PINOS ==========================

// DISPLAY TFT ST7789 240X240
#define TFT_RST     PB0     // RST (reset)         - Pino 8  do Arduino Uno (Porta B, Bit 0)
#define TFT_DC      PB1     // DC (data/command)   - Pino 9  do Arduino Uno (Porta B, Bit 1)
#define TFT_CS      PB2     // CHIP SELECT         - Pino 10 do Arduino Uno (Porta B, Bit 2)
#define TFT_MOSI    PB3     // MOSI (SPI data pin) - Pino 11 do Arduino Uno (Porta B, Bit 3)
#define TFT_SCLK    PB5     // SCLK (SPI sclk pin) - Pino 13 do Arduino Uno (Porta B, Bit 5)


// MODULO DTMF MT8870
#define STQ     PC0   // Saída de Estado (Output State)     - Pino A0 do Arduino Uno (Porta C, Bit 0)
#define Q1      PC1   // Saída do primeiro dígito DTMF      - Pino A1 do Arduino Uno (Porta C, Bit 1)
#define Q2      PC2   // Saída do segundo dígito DTMF       - Pino A2 do Arduino Uno (Porta C, Bit 2)
#define Q3      PC3   // Saída do terceiro dígito DTMF      - Pino A3 do Arduino Uno (Porta C, Bit 3)
#define Q4      PC4   // Saída do quarto dígito DTMF        - Pino A4 do Arduino Uno (Porta C, Bit 4)



// ================= INSTANCIA GLOBAL ======================

// Instância da Adafruit ST7789 TFT library
extern Adafruit_ST7789 tft ;


// ================= DEFINIÇÕES CONSTANTES =================

//#define PCINT2      _VECTOR(5)          // Pin Change Interrupt Request 1 
#define BAUD 9600                       // Taxa de baud
#define MYUBRR F_CPU / 16 / BAUD - 1    // Valor de UBRR para a configuração da UART

#define DTMF_1          0x01        //  1 (frequências: 697 Hz e 1336 Hz)
#define DTMF_2          0x02        //  2 (frequências: 697 Hz e 1477 Hz)
#define DTMF_3          0x03        //  3 (frequências: 770 Hz e 1209 Hz)
#define DTMF_4          0x04        //  4 (frequências: 770 Hz e 1336 Hz)
#define DTMF_5          0x05        //  5 (frequências: 770 Hz e 1477 Hz)
#define DTMF_6          0x06        //  6 (frequências: 852 Hz e 1209 Hz)
#define DTMF_7          0x07        //  7 (frequências: 852 Hz e 1336 Hz)
#define DTMF_8          0x08        //  8 (frequências: 852 Hz e 1477 Hz)
#define DTMF_9          0x09        //  9 (frequências: 941 Hz e 1209 Hz)
#define DTMF_0          0x00        //  0 (frequências: 697 Hz e 1209 Hz)
#define DTMF_HASH       0x0E        //  # (frequências: 941 Hz e 1477 Hz)
#define DTMF_ASTERISK   0x0F        // .* (frequências: 941 Hz e 1209 Hz)
#define DTMF_A          0x0A        //  A (frequências: 941 Hz e 1336 Hz)
#define DTMF_B          0x0B        //  B (frequências: 941 Hz e 1477 Hz)
#define DTMF_C          0x0C        //  C (frequências: 697 Hz e 1633 Hz)
#define DTMF_D          0x0D        //  D (frequências: 770 Hz e 1633 Hz)




// ========== DEFINIÇÃO DOS TONS DTMF VIA ENUM =============
/*typedef enum : uint8_t {

    DTMF_1 = 0x01,        //  1 (frequências: 697 Hz e 1336 Hz)
    DTMF_2,              //  2 (frequências: 697 Hz e 1477 Hz)
    DTMF_3,              //  3 (frequências: 770 Hz e 1209 Hz)
    DTMF_4,              //  4 (frequências: 770 Hz e 1336 Hz)
    DTMF_5,              //  5 (frequências: 770 Hz e 1477 Hz)
    DTMF_6,              //  6 (frequências: 852 Hz e 1209 Hz)
    DTMF_7,              //  7 (frequências: 852 Hz e 1336 Hz)
    DTMF_8,              //  8 (frequências: 852 Hz e 1477 Hz)
    DTMF_9,              //  9 (frequências: 941 Hz e 1209 Hz)
    DTMF_0,               //  0 (frequências: 697 Hz e 1209 Hz)
    DTMF_HASH,           //  # (frequências: 941 Hz e 1477 Hz)
    DTMF_ASTERISK,        // .* (frequências: 941 Hz e 1209 Hz)
    DTMF_A,              //  A (frequências: 941 Hz e 1336 Hz)
    DTMF_B,              //  B (frequências: 941 Hz e 1477 Hz)
    DTMF_C,              //  C (frequências: 697 Hz e 1633 Hz)
    DTMF_D              //  D (frequências: 770 Hz e 1633 Hz)

} dtmf;
*/



#endif
