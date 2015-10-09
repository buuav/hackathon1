#include "motor_pid.h"

MotorPID::MotorPID(int pwmPin, int encoderPin, void(*interruptDispatch)()){
  _pwmPin = pwmPin;
  _encoderPin = encoderPin;
  _encoderPulseCount = 0;
  _setSpeed = 0;
  _speed = 0;
  _motorPWM = 0;
  _encoderTimestamp = millis();

  pinMode(_pwmPin, OUTPUT);
  pinMode(_encoderPin, INPUT);
  digitalWrite(_encoderPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(_encoderPin), interruptDispatch, CHANGE);
//  _pwmPID.SetSampleTime(20);
  _pwmPID.SetMode(AUTOMATIC);
}

MotorPID::~MotorPID(void){
  detachInterrupt(digitalPinToInterrupt(_encoderPin));  
}

void MotorPID::setSpeed(uint16_t setSpeed){
  _setSpeed = (double) setSpeed;
  setSpeed = max(setSpeed, 0);
  if(setSpeed == 0){
    _pwmPID.SetMode(MANUAL);
    analogWrite(_pwmPin, 0);
  }
  else _pwmPID.SetMode(AUTOMATIC);
}

uint16_t MotorPID::getSpeed(void){
  return (uint16_t) _speed;
}

void MotorPID::encoderISR(void){
  _encoderPulseCount++;
}

void MotorPID::update(void){
  _speed = (60000 / 384) * _encoderPulseCount / (millis() - _encoderTimestamp);
  _encoderTimestamp = millis();
  _encoderPulseCount = 0;
  _pwmPID.Compute();
  analogWrite(_pwmPin, (uint8_t) _motorPWM);
}
