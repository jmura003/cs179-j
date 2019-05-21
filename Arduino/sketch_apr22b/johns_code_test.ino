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

bool same_sonar = false;
/*haha*/ long boi[2];

int trigArray[4] = {12, 7, 2, 4}; //array of the trig pins accessilbe via sonar_no - 1
int echoArray[4] = {10, 6, 3, 5}; //same thing as trigArray but for echo

int flag = 0;

bool done_init = false;

int buzzer_tones[] = {500, 1000, 1500, 2000}; // each element represents sonars #s 1-4

long init_dist[4];

int sonar_list[10];

int s_distance1 = 0;

int same_dist = 0;
int sonar_no = 0;


void sensors(const int, const int, const int);
void buzzer_logic(const int);
int PrioritySonar(const long *);


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

  init_dist[sonar_no-1] = s_distance1;

  if(done_init)
    buzzer_logic(s_distance1);
}
void sensors2(const int trigPin, const int echoPin, const int sonar_no) { //used only if staying on same sonar
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

  init_dist[sonar_no-1] = s_distance1;

  //if(done_init)
  // buzzer_logic(s_distance1);
}


void buzzer_logic(const int s_d1){
  //boi[flag] = s_d1;
  //delay(1000);
  
  if(s_d1 < 60.0){
    if(!same_sonar){
      Serial.println("ahfkehlkghaet"); //the code keeps entering here when it shouldnt if you stay on the same sonar
      for(int i = 0; i < 4; i++){
        tone(buzzer,buzzer_tones[sonar_no-1]);
        delay(100);
        noTone(buzzer);
        delay(50);
      }
      Serial.print("sonar number: ");
      Serial.println(sonar_no);
      if(flag > 0){
        sonar_list[flag] = sonar_no;
        if(sonar_list[flag] == sonar_list[flag-1]){
          same_sonar = true;
          flag = 0;
        }
      }
      else
        sonar_list[0] = sonar_no;
      if(!same_sonar)
        flag++;
    }
    //logic for calculating the difference 
    //can be done here
    else { 
      noTone(buzzer);
      Serial.println("you are in this state");
     
      if(flag > 0){
        sonar_list[flag] = sonar_no;
        if(sonar_list[flag] != sonar_list[flag-1]){
          same_sonar = false;
          flag = 0;
        }
      }
      else{
        sonar_list[0] = sonar_no;
      }

      if(same_sonar){
        //need to check distance and if theres movement restart
        flag++;

        int temp = s_distance1; //store old distance
        int trigNum = trigArray[sonar_no - 1]; 
        int echoNum = echoArray[sonar_no - 1];
        sensors2(trigNum, echoNum, sonar_no); //need to update the distance with the same sonar if in this state

        // Calculating the first distance of S1 and S2
        int diff = abs(s_distance1 - temp);
        Serial.println(diff);
        
        if(diff > 3 && diff < 60){ 
          Serial.println("reset same_sonar");
          same_sonar = false; //want it to buzz again
               
        }
      
      }
      
    }
  

    if(flag >= 2)
      flag = 0;
  }
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
