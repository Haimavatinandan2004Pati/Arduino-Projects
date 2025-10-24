int Wait = 2;
int Ready = 3;
int Detected = 4;
int Sensor_Pin = 5;
int Prev_Val = 0;
int motionDetected = 0;
int Sensor_Val;
void setup() {
  pinMode(Ready, OUTPUT);
  pinMode(Wait, OUTPUT);
  pinMode(Detected, OUTPUT);
  pinMode(Sensor_Pin, INPUT);
  digitalWrite(Ready, LOW);
	digitalWrite(Wait, HIGH);
	digitalWrite(Detected, LOW);
	delay(60000);
	digitalWrite(Ready, HIGH);
	digitalWrite(Wait, LOW);
  Serial.begin(9600);

}

void loop() {
Sensor_Val = digitalRead(Sensor_Pin);
	if (Sensor_Val == 1){
		digitalWrite(Detected, HIGH);
		digitalWrite(Ready, LOW);    
		motionDetected = 1;
		delay(3000);
	} else {
		digitalWrite(Detected, LOW);
	}
	// Add delay after triggering to reset sensor
	if (motionDetected == 1) {
		// After trigger wait 6 seconds to re-arm
		digitalWrite(Detected, LOW);
		digitalWrite(Ready, LOW);
		digitalWrite(Wait, HIGH);
		delay(6000);
		digitalWrite(Ready, HIGH);
		digitalWrite(Wait, LOW);
		motionDetected = 0;
	}
  
 }

