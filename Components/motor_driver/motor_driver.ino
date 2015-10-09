#include "motor_pid.h"
#include <PID_v1.h>

void leftMotorISRDispatch(), rightMotorISRDispatch();   // Declare the interrupt functions that will be called when the encoder pins change value.

// Define the motor objects for the left and right motors with (PWM pin, Encoder pin and interrupt function) as the parameters
MotorPID leftMotor(5, 2, &rightMotorISRDispatch); 
MotorPID rightMotor(6, 3, &leftMotorISRDispatch);

// Define the left and right motor encoder interrupt functions
void leftMotorISRDispatch() {
  leftMotor.encoderISR();
}

void rightMotorISRDispatch() {
  rightMotor.encoderISR();
}

// In setup, set speeds of the motors.
void setup() {
  Serial.begin(9600);
  leftMotor.setSpeed(100);
  rightMotor.setSpeed(200);
}

// The update function for the motor reads the velocity from the encoder and uses an internal PID controller to change the PWM input to the motor to maintain the motor speed at the set speed.
void loop() {
  leftMotor.update();
  rightMotor.update();
  Serial.print(leftMotor.getSpeed());
  Serial.print("\t");
  Serial.println(rightMotor.getSpeed());
  delay(200);
}

