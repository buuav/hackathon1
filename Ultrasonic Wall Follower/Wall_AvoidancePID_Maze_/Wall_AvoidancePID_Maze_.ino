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
#include <PID_v1.h>

const int motorPins[2][3] = {{4, 5, 6}, {7, 8, 9}};
const int maxSensingDist = 25;
NewPing left_sonar(10, 11, maxSensingDist);
NewPing right_sonar(12, 13, maxSensingDist);
int distance_left;
int distance_right;
int current_sensor = 0; //0 is the left sensor, 1 is the right sensor

// define variables we will be connecting
double Setpoint0, Input0, Output0, Setpoint1, Input1, Output1;
int Kp = 3.0; // 3.0
int Ki = 0.05; // 0.05
int Kd = 0.85; // 0.85

//Specify links and initial tuning parameters of PID
PID myPID0(&Input0, &Output0, &Setpoint0, Kp, Ki, Kd, DIRECT);
PID myPID1(&Input1, &Output1, &Setpoint1, Kp, Ki, Kd, DIRECT);

void setup() {
  //start serial to enable error checking
  Serial.begin(9600);

  //initialize linked variables
  Input0 = left_sonar.ping_cm();
  Input1 = right_sonar.ping_cm();
  Setpoint0 = 10; //15
  Setpoint1 = 10; //15

  //set output limits
  myPID0.SetOutputLimits(-40, 80);
  myPID1.SetOutputLimits(-40, 80);

  //turn on the PID loops
  myPID0.SetMode(AUTOMATIC);
  myPID1.SetMode(AUTOMATIC);

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
  Input0 = left_sonar.ping_cm();
  Input1 = right_sonar.ping_cm();

  // Sensors return 0 if distance is greater than max distance set
  if (Input0 == 0) Input0 = maxSensingDist; //return 200 if distance greater than maxSensingDist
  if (Input1 == 0) Input1 = maxSensingDist; //return 200 if distance greater than maxSensingDist

  myPID0.Compute();
  delay(10);
  myPID1.Compute();
  delay(10);

  if (Input0 != maxSensingDist && Input1 != maxSensingDist) {
    if (Input0 < Input1) {
      current_sensor = 0;
    } else if (Input0 > Input1) {
      current_sensor = 1;
    } else {
      current_sensor = 2;
    }
//  } else if (Input0 == maxSensingDist && Input1 == maxSensingDist) {
//    current_sensor = 3;
  } else if (Input0 == maxSensingDist) {
    current_sensor = 0;
  } else if (Input1 == maxSensingDist) {
    current_sensor = 1;
  }


  // Print Distances
  Serial.print("L: ");
  Serial.print(Input0);
  Serial.print(":");
  Serial.print(Output0);
  Serial.print(", R: ");
  Serial.print(Input1);
  Serial.print(":");
  Serial.println(Output1);
  Serial.println(current_sensor);

  // control the vehicle base on the prioritized sensor and its reading
  switch (current_sensor) {
    case 0: // control obstacle on left
      analogWrite(motorPins[1][2], 90 + Output0); // left motor
      analogWrite(motorPins[0][2], 90 - Output0); // right motor
      break;
    case 1: // control obstacle on right
      analogWrite(motorPins[0][2], 90 + Output1); // right motor
      analogWrite(motorPins[1][2], 90 - Output1); // left motor
      break;
    case 2: // go straight
      analogWrite(motorPins[0][2], 90); // right motor
      analogWrite(motorPins[1][2], 90); // left motor
//    case 3: // bot is in an opening, turn right!
//      analogWrite(motorPins[1][2], 90 + 30); // left motor
//      analogWrite(motorPins[0][2], 90 - 30); // right motor
//      delay(100);
  }

  delay(20);
}
