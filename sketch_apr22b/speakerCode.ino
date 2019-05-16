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

  tmrpcm.setVolume(2);
  tmrpcm.play("test.wav");
}
// put your setup code here, to run once:


void loop() {
  /*delay(3000);    //test code
    tone(speaker,500);
    delay(100);
    noTone(speaker);
  */
  // put your main code here, to run repeatedly:

}
