<h1 align="center">DTMF SYSTEM CONTROL</h1>

---
<p align="center">
  <img src="https://img.shields.io/badge/Status-Concluido-4B0082?style=for-the-badge&logo=statuspage&logoColor=white" alt="Status Ativo">
  <img src="https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge&logo=mit&logoColor=white" alt="Licença MIT">
  <img src="https://img.shields.io/badge/University-PUC%20MINAS-00599C?style=for-the-badge" alt="Universidade PUC MINAS">
  <img src="https://img.shields.io/badge/Microcontroller-4B0082?style=for-the-badge&logo=microchip&logoColor=white" alt="Microcontroller">
  <img src="https://img.shields.io/badge/Embedded%20System-4B0082?style=for-the-badge&logo=microchip&logoColor=white" alt="Embedded System">
</p>

# Índice

1. [Introdução](#introdução)
2. [Fluxo de Trabalho](#fluxo-de-trabalho)
3. [Características](#características)
4. [Requisitos](#requisitos)
5. [Datasheets](docs/datasheets/)
6. [Materiais de Referência](docs/reference-materials/)

## Introdução

O projeto Controle de Sistemas via DTMF foca na utilização de módulos DTMF (Dual-Tone Multi-Frequency) para o controle remoto de sistemas via áudio. O objetivo do projeto é permitir que os usuários controlem remotamente dispositivos, como relés, utilizando tons DTMF gerados através de entrada de áudio.

## Fluxo de Trabalho

Neste projeto, o microcontrolador ATmega328P embarcado em uma placa Arduino é integrado com o módulo DTMF MT8870. Esta combinação recebe e decodifica sinais DTMF provenientes de uma entrada P2 no módulo. O sistema é capaz de acionar relés com base nos códigos DTMF recebidos, executando tarefas conforme os comandos enviados. O projeto também possui um protótipo que utiliza o display ST7789 para simular uma ativação por senha, onde o sinal DTMF recebido é exibido no display e comparado com uma senha registrada no firmware.

## Características

- **Controle Remoto:** Permite o controle remoto de dispositivos via tons DTMF.
- **Integração com Arduino:** Utiliza microcontrolador Arduino para processar sinais DTMF.
- **Personalizável:** Facilmente adaptável para controlar diversos dispositivos e aplicações.
- **Interface Amigável:** Interface simples para entrada de comandos DTMF via áudio.

## Requisitos

- **Hardware:** Módulo DTMF, Arduino (e.g., ATmega328P), dispositivo de entrada/saída de áudio.
- **Software:** Arduino IDE, VSCode (PlatformIO), bibliotecas para decodificação DTMF.

## Instalação

1. Clone o repositório:

   ```bash
   git clone https://github.com/yvrcodex/DTMF_SystemControl

2. Abra o projeto no Arduino IDE ou VSCode (PlatformIO).

3. Conecte o hardware conforme especificado na documentação.

4. Compile e carregue o código no Arduino.

5. Teste o sistema enviando tons DTMF através do dispositivo de entrada de áudio.

## Datasheets

- [Datasheet ATmega328P](docs/datasheets/ATmega328P.pdf)
- [Datasheet MT8870](docs/datasheets/MT8870.pdf)

## Materiais de Referência

- [Documentação do Arduino Uno](https://www.arduino.cc/en/Main/ArduinoBoardUno)
- [Aplicações e Exemplos Práticos](docs/reference-materials/Aplicacoes_e_Exemplos.pdf)

## Displays e Expansão Futura

[#displays-e-expansão-futura](#displays-e-expansão-futura)

O protótipo atual usa um display **ST7789** (SPI, 240x240) para simular a ativação por senha: o tom DTMF recebido é decodificado, mostrado na tela e comparado com a senha registrada no firmware. Nessa versão com ATmega328P, o display roda via `Adafruit_ST7789`, já que a memória e o clock do microcontrolador limitam o uso de bibliotecas mais pesadas.

### Limitações atuais

- Pouca RAM disponível no ATmega328P para buffer de tela, o que restringe animações e atualizações parciais.
- Sem conectividade — todo o controle depende exclusivamente do áudio DTMF de entrada.
- Refresh da tela relativamente lento em operações que exigem redesenho completo.

### Planos com ESP32

A ideia é portar o núcleo de decodificação DTMF para um **ESP32**, mantendo o módulo MT8870 como front-end de entrada, e ganhar com isso:

- **LovyanGFX** no lugar da Adafruit_ST7789 — mais rápido no mesmo painel ST7789, com suporte a DMA e double buffering.
- **Wi-Fi/BLE** para status remoto do sistema (ex: histórico de comandos recebidos, estado dos relés) sem depender só do display local.
- Mais GPIO disponível para escalar o número de relés controlados.
- Possibilidade de um painel maior (ex: 320x240 ou touch) já que o ESP32 aguenta o processamento sem gargalar.


## Licença

Este projeto é licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.
Se você tiver alguma dúvida ou encontrar algum problema, por favor, abra uma issue no repositório ou entre em contato através do email fornecido na nossa página de perfil do GitHub.

---
