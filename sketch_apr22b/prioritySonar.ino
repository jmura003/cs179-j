//trigger pin does not need pwm
//echo pin needs pwm

#define sonars 4 //number of sonars 

const int trigPin1 = 12;
const int echoPin1 = 10;
const int trigPin2 = 7;
const int echoPin2 = 6;
const int trigPin3 = 2;
const int echoPin3 = 3;
const int trigPin4 = 4;
const int echoPin4 = 5;
const int buzzer = 11;
/*haha*/ long boi[10];
int flag = 1;

bool done_init = false;

int buzzer_tones[] = {500, 1000, 1500, 2000}; // each element represents sonars #s 1-4

long init_dist[4];

int s_distance1 = 0;

int sonar_no = 0;


void sensors(const int, const int, const int);
void buzzer_logic(const int);
int PrioritySonar(const int,const int,const int,const int);


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
  done_init = false;

  //initialization to find the closest sonar
  sonar_no = 1;
  sensors(trigPin1, echoPin1, sonar_no);
  sonar_no++;
  sensors(trigPin2, echoPin2, sonar_no);
  sonar_no++;
  sensors(trigPin3, echoPin3, sonar_no);
  sonar_no++;
  sensors(trigPin4, echoPin4, sonar_no);
  sonar_no = 1;

  done_init = true; //after initializing, set to true to initial buzzing

  sonar_no = 1;

  sonar_no = PrioritySonar(init_dist);

  if(sonar_no == 1)
    sensors(trigPin1, echoPin1, sonar_no);
  if(sonar_no == 2)
    sensors(trigPin2, echoPin2, sonar_no);
  if(sonar_no == 3)
    sensors(trigPin3, echoPin3, sonar_no);
  if(sonar_no == 4)
    sensors(trigPin4, echoPin4, sonar_no);
  
  // if(flag == 1 || flag == 2){
  //   sensors(trigPin1, echoPin1, sonar_no);
  // }
  // //delay(300);
  
  // sonar_no++;
  // if(flag == 3 || flag == 4){
  //   sensors(trigPin2, echoPin2, sonar_no);
  // }
  // //delay(300);
  // sonar_no++;
  // if(flag == 5 || flag == 6)
  //   sensors(trigPin3, echoPin3, sonar_no);
  // //delay(300);
  // sonar_no++;
  // if(flag == 7 || flag == 8)
  //   sensors(trigPin4, echoPin4, sonar_no);

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

  s_distance1 = 0;
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


  Serial.print("s_distance1: ");
  Serial.println(s_distance1);\

  init_dist[sonar_no-1] = s_distance1;



  if(done_init)
    buzzer_logic(s_distance1);
  //buzzer_logic(s_distance1);






}

void buzzer_logic(const int s_d1){
  boi[flag] = s_d1;
  //delay(1000);
  if(s_d1 < 60.0){
      //if(difference > 5){
        tone(buzzer,buzzer_tones[sonar_no-1]);
        delay(100);
      //}
    }
    noTone(buzzer);
  // if(flag % 2 == 0){
  //   long difference = abs(boi[2] - boi[1]);
  //   Serial.print("difference: ");
  //   Serial.println(difference);
  //   //delay(1000);
  //   if(s_d1 < 60.0){
  //     //if(difference > 5){
  //       tone(buzzer,buzzer_tones[sonar_no-1]);
  //       delay(100);
  //     //}
  //   }
  //   if(flag == 8) flag = 1;
  //   else flag++;
  //   noTone(buzzer);
  // }
  // else flag++;
}

int PrioritySonar(const long * distances){
  long temp_d = distances[0];
  for(int i = 0; i < sonars; i++)
    if(temp_d > distances[i])
      temp_d = distances[i];
  for(int i = 0; i < sonars; i++)
    if(temp_d == distances[i])
      return i + 1;
}

