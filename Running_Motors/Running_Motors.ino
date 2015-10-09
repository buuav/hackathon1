// This script is sample code that initializes your motors and runs them. 
// Much of this code takes more steps than necessary in order to outline what is happening,
// as you become more familiar coding Arduino scripts, your code will be a lot more 
// concise.

// create the variables that defines which pins the motors are connected to
const int leftMotorPins = {4, 5, 6};    
const int rightMotorPins = {7, 8, 9}; 

//----------//
// This is the set-up for all of the pins you are using on the Arduino
// This section only runs once each time you begin the script
void setup() {
  
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
//This is the main section of your code, it repeatedly loops through.
void loop() {

  // this tells the motors to run (default value is 100), change this and see what happens.
  analogWrite(leftMotorPins[2], 100); 
  analogWrite(rightMotorPins[2], 100); 
  delay(20) // this delay is necessary to give it a little more time to move and process.
}
