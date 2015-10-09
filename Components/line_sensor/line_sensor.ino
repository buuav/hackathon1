#include "LineSensor.h"
LineSensor sense(A0, A1, A2);

void setup() {
  Serial.begin(9600);
  sense.calibrate();
}


void loop() {
//  sense.getLinePosition();
  if(sense.isLineVisible()) Serial.println(sense.getLinePosition());
  delay(20);
}
