#include <PID_v1.h>
#include "motor_pid.h"
#include "LineSensor.h"

#define LEFT_MOTOR_PWM 6
#define AIN2 5
#define AIN1 4
#define BIN1 7
#define BIN2 8
#define RIGHT_MOTOR_PWM 9

#define BIN_LEFT 0
#define BIN_CENTER 1
#define BIN_RIGHT 2

LineSensor lineSensor(A0, A1, A2);

void setup() {
  Serial.begin(9600);
  lineSensor.calibrate();
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
//  analogWrite(LEFT_MOTOR_PWM, 128);
//  analogWrite(RIGHT_MOTOR_PWM, 128);
}

void loop() {
  Serial.println(lineSensor.getLinePosition());
  delay(20);
//  switch(lineSensor.getLinePosition()){
//    case BIN_LEFT:
//      analogWrite(LEFT_MOTOR_PWM, 0);
//      analogWrite(RIGHT_MOTOR_PWM, 128);
//      Serial.println("Left");
//      break;
//    case BIN_CENTER:
//      analogWrite(LEFT_MOTOR_PWM, 128);
//      analogWrite(RIGHT_MOTOR_PWM, 128);
//      Serial.println("Center");
//      break;
//    case BIN_RIGHT:
//      analogWrite(LEFT_MOTOR_PWM, 128);
//      analogWrite(RIGHT_MOTOR_PWM, 0);
//      Serial.println("Right");
//  }
//  delay(100);
}
