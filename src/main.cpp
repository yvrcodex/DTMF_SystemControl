/* 
 * Arquivo: main.c
 * Descrição: Este arquivo contém o firmware DTMF para o microcontrolador ATmega328P.
 * Autor: Yasser Oliveira
 * Universidade: Pontifícia Universidade Católica de Minas Gerais
 * Licença: MIT License
 */

//================= DIRETIVAS =====================

#include "../include/atmega328p_config.h"   //Cabeçalho Definições

//============= INICIANDO PROTOTIPOS ===============================

bool check_password(uint8_t *password);
void loading(void);
void reading();

// ============= DEFINES UNIDADE DE COMPILAÇAO LOCAL ==============

#define KEYWORD_MAX_LENGTH 8        // Comprimento máximo da sequência de tons DTMF


// ============ VARIAVEIS GLOBAL ==================================

uint8_t keyword_read[KEYWORD_MAX_LENGTH];
uint8_t keyword_sequence = 0;
uint8_t keyword;

// ============ PASSWORD PARA ATIVAÇÃO ============================

DTMF password_A1[] = {DTMF_1, DTMF_0, DTMF_8};                 // ATIVAÇÃO RELÉ A1
DTMF password_A2[] = {DTMF_5, DTMF_ASTERISK, DTMF_3};          // ATIVAÇÃO RELÉ A2
DTMF password_A3[] = {DTMF_7, DTMF_HASH, DTMF_A};              // ATIVAÇÃO RELÉ A3
DTMF password_A4[] = {DTMF_B, DTMF_C, DTMF_D};                 // ATIVAÇÃO RELÉ A4


int main(){

    //=================== SETUP INICIAL =================

    DDRB    &= ~0x1F;       // define os pinos PB0 à PB4 como entrada sem alterar o estado dos outros
    PORTC   &= ~0x1E;       // Garante que os pinos Q1 Q2 Q3 Q4 iniciem em zero.
    UCSR0B  &= ~0x18;       // desabilita RX (bit4) e TX(bit3) para trabalho com os pinos do PORTD no Arduino

    loading();              //animação inicial


    while(true)             // LOOP INFINITO
    {

     bool signal = PINC & (1 << STQ);                        // Lê o estado do STQ: BIT0 do PC0 (PINO A0)

        if (signal)
        {                                                   // Se Houver sinal do STQ
            keyword = (PINC & 0x1E) >> 1;                   // key recebe Q1 Q2 Q3 Q4, e descarta os outros bits. 0b0000xxxx

                if (keyword_sequence < KEYWORD_MAX_LENGTH)
                    {
                        keyword_read[keyword_sequence++] = keyword; // adiciona o tone à sequencia;
                    }
        }

    }//fim while
}//fim main


//============= SUB ROTINAS ======================


// Função para verificar se a sequência de tons corresponde a uma senha
bool check_password(uint8_t *password)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (keyword_read[i] != password[i]) // Verifica cada elemento da sequência com a senha
            return false;           // Se houver uma diferença, retorna falso
    }
    return true; // Se a sequência corresponder à senha, retorna verdadeiro
}