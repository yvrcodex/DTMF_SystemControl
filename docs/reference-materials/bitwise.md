<h3 align="center">REGISTRADORES: BITWISE E BITMASK </h3>

---
#### OPERAÇÃO PARA BIT = 1

Para configurar um pino específico, como o PB5 (correspondente ao pin 13 no Arduino Uno), como saída utilizando operações bitwise em registradores AVR.

```c
DDRB |= (1 << PB5); // Configura PB5 (pin13) como saída (bit = 1)
```

- A expressão `(1 << PB5)` desloca 1 para a esquerda em PB5 posições, resultando em `00100000` (ou seja, 0b00100000 em binário).
- Em seguida, o operador `|=` é usado para realizar uma operação OR bit a bit entre o valor atual de DDRB e o valor calculado acima.
- Supondo que DDRB inicialmente seja `10001001`, após a operação, DDRB se torna `10101001`, indicando que PB5 agora é uma saída **sem alterar o estado inicial dos outros bits do DDRB**

Tabela passo a passo:

| DDRB   | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |
|--------|---|---|---|---|---|---|---|---|
| 1<<PB5 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
| Resultado | 1 | 0 | 1 | 0 | 1 | 0 | 0 | 1 |


O bit PB5 (pino 13) foi configurado como saída (1), mantendo os outros bits de DDRB intactos.
___
#### OPERAÇÃO PARA BIT = 0

Para configurar um pino específico, como o PB5 (correspondente ao pin 13 no Arduino Uno), como entrada utilizando operações bitwise em registradores AVR.

```c
DDRB &= ~(1 << PB5); // Configura PB5 (pino 13) como entrada (bit = 0)
```

- A expressão `(1 << PB5)` desloca 1 para a esquerda em PB5 posições, resultando em `00100000` (ou seja, 0b00100000 em binário).
- Em seguida, a operação `~` é usada para inverter todos os bits do valor calculado, resultando em `11011111`.
- O operador `&=` é usado para realizar uma operação AND bit a bit entre o valor atual de DDRB e o valor invertido calculado acima, fazendo com que o bit correspondente a PB5 seja 0 e **mantendo os outros bits de DDRB intactos.**

Tabela passo a passo:

| 1<<PB5 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |
|--------|---|---|---|---|---|---|---|---|
| ~1<<PB5 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 |
| **DDRB**  | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |
| Result | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 1 |

0 bit PB5 foi configurado como entrada (0), mantendo os outros bits de DDRB intactos.
