const int motorPins[3] = {4, 5, 6};

void setup(){
	for(int i=0; i<3; i++)
		pinMode(motorPins[i], OUTPUT);
	digitalWrite(motorPin[0], HIGH);
	digitalWrite(motorPin[1], LOW);
}

void loop(){
	for(int i=0; i<255; i++){
		analogWrite(motorPin[2], i);
		delay(10);
	}	
	for(int i=255; i>0; i--){
		analogWrite(motorPin[2], i);
		delay(10);
	}	
}