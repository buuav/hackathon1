// This script sets up your line sensor and lets you see the outputs from it. 

#include "LineSensor.h" // this includes the library we made for the line sensor

// These are the pins that the line sensor uses, follow the instructions in the line-sensor 
// set up to make sure they are connected properly.
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
// now move your connected line sensor over a dark line and read the 
// serial output (Click the magnifying glass looking button in the top
// right corner of this box).

