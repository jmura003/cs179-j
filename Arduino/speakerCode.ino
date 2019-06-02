#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SPI.h>
#include <SD.h>
#define SD_ChipSelectPin 4

TMRpcm tmrpcm;

void setup() {
  //char* file = "test.wav";
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }

  tmrpcm.setVolume(4);
//  tmrpcm.play("right.wav");
////  delay(1000);
////  tmrpcm.play("left.wav");
////  delay(1000);
////  tmrpcm.play("behind.wav");
////  delay(1000);
////  tmrpcm.play("front.wav");
}
// put your setup code here, to run once:


void loop() {
  /*delay(3000);    //test code
    tone(speaker,500);
    delay(100);
    noTone(speaker);
  */
  tmrpcm.play("right.wav");
  delay(1000);
  tmrpcm.play("left.wav");
  delay(1000);
  tmrpcm.play("behind.wav");
  delay(1000);
  tmrpcm.play("front.wav");
  delay(1000);
  // put your main code here, to run repeatedly:

}
