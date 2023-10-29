#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#define MOTOR_A_DIRECAO_POS_PIN 8
#define MOTOR_A_DIRECAO_NEG_PIN 9
#define MOTOR_A_ENABLE_PIN 10

#define MOTOR_B_DIRECAO_POS_PIN 6
#define MOTOR_B_DIRECAO_NEG_PIN 7
#define MOTOR_B_ENABLE_PIN 5

void setup(){
  Dabble.begin("GELEIA");//Nome bluetooth para aparecer

  //Motor A
  pinMode(MOTOR_A_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_A_DIRECAO_POS_PIN, OUTPUT);
  pinMode(MOTOR_A_DIRECAO_NEG_PIN, OUTPUT);
  //Motor B
  pinMode(MOTOR_B_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_B_DIRECAO_POS_PIN, OUTPUT);
  pinMode(MOTOR_B_DIRECAO_NEG_PIN, OUTPUT);
}

void send_command_to_motor(int vel, int pos_dir_pin, int neg_dir_pin, int enable_pin){
  digitalWrite(pos_dir_pin, (vel > 0 ? HIGH : LOW));
  digitalWrite(neg_dir_pin, (vel < 0 ? HIGH : LOW));
  analogWrite(enable_pin, (vel < 0 ? -vel : vel));
}
void loop(){
  Dabble.processInput();

  float comandoMotorA = GamePad.getYaxisData() + GamePad.getXaxisData();
  float comandoMotorB = GamePad.getYaxisData() - GamePad.getXaxisData();
  int velMotorA = map(comandoMotorA, -10.00, 10.00, -255, 255);
  int velMotorB = map(comandoMotorB, -10.00, 10.00, -255, 255);
  //Motor A
  send_command_to_motor(velMotorA,
  			MOTOR_A_DIRECAO_POS_PIN, MOTOR_A_DIRECAO_NEG_PIN, MOTOR_A_ENABLE_PIN);
  //Motor B
  send_command_to_motor(velMotorB,
  			MOTOR_B_DIRECAO_POS_PIN, MOTOR_B_DIRECAO_NEG_PIN, MOTOR_B_ENABLE_PIN);
}
