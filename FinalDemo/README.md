# Third Eye

A wearable aid device for assisting anyone with visual impairments. It contains: multiple sonar sensors to track approaching objects and a camera to identify faces according to a user-entered database. 

Face detection is used in order to store people in a contact list form and inform the user who is approaching. The intent is for the blind individual to know who they are talking to or who is approaching them. This concept can eventually be expanded upon to recognize strangers through reverse image-search for future prototypes. These devices will communicate about who is approaching with the user through separate speakers.

### Files
These are the final versions of our code used in our final demonstration: 
* Third Eye.jpg - a picture of our project. 
* face_recog.py - the script that is ran on the Raspberry Pi for running facial detection and sending sound cues. 
* sensor_with_speaker.ino - the script that is ran on the Arduino Uno for recognizing four sonars, priority detection, and sending sound cues.
* face_dataset.py - the script that is run if you want to add a new face for detection in your contact's list.
* faceScript.sh - the script that runs all the necessary commands to run face_recog.py as soon as the Raspberry Pi starts up.
* face_training.py - the script that is run after a new face is added to the dataset, which uses the pre-trained model.

### Authors

* Esmeralda Mendoza 
    * Helped with multiple sonar sensor wiring
	* Helped with multiple sonar sensor functionality
	* Helped with raspberry pi setup and facial recongition
	* Speaker, 3.5mm Audio Jack, SD card reader Arduino wiring and code functionality
* Johnathan Murad
	* Helped implement Sonar priority
	* Helped implement zoning to send another sound cue when they move forward or backward
	* Helped implement the buzzer logic to make the system stop issuing sound cues when the sonar with the highest priority remains in the same position
	* Helped setup Raspbian and the camera
* Richard Rangel
	* Helped implement multiple sonar sensor code
	* Helped implement zoning functionality in the case of movement on the same sonar
	* Helped construct mock display for the system
* Tasmiyah Qazi
	* Raspberry Pi facial recognition with OpenCV and camera functionality
	* Raspberry Pi speaker interface and code
	* Single sonar sensor functionality and code
	* Helped with SD card module interface with Arduino Uno

### Refernces
Tutorials and online resources:
* [Raspberry Pi facial recognition](https://www.hackster.io/mjrobot/real-time-face-recognition-an-end-to-end-project-a10826)
* [Single ultrasonic sensor](https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/)
* [Convert text to speech](https://soundoftext.com/)
* [Convert MP3 to WAV](https://audio.online-convert.com/convert-to-wav)
* [Arduino library to play from audio files](https://github.com/TMRh20/TMRpcm)
* [Audio jack breakout wiring](https://learn.sparkfun.com/tutorials/mbed-starter-kit-experiment-guide/experiment-9-pwm-sounds)
