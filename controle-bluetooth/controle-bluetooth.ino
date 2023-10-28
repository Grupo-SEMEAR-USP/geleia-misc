#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#define PONTE_H_MOTOR_A_DIRECAO_POS_PIN 8
#define PONTE_H_MOTOR_A_DIRECAO_NEG_PIN 9
#define PONTE_H_MOTOR_A_VELOCIDADE_PIN 10
#define LED_MOTOR_A_ID 0

#define PONTE_H_MOTOR_B_DIRECAO_POS_PIN 6
#define PONTE_H_MOTOR_B_DIRECAO_NEG_PIN 7
#define PONTE_H_MOTOR_B_VELOCIDADE_PIN 5
#define LED_MOTOR_B_ID 1

void setup() {
  Dabble.begin("GELEIA");//Nome bluetooth para aparecer
  ledcSetup(LED_MOTOR_A_ID, 500, 8);
  ledcSetup(LED_MOTOR_B_ID, 500, 8);

  //Motor A
  pinMode(PONTE_H_MOTOR_A_VELOCIDADE_PIN, OUTPUT);
  pinMode(PONTE_H_MOTOR_A_DIRECAO_POS_PIN, OUTPUT);
  pinMode(PONTE_H_MOTOR_A_DIRECAO_NEG_PIN, OUTPUT);
  ledcAttachPin(PONTE_H_MOTOR_A_VELOCIDADE_PIN, LED_MOTOR_A_ID);
  //Motor B
  pinMode(PONTE_H_MOTOR_B_VELOCIDADE_PIN, OUTPUT);
  pinMode(PONTE_H_MOTOR_B_DIRECAO_POS_PIN, OUTPUT);
  pinMode(PONTE_H_MOTOR_B_DIRECAO_NEG_PIN, OUTPUT);
  ledcAttachPin(PONTE_H_MOTOR_B_VELOCIDADE_PIN, LED_MOTOR_B_ID);
}

void loop() {
  Dabble.processInput();

  float comandoMotorA = GamePad.getYaxisData() + GamePad.getXaxisData();
  float comandoMotorB = GamePad.getYaxisData() - GamePad.getXaxisData();
  int velMotorA = map(comandoMotorA, -10.00, 10.00, -255, 255);
  int velMotorB = map(comandoMotorB, -10.00, 10.00, -255, 255);
  //Motor A
  digitalWrite(PONTE_H_MOTOR_A_DIRECAO_POS_PIN, (velMotorA > 0 ? HIGH : LOW));
  digitalWrite(PONTE_H_MOTOR_A_DIRECAO_NEG_PIN, (velMotorA < 0 ? HIGH : LOW));
  ledcWrite(LED_MOTOR_A_ID, (velMotorA < 0 ? -velMotorA : velMotorA));
  //Motor B
  digitalWrite(PONTE_H_MOTOR_B_DIRECAO_POS_PIN, (velMotorB > 0 ? HIGH : LOW));
  digitalWrite(PONTE_H_MOTOR_B_DIRECAO_NEG_PIN, (velMotorB < 0 ? HIGH : LOW));
  ledcWrite(LED_MOTOR_B_ID, (velMotorB < 0 ? -velMotorB : velMotorB));
}
