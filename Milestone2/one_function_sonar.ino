//trigger pin does not need pwm
//echo pin needs pwm

const int trigPin1 = 12;
const int echoPin1 = 10;
const int trigPin2 = 7;
const int echoPin2 = 6;
const int trigPin3 = 2;
const int echoPin3 = 3;
const int trigPin4 = 4;
const int echoPin4 = 5;
const int buzzer = 11;

// defines variables
//long s1_duration1;
//long s1_duration2;
//long s2_duration1;
//long s2_duration2;
//
//int s1_distance1;
//int s1_distance2;
//int s2_distance1;
//int s2_distance2;

void sensors(const int, const int, const int);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // Starts the serial communication

}

void loop() {
  
  int sonar_no = 1;
  sensors(trigPin1, echoPin1, sonar_no);
  
  sonar_no++;
  sensors(trigPin2, echoPin2, sonar_no);
  
//  sonar_no++;
//  sensors(trigPin3, echoPin3, sonar_no);
//  
//  sonar_no++;
//  sensors(trigPin4, echoPin4, sonar_no);

}

//function with paramters trigPin, echoPin, sonar_no
//function activates sensors based on which which pins
//are passed in to the function
void sensors(const int trigPin, const int echoPin, const int sonar_no) {
  // Clears the trigPin
  Serial.println("--------------------");
  Serial.print("sonar number: ");
  Serial.println(sonar_no);

  long s_duration1 = 0;
  long s_duration2 = 0;

  int s_distance1 = 0;
  int s_distance2 = 0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  s_duration1 = pulseIn(echoPin, HIGH);

  // Calculating the first distance of S1 and S2
  s_distance1 = s_duration1 * 0.034 / 2;

  delay(1000);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Calculating the second distance of S1
  s_duration2 = pulseIn(echoPin, HIGH);
  s_distance2 = s_duration2 * 0.034 / 2;
  Serial.print("s_distance1: ");
  Serial.println(s_distance1);
  Serial.print("s_distance2: ");
  Serial.println(s_distance2);

  if (s_distance2 <= 60 && abs(s_distance2 - s_distance1) > 10) {
    Serial.print("S1 HIT \n");
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(500);
    //Serial.println(distance);
  }

}
