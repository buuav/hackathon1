#include "LineSensor.h"

LineSensor::LineSensor(int pin0, int pin1, int pin2) {
  inPin[0] = pin0;
  inPin[1] = pin1;
  inPin[2] = pin2;

  for (int i = 0; i < 3; i++)
    pinMode(inPin[i], INPUT);
}

int LineSensor::getLinePosition() {
  int currentVals[3];
  int maxVal = 0;
  int binNumber = 0;
  for (int i = 0; i < 3; i++) {
    currentVals[i] = analogRead(inPin[i]) - offsetVal[i];
    //    Serial.print(currentVals[i]);
    //    Serial.print("\t");
    if (currentVals[i] > maxVal) {
      maxVal = currentVals[i];
      binNumber = i;
    }
  }
  //  Serial.println("");
  //  Serial.println(binNumber);

  return binNumber;
//  return 100 * (-currentVals[0] + currentVals[2]) / (currentVals[0] + currentVals[1] + currentVals[2]);
}

void LineSensor::calibrate(void) {
  for (int i = 0; i < 3; i++)
    offsetVal[i] = analogRead(inPin[i]);
}
