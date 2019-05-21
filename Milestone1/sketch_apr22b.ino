// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
long duration2;
int distance;
int distance2;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration*0.034/2;
delay(1000);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration2 = pulseIn(echoPin, HIGH);
distance2 = duration2*0.034/2;
Serial.print("Distance: ");
 Serial.println(distance);
 Serial.print("Distance2: ");
  Serial.println(distance2);
if(distance2 <= 60 && abs(distance2 - distance) > 10){
  Serial.print("HIT \n");
  //Serial.println(distance);
}

// Prints the distance on the Serial Monitor

}
