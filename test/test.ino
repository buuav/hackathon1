#include <PID_v1.h>
#include "motor_pid.h"
#include "LineSensor.h"

#define PID_P 2
#define PID_I 0
#define PID_D 0


void leftMotorISRDispatch(), rightMotorISRDispatch();
MotorPID leftMotor(5, 2, &rightMotorISRDispatch);
MotorPID rightMotor(6, 3, &leftMotorISRDispatch);
LineSensor lineSensor(A0, A1, A2);

uint16_t baseSpeed = 50;
double differentialSpeed = 0;
double linePosition = 0;
double setLinePosition = 0;
PID motorDifferentialPid(&linePosition, &differentialSpeed, &setLinePosition, PID_P, PID_I, PID_D, DIRECT);

void leftMotorISRDispatch() {
  leftMotor.encoderISR();
}

void rightMotorISRDispatch() {
  rightMotor.encoderISR();
}

void setup() {
  Serial.begin(9600);
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  motorDifferentialPid.SetOutputLimits(-40, 40);
  lineSensor.calibrate();
}

void loop() {
  if (lineSensor.isLineVisible()) {
    motorDifferentialPid.SetMode(AUTOMATIC);
    linePosition = lineSensor.getLinePosition();
    motorDifferentialPid.Compute();
    leftMotor.setSpeed((uint16_t)(baseSpeed + differentialSpeed));
    rightMotor.setSpeed((uint16_t)(baseSpeed - differentialSpeed));
    leftMotor.update();
    rightMotor.update();
    Serial.print(round(linePosition));
    Serial.print('\t');
    Serial.println(differentialSpeed);
  } else {
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
    motorDifferentialPid.SetMode(MANUAL);
    differentialSpeed = 0;
    Serial.println("Stopped");
  }
  delay(200);
}
