#include "LineSensor.h"

LineSensor::LineSensor(int pin0, int pin1, int pin2) {
  inPin[0] = pin0;
  inPin[1] = pin1;
  inPin[2] = pin2;

  for (int i = 0; i < 3; i++)
    pinMode(inPin[i], INPUT);
}

bool LineSensor::isLineVisible() {
  int currentVals[3];
  int minVal = 1023;
  for (int i = 0; i < 3; i++) {
    currentVals[i] = analogRead(inPin[i]) - offsetVal[i];
    if (currentVals[i] < minVal) minVal = currentVals[i];
  }
  int maxVal = 0;
  for (int i = 0; i < 3; i++) {
    currentVals[i] -= minVal;
    if (currentVals[i] > maxVal) maxVal = currentVals[i];
  }

  if (maxVal > 10)  return true;
  else      return false;
}

void LineSensor::calibrate(void) {
  for (int i = 0; i < 3; i++)
    offsetVal[i] = analogRead(inPin[i]);
}

double LineSensor::getLinePosition() {
  int currentVals[3];
  int minVal = 1023;
  for (int i = 0; i < 3; i++) {
    currentVals[i] = analogRead(inPin[i]) - offsetVal[i];
    if (currentVals[i] < minVal) minVal = currentVals[i];
  }
//  for (int i = 0; i < 3; i++)
//    currentVals[i] -= minVal;

  //  Serial.println(String(String(analogRead(inPin[0])) + '\t' + String(analogRead(inPin[1])) + '\t' + String(analogRead(inPin[2]))));
//  Serial.println(String("(" + String(analogRead(inPin[0])) + "," + String(currentVals[0]) + ")\t(" + String(analogRead(inPin[1])) + "," + String(currentVals[1]) + ")\t(" + String(analogRead(inPin[2])) + "," + String(currentVals[2]) + ")"));

  return 100 * (-currentVals[0] + currentVals[2]) / (currentVals[0] + currentVals[1] + currentVals[2]);
}
