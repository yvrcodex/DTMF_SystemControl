// include PlatformIO extension VSCODE
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

// INICIAR COMUNICAÇÃO SERIAL VIA REGISTER UBBR
int x = 1;

void USART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_Println(const char *s)
{
    while (*s)
    {
        USART_Transmit(*s++);
    }
    USART_Transmit('\r');
    USART_Transmit('\n');
}

// FUNÇÃO PRINT USANDO FUNCTION

void printDTMF(char key, const char *tone)
{
    char buffer[50];
    sprintf(buffer, "Tecla: %c, Tons DTMF: %s", key, tone);
    USART_Println(buffer);
}

int main(void)
{
    // ///DDRD &= ~((1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7));Configura os pinos D3 a D7 como entrada

    DDRD &= 0xF8; // Configura os pinos D3 até D7 como entrada
    DDRB &= 0xFE; // Configura o pino 8 (PB0) como entrada

    USART_Init(MYUBRR);

    while (1)
    {
        uint8_t number;

        // Verifica se o pino 8 (PB0) está em nível alto (HIGH)
        if (PINB & (1 << PINB0))
        {
            // Se estiver em nível alto, sai do loop
            USART_Println("Sequência de tons encerrada");
            break;
        }

        bool signal = PIND & (1 << PIND7); // leitura pino D7

        if (signal)
        {
            _delay_ms(200);              // Delay para debouncing
            number = (PIND & 0x78) >> 3; // leitura dos  pinos D3 a D6 e ajusta a posição dos bits
            switch (number)
            {

            case 0x01: // b0001

                printDTMF('1', "697 Hz e 1209 Hz");

                break;

            case 0x02: // b0010

                printDTMF('2', "697 Hz e 1336 Hz");
                break;

            case 0x03: // b0011
                printDTMF('3', "697 Hz e 1477 Hz");
                break;

            case 0x04: // b0100

                printDTMF('4', "770 Hz e 1209 Hz");
                break;

            case 0x05: // b0101

                printDTMF('5', "770 Hz e 1336 Hz");
                break;

            case 0x06: // b0110

                printDTMF('6', "770 Hz e 1477 Hz");
                break;

            case 0x07: // b0111

                printDTMF('7', "852 Hz e 1209 Hz");
                break;

            case 0x08: // b1000
                printDTMF('8', "852 Hz e 1336 Hz");
                break;

            case 0x09: // b1001

                printDTMF('9', "852 Hz e 1477 Hz");
                break;

            case 0x0A: // b1010

                printDTMF('0', "941 Hz e 1336 Hz");
                break;

            case 0x0B: // b1011
            
                printDTMF('*', "941 Hz e 1209 Hz");
                break;

            case 0x0C: // b1100
                printDTMF('#', "941 Hz e 1477 Hz");
                break;

            default:
                break;
            }
        }
    }

    return 0;
}

/* IMplementação bateria de teste. Comparação de saidas */