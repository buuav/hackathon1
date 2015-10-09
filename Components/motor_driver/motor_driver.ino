#include "motor_pid.h"
#include <PID_v1.h>

void leftMotorISRDispatch(), rightMotorISRDispatch();
MotorPID leftMotor(5, 2, &rightMotorISRDispatch);
MotorPID rightMotor(6, 3, &leftMotorISRDispatch);

void leftMotorISRDispatch() {
  leftMotor.encoderISR();
}

void rightMotorISRDispatch() {
  rightMotor.encoderISR();
}

void setup() {
  Serial.begin(9600);
  leftMotor.setSpeed(100);
  rightMotor.setSpeed(200);
}

void loop() {
  leftMotor.update();
  rightMotor.update();
  Serial.print(leftMotor.getSpeed());
  Serial.print("\t");
  Serial.println(rightMotor.getSpeed());
  delay(200);
}

