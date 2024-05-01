// ============== LIBRARIES ========================
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

// ============== DEFINIÇÃO CONSTANTE ============
#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1
#define MAX_SEQUENCE_LENGTH 20

// ============== VARIAVEIS GLOBAL ===================
uint8_t read[MAX_SEQUENCE_LENGTH]; // Array para armazenar a sequência de tons
uint8_t sequence_length = 0;       // Variável para rastrear o comprimento atual da sequência
uint8_t number;                    // Variável para armazenar o número do tom recebido
uint8_t keyword = 0;               // Variável para determinar qual senha foi correspondida

// -------------- PASSWORDS ---------------------------
uint8_t password1[] = {0x00, 0x00, 0x00}; // Primeira senha
uint8_t password2[] = {8, 8, 8};          // Segunda senha
uint8_t password3[] = {2, 2, 3};          // Terceira senha

// ============= DECLARAÇÃO PROTOTIPOS ===============
void USART_Init(unsigned int ubrr);      // Inicializa a comunicação serial
void USART_Transmit(unsigned char data); // Transmite dados via comunicação serial
void USART_Println(const char *s);       // Imprime uma string seguida de nova linha
bool check_password(uint8_t *password);  // Verifica se a sequência de tons corresponde a uma senha

// ================= MAIN ============================
int main(void)
{
    USART_Init(MYUBRR); // Inicializa a comunicação serial

    DDRD &= 0xF8;  // Configura os pinos D3 até D7 como entrada
    DDRB = 0xF7;  // Para os pinos 9, 10 e 11 como saída, e o pino 8 como entrada
    PORTB = 0x00; // Define os pinos 8, 9 e 10 em LOW

    USART_Println("\nREADING TONE...");

    while (1)
    {   
       
        if (PINB & (1 << PINB0)) // Verifica o estado do pino 8 (PB0)

        {
             _delay_ms(10);
            
            // Se o botão estiver pressionado, verifica se a sequência de tons corresponde a alguma senha
            if (check_password(password1))
            {
                USART_Println("\nativando relé 1"); // Ativa o relé 1 se a senha for correspondida

                PORTB |= (1 << PB1); // Define o pino 9 (PB1) como HIGH, mantendo os outros pinos inalterados
            }
            else if (check_password(password2))
            {
                USART_Println("\nativando relé 2"); // Ativa o relé 2 se a senha for correspondida
                PORTB |= (1 << PB2);                // Define o pino 10 como HIGH, mantendo os outros pinos inalterados
            }
            else if (check_password(password3))
            {
                USART_Println("\nativando relé 3"); // Ativa o relé 3 se a senha for correspondida
                PORTB |= (1 << PB3);                // Define o pino 11 como HIGH, mantendo os outros pinos inalterados
                
            }
            else
            {
                USART_Println("\nINVALID PASSWORD..."); // Imprime mensagem de senha inválida
            }
            _delay_ms(5000);
            PORTB &= ~((1 << PB1) | (1 << PB2) | (1 << PB3)); // Define os pinos 9, 10 e 11 como LOW, mantendo os outros pinos inalterados

            sequence_length = 0; // Reseta a sequência
            _delay_ms(20);      // Aguarda antes de ler uma nova sequência
        }
        else
        {
            bool signal = PIND & (1 << PIND7); // Lê o estado do pino D7
            _delay_ms(20);
            if (signal) // Se um sinal for detectado no pino D7
            {
                _delay_ms(100);              // Aguarda 100ms para evitar debouncing
                number = (PIND & 0x78) >> 3; // Lê o número do tom dos pinos D3 a D6

                if (sequence_length < MAX_SEQUENCE_LENGTH)
                {
                    read[sequence_length++] = number; // Adiciona o tom à sequência
                }

                USART_Transmit(number + '0'); // Imprime o número do tom recebido
                USART_Transmit('\n');         // Imprime uma nova linha
            }
        } // FIM ELSE
    } // FIM WHILE

    return 0;
} // FIM MAIN

// ################# SUB ROTINAS ###########################

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

// Inicializa a comunicação serial
void USART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Transmite um byte via comunicação serial
void USART_Transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;        // Aguarda o buffer de transmissão estar vazio
    UDR0 = data; // Transmite o byte
}

// Imprime uma string seguida de nova linha via comunicação serial
void USART_Println(const char *s)
{
    while (*s)
    {
        USART_Transmit(*s++); // Transmite cada caractere da string
    }
    USART_Transmit('\r'); // Transmite o caractere de retorno de carro (CR)
    USART_Transmit('\n'); // Transmite o caractere de nova linha (LF)
}
