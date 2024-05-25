# Controle PS4

## Dependencias do código

As dependencias desse código estao explicitas no arquivo [sketch.yaml](https://github.com/Grupo-SEMEAR-USP/geleia-misc/blob/main/controle-esc/sketch.yaml) que segue nessa pasta, portanto se voce estiver usando [arduino-cli](https://arduino.github.io/arduino-cli/), só é necessário rodar o comando
```bash
arduino-cli compile
```
para compilar.

Caso esteja usando o arduino IDE, eis o que voce precisa ter instalado (e em **qual versao**) para compilar esse código:
- Boards:
    - Board [ESP32 Lolin C3 Mini (2.0.13)](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
- Bibliotecas:
    - [ESP32Servo (1.2.1)](https://www.arduino.cc/reference/en/libraries/esp32servo/)
    - [PS4COntroller (1.0.8)](https://github.com/pablomarquez76/PS4_Controller_Host)
