#include "LineSensor.h"
LineSensor sense(A0, A1, A2);   // Create a new sensor object and give it the three input analog pins in the order (LEFT, CENTER, RIGHT)

void setup() {
  Serial.begin(9600);
  sense.calibrate();	// Calibrate sensor on current surface to set offset value to remove from every reading after this.
}


void loop() {
  Serial.println(sense.getLinePosition());	// getLinePosition() gives the line position either as (0, 1, 2) if you have binning enabled or as a linear value between -100 to +100 if you have linear output enabled.
  delay(20);
}
