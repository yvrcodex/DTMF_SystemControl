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
#define EST     PC0   // Saída de Estado (Output State)     - Pino A0 do Arduino Uno (Porta C, Bit 0)
#define Q1      PC1   // Saída do primeiro dígito DTMF      - Pino A1 do Arduino Uno (Porta C, Bit 1)
#define Q2      PC2   // Saída do segundo dígito DTMF       - Pino A2 do Arduino Uno (Porta C, Bit 2)
#define Q3      PC3   // Saída do terceiro dígito DTMF      - Pino A3 do Arduino Uno (Porta C, Bit 3)
#define Q4      PC4   // Saída do quarto dígito DTMF        - Pino A4 do Arduino Uno (Porta C, Bit 4)



// ================= INSTANCIA GLOBAL ======================

// Instância da Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);



// ================= DEFINIÇÕES CONSTANTES =================


#define BAUD 9600                      // Taxa de baud
#define MYUBRR F_CPU / 16 / BAUD - 1   // Valor de UBRR para a configuração da UART
#define MAX_SEQUENCE_LENGTH 20         // Comprimento máximo da sequência de tons DTMF

#endif