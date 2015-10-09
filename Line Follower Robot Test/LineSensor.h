#ifndef LineSensor_h
#define LineSensor_h

#include <Arduino.h>

class LineSensor {
  private:
    uint8_t inPin[3];
    unsigned int offsetVal[3];

  public:
    LineSensor(int pin0, int pin1, int pin2);
    int getLinePosition();
    void calibrate(void);
};

#endif
