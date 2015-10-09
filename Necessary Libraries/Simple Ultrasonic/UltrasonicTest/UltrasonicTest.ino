// This script is a sample to show how to use the HC-SR04 ultrasonic sensor 

#include <NewPing.h>

#define TRIGGER_PIN 12   //Trigger pin (sends out the ultrasonic pulse)
#define ECHO_PIN    11   //Echo pin (recieves the ultrasonic pulse).
#define MAX_DIST    100  //Max distance the ultrasonic will sense. (Effective range is <3m)

//set up the sonar, connect the arduino to the corresponding pins on the ultrasonic.
//connect the 5V pin on the Arduino to VCC on the ultrasonic, and ground to ground.
NewPing sonar_1(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

void setup() {
  Serial.begin(9600); //sets up a serial connection so you can see the sonar readings.
}

void loop() {
  unsigned int Ping_1 = sonar_1.ping_cm(); // sets up the variable to get sonar pings and convert dist to cm.
  if (Ping_1 == 0) {
    Ping_1 = 100; // when the sensor is trying to get a range beyond its max distnace it will return 0, to 
  }               // correct for this we will set it to 100 if it is 0. This is a hack so be careful using it.
  
  Serial.print("Sonar_1: "); 
  Serial.print(Ping_1);
  Serial.println("cm"); //these print statements show you a nice centimeter distance over serial.
  delay(50); //required delay so that the sensors have time to get a response.
}

// Now press the button that looks like a magnifying glass in the top right corner to see the serial monitor.
