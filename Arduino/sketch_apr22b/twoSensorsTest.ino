// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int trigPIN2 = 6;
const int echoPIN2 = 5;
// defines variables
long duration;
long duration2;
long durSens2Pt2;
long durationSensor2;

int distance;
int distance2;
int distSens2Pt2;
int distSensor2;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(trigPIN2, OUTPUT);
pinMode(echoPIN2, INPUT);
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

//clears trig pin #2
digitalWrite(trigPIN2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPIN2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPIN2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

durationSensor2 = pulseIn(echoPIN2, HIGH);

// Calculating the distance
distance = duration*0.034/2;

//calculating the dist of sensor #2
distSensor2 = durationSensor2*0.034/2;

delay(1000);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

digitalWrite(trigPIN2, LOW);
delayMicroseconds(2);
digitalWrite(trigPIN2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPIN2, LOW);

duration2 = pulseIn(echoPin, HIGH);
distance2 = duration2*0.034/2;
Serial.print("Distance: ");
 Serial.println(distance);
 Serial.print("Distance2: ");
  Serial.println(distance2);

//sensor #2 distances
durSens2Pt2 = pulseIn(echoPIN2, HIGH);
distSens2Pt2 = durSens2Pt2*0.034/2;
Serial.print("Distance Sensor 2: ");
 Serial.println(distSensor2);
 Serial.print("Distance2 Sensor 2: ");
  Serial.println(distSens2Pt2);
  
if(distance2 <= 60 && abs(distance2 - distance) > 10){
  Serial.print("HIT \n");
  //Serial.println(distance);
}

// Prints the distance on the Serial Monitor

}
