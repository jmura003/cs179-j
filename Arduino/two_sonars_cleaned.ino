// defines pins numbers
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 6;
const int echoPin2 = 5;

// defines variables
long s1_duration1;
long s1_duration2;
long s2_duration1;
long s2_duration2;

int s1_distance1;
int s1_distance2;
int s2_distance1;
int s2_distance2;

void sensor1() {
   // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  s1_duration1 = pulseIn(echoPin1, HIGH);

  // Calculating the first distance of S1 and S2
  s1_distance1 = s1_duration1*0.034/2;

  delay(1000);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  //Calculating the second distance of S1
  s1_duration2 = pulseIn(echoPin1, HIGH);
  s1_distance2 = s1_duration2*0.034/2;
  Serial.print("s1_distance1: ");
  Serial.println(s1_distance1);
  Serial.print("s1_distance2: ");
  Serial.println(s1_distance2);

  if(s1_distance2 <= 60 && abs(s1_distance2 - s1_distance1) > 10){
    Serial.print("S1 HIT \n");
    //Serial.println(distance);
  }
}
void sensor2(){
  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  s2_duration1 = pulseIn(echoPin2, HIGH);

  // Calculating the first distance of S1 and S2
  s2_distance1 = s2_duration1*0.034/2;

  delay(1000);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  //Calculating the second distance of S1
  s2_duration2 = pulseIn(echoPin2, HIGH);
  s2_distance2 = s2_duration2*0.034/2;
  Serial.print("s2_distance1: ");
  Serial.println(s2_distance1);
  Serial.print("s2_distance2: ");
  Serial.println(s2_distance2);

  if(s2_distance2 <= 60 && abs(s2_distance2 - s2_distance1) > 10){
    Serial.print("S2 HIT \n");
    //Serial.println(distance);
  }

}
void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {

 sensor1();
 delay(100);
 sensor2();

}
