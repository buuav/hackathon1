// Braking before you hit an object! Put the ultrasonic on the front of your vehicle.
// This is a sample script showing you how to combine driving your motors and using
// the HC-SR04 ultrasonic sensor. If you don't know how to use these things, go through
// both of the intro scripts for the individual parts first.

#include <NewPing.h>

// create the variables that defines which pins the motors are connected to
const int rightMotorPins[3] = {4, 5, 6};
const int leftMotorPins[3] = {7, 8, 9};

#define TRIGGER_PIN 12   //Trigger pin (sends out the ultrasonic pulse).
#define ECHO_PIN    13   //Echo pin (recieves the ultrasonic pulse).
#define MAX_DIST    100  //Max distance the ultrasonic will sense. (Effective range is <3m)

NewPing sonar_1(TRIGGER_PIN, ECHO_PIN, MAX_DIST); // create sonar

//----------//
// SETUP CODE, RUNS ONCE EACH TIME THE ARDUINO BOOTS
void setup() {
  Serial.begin(9600); //sets up a serial connection so you can see the sonar readings.

  // set all the motor pins as OUTPUT pins
  for (int i = 0; i < 3; i++) {
    pinMode(leftMotorPins[i], OUTPUT); // for loop goes through the index and sets as HIGH
    pinMode(rightMotorPins[i], OUTPUT); // for loop goes through the index and sets as HIGH
  }

  // this sets A0 and B0 to HIGH and A1 and B1 to LOW output on each motor
  // this will determine the direction that the motors turn
  // switch HIGH and LOW to go in the other direction
  digitalWrite(leftMotorPins[0], HIGH);
  digitalWrite(rightMotorPins[0], HIGH);
  digitalWrite(leftMotorPins[1], LOW);
  digitalWrite(rightMotorPins[1], LOW);


}

//----------//
//MAIN LOOP, KEEPS RUNNING THROUGH WHILE THE ARDUINO IS POWERED
void loop() {

  // get your ultrasonic reading
  unsigned int Ping_1 = sonar_1.ping_cm(); // sets up the variable to get sonar pings and convert dist to cm.
  if (Ping_1 == 0) {
    Ping_1 = 100; // when the sensor is trying to get a range beyond its max distnace it will return 0, this changes any 0 output and makes it 100.
  }
  // logic statements to make the arduino slow down and stop a set distance away from an object
  // think about how you can vary the motor inputs and add a little more logic to change this to avoid an object.

  if (Ping_1 < 10) {
    analogWrite(leftMotorPins[2], 0); // stop! we are too close to the object.
    analogWrite(rightMotorPins[2], 0);
  } else if (Ping_1 < 25) {
    analogWrite(leftMotorPins[2], 70); // slow down, we are getting close to the wall.
    analogWrite(rightMotorPins[2], 70);
  } else {
    analogWrite(leftMotorPins[2], 120); // go fast we are far from the object.
    analogWrite(rightMotorPins[2], 120);
  }
  delay(40); // necessary delay to allow the sensor to get the data.
}
