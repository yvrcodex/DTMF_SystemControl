/*
 * Arquivo: main.c
 * Descrição: Este arquivo contém o firmware DTMF para o microcontrolador ATmega328P.
 * Autor: Yasser Oliveira
 * Universidade: Pontifícia Universidade Católica de Minas Gerais
 * Licença: MIT License
 */

//================= DIRETIVAS =====================

#include "../include/atmega328p_config.h" //Cabeçalho Definições

//============= INICIANDO PROTOTIPOS ===============================

bool check_password(uint8_t *password);
void loading(void);
void reading();

// ============= DEFINES UNIDADE DE COMPILAÇAO LOCAL ==============

#define KEYWORD_MAX_LENGTH 4 // Comprimento máximo da sequência de tons DTMF

// ============ VARIAVEIS GLOBAL ==================================

volatile bool interrupt_flag = 0;
uint8_t keyword_read[KEYWORD_MAX_LENGTH];
uint8_t keyword_sequence = 0;
uint8_t keyword;
uint8_t cursor_pos;



// ============ PASSWORD PARA ATIVAÇÃO ============================

uint8_t password_A1[] = {DTMF_1, DTMF_0, DTMF_8};        // ATIVAÇÃO RELÉ A1
uint8_t password_A2[] = {DTMF_5, DTMF_ASTERISK, DTMF_3}; // ATIVAÇÃO RELÉ A2
uint8_t password_A3[] = {DTMF_7, DTMF_HASH, DTMF_A};     // ATIVAÇÃO RELÉ A3
uint8_t password_A4[] = {DTMF_B, DTMF_C, DTMF_D};        // ATIVAÇÃO RELÉ A4

int main()
{

  DDRB    &= ~0x1F;   // define os pinos PB0 à PB4 como entrada sem alterar o estado dos outros
  PORTC   &= ~0xFF;   // Garante que os pinos PINC6 a PINC0 iniciem em zero;
  UCSR0B  &= ~0x18;   // desabilita RX (bit4) e TX(bit3) para trabalho com os pinos do PORTD no Arduino
  PORTD   &= ~0x10;   // garante que o PD5  PCINT21  pino 5 arduino esteja em LOW

  PCICR   |= (1 << PCIE2);     // Habilita a interrupção via PORTD (PCINT16-23)
  PCMSK2  |= (1 << PCINT21);   // habilita interrupção para PCINT21 (PD5) (pino 5 arduino)
  SREG    |= 0x80;             // Habilitar interrupções globais bit (I = 1)


  loading(); // animação inicial

  while (true) // LOOP INFINITO
  {

    bool signal = PINC & (1 << STQ); // Lê o estado do STQ: BIT0 do PC0 (PINO A0)

    if (signal) // / Se Houver sinal do STQ e o tom  for diferente de #
    {
      keyword = (PINC & 0x1E) >> 1; // key recebe Q1 Q2 Q3 Q4, e descarta os outros bits. 0b0000xxxx

      if (keyword != DTMF_ASTERISK && keyword_sequence < KEYWORD_MAX_LENGTH)
      {

        keyword_read[keyword_sequence++] = keyword; // adiciona o tone à sequencia;

        dtmf_dispChar(keyword);
      }//fim if

      else if(keyword == DTMF_ASTERISK )
      {
          PORTD |= (1 << PD5); // ATIVA INTERRUPÇÃO  
          _delay_ms(1000);
          tft.fillScreen(ST77XX_BLACK);

      }// fim else
    }

  } // fim if
} // fim main


// ============================== INTERUPTION FUNCTION ======================
ISR(PCINT2_vect){

  if(PD5){

  check_password(password_A1);
  
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(8); // Tamanho da fonte grande
  tft.setCursor(80, 50);
  tft.println("A1 ");

  tft.setTextSize(3); // Tamanho da fonte grande
  tft.setCursor(35, 130);
  tft.println("ATIVACTED");

  }else{
  
  tft.setTextSize(3); // Tamanho da fonte grande
  tft.setCursor(35, 130);
  tft.println("INVALID");
  tft.setCursor(35, 150);
  tft.println("PASSWORD");

  }

  PORTD &= ~(1 << PD5);
}
//=====================================================================================


// ======================= DIPLAY PRINT TONE ==========================================
uint8_t dtmf_dispChar (uint8_t keyword_value){


  extern uint8_t cursor_pos;

  tft.setTextSize(3);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(cursor_pos, 50);

  switch (keyword_value)
  {

  case DTMF_1:            tft.setCursor(cursor_pos, 50); tft.println("1");   break;

  case DTMF_2:            tft.setCursor(cursor_pos, 50); tft.println("2");   break;

  case DTMF_3:            tft.setCursor(cursor_pos, 50); tft.println("3");   break;

  case DTMF_4:            tft.setCursor(cursor_pos, 50); tft.println("4");   break;

  case DTMF_5:            tft.setCursor(cursor_pos, 50); tft.println("5");   break;

  case DTMF_6:            tft.setCursor(cursor_pos, 50); tft.println("6");   break;

  case DTMF_7:            tft.setCursor(cursor_pos, 50); tft.println("7");   break;

  case DTMF_8:            tft.setCursor(cursor_pos, 50); tft.println("8");   break;

  case DTMF_9:            tft.setCursor(cursor_pos, 50); tft.println("9");   break;

  case DTMF_0:            tft.setCursor(cursor_pos, 50); tft.println("0");   break;

  case DTMF_HASH:         tft.setCursor(cursor_pos, 50); tft.println("#");   break;

  case DTMF_ASTERISK:     tft.setCursor(cursor_pos, 50); tft.println("#");   break;

  default:  tft.println("ERROR");
  break;
  }

  cursor_pos+= 5;

}

// ================== PASSWORD CHECK ===================================================
bool check_password(uint8_t *password) // Função para verificar se a sequência de tons corresponde a uma senha
{
  for (uint8_t i = 0; i < KEYWORD_MAX_LENGTH; i++)
  {
    if (keyword_read[i] != password[i]) // Verifica cada elemento da sequência com a senha
      return false;                     // Se houver uma diferença, retorna falso
  }
  return true; // Se a sequência corresponder à senha, retorna verdadeiro
} //fim check_password

// ================================ TRY DELETE ======================================
uint8_t dmtf_keywordChar (uint8_t keyword_read_char[]){

    uint8_t keyword_char[KEYWORD_MAX_LENGTH];
    uint8_t keyword_value_char;

    for(uint8_t value = 0; value < KEYWORD_MAX_LENGTH; value++)
    {
        switch (keyword_read_char[value]) {

            case DTMF_1:      keyword_value_char = '1'; break;

            case DTMF_2:      keyword_value_char = '2'; break;

            case DTMF_3:      keyword_value_char = '3'; break;

            case DTMF_4:      keyword_value_char = '4'; break;

            case DTMF_5:      keyword_value_char = '5'; break;

            case DTMF_6:      keyword_value_char = '6'; break;

            case DTMF_7:      keyword_value_char = '7'; break;

            case DTMF_8:      keyword_value_char = '8'; break;

            case DTMF_9:      keyword_value_char = '9'; break;

            case DTMF_0:      keyword_value_char = '0'; break;

            case DTMF_HASH:   keyword_value_char = '*'; break;

            case DTMF_ASTERISK: keyword_value_char= '#'; break;

            default:   keyword_value_char = '?'; break; // Caractere padrão para valores não especificados       

    }//fim switch

      keyword_char[value++] =  keyword_value_char;

    }//fim while

}//fim dmtf_keywordChar
