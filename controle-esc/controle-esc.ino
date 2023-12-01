#include <ESP32Servo.h>

Servo esc_sig;
#define ESC_SIG_PIN 9

#define JOYSTICK_VX_PIN 4
#define JOYSTICK_VX_PIN 3
#define JOYSTICK_BUTTON_PIN 2

//Funcao para converter e enviar o sinal de "potencia" de 0 - 1 para o angular do servo de 0 - 180
void send_signal_esc(float sig) {
  esc_sig.write((int)(sig * 180));
}

void start_esc() {
  // De https://electronics.stackexchange.com/questions/169285/initializing-the-esc-through-microcontroller
  // Envia o sinal equivalente ao maximo (180) um pulso de 2ms
  // Espera 2-3 segundos
  // Envia o sinal equivalente ao minimo (0) um pulso de 1 ms
  // Espera 2-3 segundos
  // GG!
  //Usando delay de 5s pois 2.5s foi muito pouco
  send_signal_esc(1.f);
  delay(5000); // delay de 5 s
  send_signal_esc(0.f);
  delay(5000); // delay de 5 s
}

void setup() {
  Serial.begin(9600);
  esc_sig.attach(ESC_SIG_PIN, 1000, 2000);
  //delay(5000); //Delay para inicio do attach
  start_esc();
}

void loop() {
  // put your main code here, to run repeatedly:
  float value = (float)analogRead(JOYSTICK_VX_PIN) / 4095;
  send_signal_esc(value);
  //Serial.println(value); //Serial para debug
  delay(50); //Delay para nao mudar a saida muito rapidamente
}

