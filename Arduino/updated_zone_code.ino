//trigger pin does not need pwm
//echo pin needs pwm

#define sonars 4 //number of sonars 
#define MAX_DIST 150.0
const int trigPin1 = 8; //changed 12 to 8
const int echoPin1 = 9; //changed 10 to 9
const int trigPin2 = 7;
const int echoPin2 = 6;
const int trigPin3 = 2;
const int echoPin3 = 3;
const int trigPin4 = 4;
const int echoPin4 = 5;
const int buzzer = 11; //

//esmerald needs 11, 12, 13
bool same_sonar = false;
/*haha*/ long boi[2];

//int trigArray[4] = {12, 7, 2, 4}; //array of the trig pins accessilbe via sonar_no - 1
int trigArray[4] = {8, 7, 2, 4}; //array of the trig pins accessilbe via sonar_no - 1

//int echoArray[4] = {10, 6, 3, 5}; //same thing as trigArray but for echo
int echoArray[4] = {9, 6, 3, 5}; //same thing as trigArray but for echo

int flag = 0;

bool done_init = false;

int buzzer_tones[] = {500, 1000, 1500, 2000}; // each element represents sonars #s 1-4

long init_dist[4];

int sonar_list[2];

int s_distance1 = 0;

int same_dist = 0;
int sonar_no = 0;
int sonar_zone = 0; //1, 2 for testing

void sensors(const int, const int, const int);
void buzzer_logic(const int);
int PrioritySonar(const long *);
int zone_check(const long);


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
  for(int i = 0; i < 10; i++)
    sonar_list[i] = 1000;
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
}

//function with paramters trigPin, echoPin, sonar_no
//function activates sensors based on which which pins
//are passed in to the function
void sensors(const int trigPin, const int echoPin, const int sonar_no) {
  // Clears the trigPin
  // Serial.println("--------------------");
  // Serial.print("sonar number: ");
  // Serial.println(sonar_no);
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
  if(!done_init)
    init_dist[sonar_no-1] = s_distance1;

  if(done_init)
    buzzer_logic(s_distance1);
}


//just to return the distance from a sensor reading
int sensors2(const int trigPin, const int echoPin, const int sonar_no) { 
  
  long s_duration1 = 0;
  long s_distance2 = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  s_duration1 = pulseIn(echoPin, HIGH);

  // Calculating the first distance of S1 and S2
  s_distance2 = s_duration1 * 0.034 / 2;

  return s_distance2;
}

void buzzer_logic(const int s_d1){
    bool diff_sonar = true;
    if(!same_sonar){
      if(s_d1 < MAX_DIST){
        for(int i = 0; i < 4; i++){
          tone(buzzer,buzzer_tones[sonar_no-1]);
          delay(100);
          noTone(buzzer);
          delay(50);
        }
      }
      Serial.print("sonar number: ");
      Serial.println(sonar_no);
      if(flag > 0){
        Serial.print("s_distance1: ");
        Serial.println(s_distance1);
        sonar_zone = zone_check(s_distance1);
        Serial.print("current zone: ");
          Serial.println(sonar_zone);
        sonar_list[flag] = sonar_no;
        if(sonar_list[flag] == sonar_list[flag-1]){
          same_sonar = true;
          //flag = 0;
        }
        else
          flag = 0;
      }
      else{
        sonar_list[flag] = sonar_no;
        flag = 1;
      }
    }
    //logic for calculating the difference 
    //can be done here
    else { 
      long temp_arr[sonars];
      if(s_d1 > MAX_DIST){
        flag = 0; 
        same_sonar = false;
      }
      if(same_sonar){
        noTone(buzzer);
        Serial.print("same buzzer: ");
        Serial.println(sonar_list[flag]);

        if(flag == 1){
          sonar_list[flag] = sonar_no;
          flag = 0;
        }
        else{
          sonar_list[flag] = sonar_no;
          flag = 1;
        }
        if(sonar_list[0] != sonar_list[1]){
          same_sonar = false;
          flag = 0;
        }

        if(zone_check(s_distance1) != -1 && sonar_zone != zone_check(s_distance1)){
          Serial.print("different zone: ");
          Serial.println(sonar_zone);
          sonar_zone = zone_check(s_distance1);
          flag = 0;
          same_sonar = false;
        }

        //need to set a range, if on same sonar and the range zone is different
        //test 0-10 10-20
      }
  

      
      }
      
    if(flag >= 2)
      flag = 0;
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

//checking zone size of 25
int zone_check(const long s_d1){
  if(s_d1 > 0.0 && s_d1 < 25.0)
      return 1;
  else if(s_d1 >= 25.0 && s_d1 < 50.0)
      return 2;
  else if(s_d1 >= 50.0 && s_d1 < 75.0)
      return 3;
  else if(s_d1 >= 75.0 && s_d1 < 100.0)
      return 4;
  else if(s_d1 >= 100.0 && s_d1 < 125.0)
      return 5;
  else if(s_d1 >= 125.0 && s_d1 < 150.0)
      return 6;
 /* else if(s_d1 >= 90.0 && s_d1 < 105.0)
      return 7;
  else if(s_d1 >= 105.0 && s_d1 < 120.0)
      return 8;
  else if(s_d1 >= 80.0 && s_d1 < 90.0)
      return 9;
  else if(s_d1 >= 90.0 && s_d1 < 100.0)
      return 10;*/
  else
      return -1; //error
  
}
