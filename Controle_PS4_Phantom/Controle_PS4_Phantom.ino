#include <PS4Controller.h>
#include <ps4.h>
#include <ps4_int.h>

#include <ESP32Servo.h>
#include <analogWrite.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>

#include <math.h>

#define leftMotorPin 25 
#define rightMotorPin 26 

Servo MotorEsquerdo;
Servo MotorDireito;

//fc:b3:bc:76:e9:03
void setup() {
  PS4.begin("fc:b3:bc:76:e9:03");
  Serial.begin(9600);

  while(!PS4.isConnected()){
    Serial.println("Esperando Conexao");
    delay(250);
  }


  PS4.setLed(0,100,0);
  PS4.sendToController();

  MotorEsquerdo.attach(leftMotorPin);
  MotorDireito.attach(rightMotorPin);
  MotorEsquerdo.write(90);
  MotorDireito.write(90);

  Serial.println("Conexao Estabelecida");
}

void loop() {
  if(PS4.isConnected()){
    int LStickX = PS4.LStickX();
    int LStickY = PS4.LStickY();

    float inputX =   LStickX / 256.f ; 
    float inputY =   LStickY / 256.f ;
    float moduloInput =  sqrt(inputX*inputX + inputY*inputY);
    inputX = inputX / moduloInput;
    inputY = inputY / moduloInput;


    int leftMotorOutput = (inputX + inputY) * 90 + 90;
    int rightMotorOutput = (inputX - inputY) * 90 + 90;
    if(leftMotorOutput > 95 || leftMotorOutput < 85 ){
      MotorEsquerdo.write(leftMotorOutput);
    }
    else{
      MotorEsquerdo.write(116.64);
    }
  
    if(rightMotorOutput > 95 || rightMotorOutput < 85 ){
      MotorDireito.write(rightMotorOutput);
    }
    else{
      MotorDireito.write(116.64);
    }
  }
  else{
      MotorEsquerdo.write(116.64);
      MotorDireito.write(116.64);
  }
}
