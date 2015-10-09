#include <Arduino.h>
#include <PID_v1.h>

#ifndef motor_pid_h
#define motor_pid_h

#define PID_P 1
#define PID_I 15
#define PID_D 0.05

class MotorPID{
  private: 
    int _pwmPin;
    int _encoderPin;
    double _speed;
    double _setSpeed;
    double _motorPWM;
    uint32_t _encoderTimestamp;
    volatile long _encoderPulseCount;

    PID _pwmPID = PID(&_speed, &_motorPWM, &_setSpeed, PID_P, PID_I, PID_D, DIRECT);

  public:
    MotorPID(int pwmPin, int encoderPin, void(*interruptDispatch)());
    ~MotorPID(void);
    void setSpeed(uint16_t);
    uint16_t getSpeed(void);
    void update(void);
    void encoderISR(void);
};

#endif
