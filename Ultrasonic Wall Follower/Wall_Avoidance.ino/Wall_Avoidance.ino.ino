// NEW PING LIBRARY SYNTAX
//NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]) - Initialize an ultrasonic device, trigger pin, echo pin, and optional maximum distance you wish to sensor to measure (default = 500cm).
//sonar.ping() - Send a ping and get the echo time (in microseconds) as a result.
//sonar.ping_in() - Send a ping and get the distance in whole inches.
//sonar.ping_cm() - Send a ping and get the distance in whole centimeters.
//sonar.ping_median(iterations) - Do multiple pings (default=5), discard out of range pings and return median in microseconds.
//sonar.convert_in(echoTime) - Convert echoTime from microseconds to inches.
//sonar.convert_cm(echoTime) - Convert echoTime from microseconds to centimeters.
//sonar.ping_timer(function) - Send a ping and call function to test if ping is complete.
//sonar.check_timer() - Check if ping has returned within the set distance limit.
//NewPing::timer_us(frequency, function) - Call function every frequency microseconds.
//NewPing::timer_ms(frequency, function) - Call function every frequency milliseconds.
//NewPing::timer_stop() - Stop the timer.


#include <NewPing.h>

const int motorPins[2][3] = {{4, 5, 6}, {7, 8, 9}};
NewPing left_sonar(10, 11, 200);
NewPing right_sonar(12, 13, 200);
int distance_left;
int distance_right;
int current_sensor = 0; //0 is the left sensor, 1 is the right sensor

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++)
      pinMode(motorPins[i][j], OUTPUT);
  for (int i = 0; i < 2; i++) {
    digitalWrite(motorPins[i][0], HIGH);
    digitalWrite(motorPins[i][1], LOW);
  }
}
void loop() {
  // Get distances from both sensors
  distance_left = left_sonar.ping_cm();
  distance_right = right_sonar.ping_cm();

  // Sensors return 0 if distance is greater than max distance set
  if (distance_left == 0) distance_left = 200; //return 200 if distance greater than 200
  if (distance_right == 0) distance_right = 200; //return 200 if distance greater than 200

  // Print Distances
  Serial.print("L: ");
  Serial.print(distance_left);
  Serial.print(", R: ");
  Serial.println(distance_right);

  // Logic to select which sensor the vehicle is prioritizing and the direction it needs to go
  if ((distance_left < 15) && (distance_left < distance_right)) {
    current_sensor = 0; // turn right
  }
  else if ((distance_right < 15) && (distance_left > distance_right)) {
    current_sensor = 1; // turn left
  }
  else if ((distance_left > 20) && (distance_left < distance_right)) {
    current_sensor = 1; // turn left
  }
  else if ((distance_right > 20) && (distance_left > distance_right)) {
    current_sensor = 0; // turn right
  }
  else {
    current_sensor = 2;
  }
 
 Serial.println(current_sensor);
 
  // control the vehicle base on the prioritized sensor and its reading
  switch (current_sensor) {
    case 0: // turn right
      analogWrite(motorPins[1][2], 120);
      analogWrite(motorPins[0][2], 90);
      break;
    case 1: // turn left
      analogWrite(motorPins[0][2], 120);
      analogWrite(motorPins[1][2], 90);
      break;
    case 2: // go straight
      analogWrite(motorPins[0][2], 90);
      analogWrite(motorPins[1][2], 90);
  }

  delay(100);
}
