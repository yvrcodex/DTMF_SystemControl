/* 
 * Arquivo: main.c
 * Descrição: Este arquivo contém o firmware DTMF para o microcontrolador ATmega328P.
 * Autor: Yasser Oliveira
 * Universidade: Pontifícia Universidade Católica de Minas Gerais
 * Licença: MIT License
 */

//================= DIRETIVAS =====================

#include "../include/atmega328p_config.h"        //Cabeçalho Definições

//============= INICIANDO PROTOTIPOS ===============================

bool check_password(uint8_t *password);
void loading(void);



int main(){



//=================== SETUP INICIAL =================

    DDRB    &= ~0x1F;       // define os pinos PB0 à PB4 como entrada sem alterar o estado dos outros
    PORTB   &= ~0x1E;       // Garante que os pinos Q1 Q2 Q3 Q4 iniciem em zero.
    UCSR0B  &= ~0x18;       // desabilita RX (bit4) e TX(bit3) para trabalho com os pinos do PORTD no Arduino

    loading();              //animação inicial


    while(true)
    {



    }//fim while
}//fim main


//============= SUB ROTINAS ======================


// Função para verificar se a sequência de tons corresponde a uma senha
bool check_password(uint8_t *password)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (read[i] != password[i]) // Verifica cada elemento da sequência com a senha
            return false;           // Se houver uma diferença, retorna falso
    }
    return true; // Se a sequência corresponder à senha, retorna verdadeiro
}