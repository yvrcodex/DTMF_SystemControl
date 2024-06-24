<h1 align="center">CONTROLE DE SISTEMAS VIA DTMF</h1>

---
<p align="center">
  <img src="https://img.shields.io/badge/Status-Ativo-4B0082?style=for-the-badge&logo=statuspage&logoColor=white" alt="Status Ativo">
  <img src="https://img.shields.io/badge/Licen%C3%A7a-MIT-blue.svg?style=for-the-badge&logo=mit&logoColor=white" alt="Licença MIT">
  <img src="https://img.shields.io/badge/Universidade-PUC%20MINAS-00599C?style=for-the-badge" alt="Universidade PUC MINAS">
  <img src="https://img.shields.io/badge/Microcontrolador-4B0082?style=for-the-badge&logo=microchip&logoColor=white" alt="Microcontrolador">
  <img src="https://img.shields.io/badge/Sistema%20Embutido-4B0082?style=for-the-badge&logo=microchip&logoColor=white" alt="Sistema Embutido">
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

## Licença

Este projeto é licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.
Se você tiver alguma dúvida ou encontrar algum problema, por favor, abra uma issue no repositório ou entre em contato através do email fornecido na nossa página de perfil do GitHub.

---
