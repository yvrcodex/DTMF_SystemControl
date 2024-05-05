<h3 align="center">Interrupções no Atmega328p</h3>

---

## Introdução

Interrupções são uma característica essencial dos microcontroladores como o Atmega328p, permitindo que eles respondam a eventos externos sem a necessidade de verificação constante. Neste guia, exploraremos as interrupções em detalhes, começando com as interrupções externas e sua configuração.

## O Bit I do Registrador de Status (SREG)

O Atmega328p possui um bit responsável por habilitar ou desabilitar todas as interrupções de uma vez, conhecido como o bit I no Registrador de Status (SREG).
Quando uma interrupção é acionada, o microcontrolador desabilita todas as outras interrupções, limpando o bit I no SREG. Ao retornar da interrupção, ele configura novamente o bit I, permitindo que outras interrupções sejam atendidas.
É importante notar que quando uma interrupção é executada em assembly, o Registrador de Status (SREG) não é automaticamente preservado ou restaurado no final da execução.

## Interrupções Vetorizadas e Mascaráveis

As interrupções no Atmega328p são vetorizadas, o que significa que cada interrupção possui um endereço de serviço fixo na memória do programa.
Além disso, as interrupções são mascaráveis, o que significa que podem ser habilitadas ou desabilitadas agindo em bits específicos.
O AVR sempre executará uma instrução do programa principal antes de atender qualquer interrupção na fila.

## Interrupções Externas — INT0 e INT1

As interrupções externas INT0 e INT1 são controladas por bits no Registrador de Controle de Interrupção Externa A (EICRA).
Esses bits configuram as condições de gatilho para as interrupções externas.
Para habilitar as interrupções externas INT0 e INT1, os bits correspondentes no Registrador de Máscara de Interrupção Externa (EIMSK) devem ser definidos, juntamente com o bit I no Registrador de Status (SREG).

### EICRA: Registrador de Controle de Interrupção Externa A

O registrador EICRA contém bits de configuração para INT0 e INT1, especificando as condições de gatilho para cada interrupção. Aqui está a descrição:

| Bits  | Descrição                                  |
|-------|--------------------------------------------|
| ISC01, ISC00 | Controle de Sensibilidade de Interrupção para INT0 |
| ISC11, ISC10 | Controle de Sensibilidade de Interrupção para INT1 |

Os bits de sensibilidade de interrupção (ISC) controlam a condição de gatilho para as interrupções externas. Aqui estão as combinações possíveis:

| ISC01 | ISC00 | Tipo de Bordas | Descrição                |
|-------|-------|----------------|--------------------------|
|   0   |   0   |   Baixo nível  | Interrupção ocorre quando o pino está em nível baixo (0)      |
|   0   |   1   |   Qualquer borda | Interrupção ocorre quando ocorre qualquer mudança de nível no pino |
|   1   |   0   |   Borda de subida | Interrupção ocorre quando o pino muda de nível baixo (0) para alto (1)    |
|   1   |   1   |   Borda de descida | Interrupção ocorre quando o pino muda de nível alto (1) para baixo (0)    |

### EIMSK: Registrador de Máscara de Interrupção Externa

O registrador EIMSK habilita ou desabilita as interrupções externas INT0 e INT1. Aqui está o layout:

| Bits | Descrição                                  |
|------|--------------------------------------------|
| INT1 | Habilitar Solicitação de Interrupção Externa 1 |
| INT0 | Habilitar Solicitação de Interrupção Externa 0 |


### Exemplo de Código

Aqui está um exemplo de código em C para configurar, chamar e lidar com interrupções externas no Atmega328p:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

// Função de tratamento da interrupção externa 0 (INT0)
ISR(INT0_vect) {
    // Seu código de tratamento de interrupção aqui
}

int main(void) {
    // Configura o pino de interrupção externa INT0 (PD2) como entrada
    DDRD &= ~(1 << PD2);

    // Habilita a interrupção externa INT0 e o bit I de todas as interrupções
    EIMSK |= (1 << INT0);
    sei(); // Habilita interrupções globais

    while (1) {
        // Seu código principal aqui
    }

    return 0;
}
```