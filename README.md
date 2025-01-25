# colour-sensor-controller

controller detects different colour frequencies and presses a key allocated to each colour 
ultra sonic motion sensor detects a specific distance and presses the letter E


references:
(for sensor library)
https://github.com/nthnn/TCS3200

(waveshare colour sensore wiki)
https://www.waveshare.com/wiki/Color_Sensor#Overview

--------------------------------

previous code?/ sensor test:
(1)
#include <NewPing.h>
#include <softwareSerial.h>
#include <TCS3200.h>

SoftwareSerial mySerial(10,11);

#define S0_PIN 15
#define S1_PIN 2
#define S2_PIN 0
#define S3_PIN 4
#define OUT_PIN 16

TCS3200 tcs3200(S0_PIN,S1_PIN,S2_PIN,S3_PIN,OUT_PIN);

String color_indices[] = {"Red", "Green", "Blue"};

RGBColor color_value[] = {
  {255,0,0}, //red
  {0,255,0},  //green
  {0,0,255}, //blue
};  // used to define corresponding colors 

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 10
#define MAX_DISTANCE2 5

const int distanceThresholdB = 10;
const int distanceThresholdT = 5;

NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE,MAX_DISTANCE2);

void setup() {

tcs3200.begin();
tcs3200.frequency_scaling(TCS3200_OFREQ_20P);

 Serial.begin(9600);
 mySerial.begin(115200); 
mySerial.println("TCS3200 Full Example");
mySerial.println("-----------------------------");

mySerial.println("calibrating...");

mySerial.println("please face the white side of the lid");
delay(1000);
tcs3200.calibrate_light();

mySerial.println("please face the dark side of the lid");
delay(1000);
tcs3200.calibrate_dark();

mySerial.println("done calibrating!");
tcs3200.calibrate();
delay(1000);

}

void loop() {
if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n'); // Read input
    // Process data and optionally send a response
    Serial.println("Message received: " + received);
  }

long duration, distance;
duration = pulseIn(ECHO_PIN, HIGH);
distance = duration * 0.034/2;

Serial.print("ping");
Serial.print(sonar.ping_cm());
Serial.print("cm");

if (distance <= distanceThresholdB){
  serial.println("LB/RB")
else { 
serial.println("0")
 }
}
if (distance <= distanceThresholdT){
  serial.print("LT/RT")
  else{ 
  serial.println("0")
 }
}

tcs3200.loop();

mySerial.println("------------------------");

RGBColor rgb_color = tcs3200.read_rgb_color();
mySerial.println("Red:" + String(rgb_color.red)+
  ",Green :" + String(rgb_color.green)+
  ",Blue :" + String(rgb_color.blue));

if (serial.print == ("Red")) {
// move to directiioonn
} else {
  serial.print("0")
}
if (serial.print == ("Green")) {
// move to directiioonn
} else {
  serial.print("0")
}
if (serial.print == ("Blue")) {
// move to directiioonn
} else {
  serial.print("0")
}




delay(3000);

}

(2)

#include <Keyboard.h>
#include <TCS3200.h>

#define S0_PIN 4
#define S1_PIN 5
#define S2_PIN 6
#define S3_PIN 7
#define OUT_PIN 8

int Frequency = 0;

void setup() {

  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);



digitalWrite(S0_PIN, HIGH);
digitalWrite(S1_PIN, HIGH);

Serial.begin(9600);

delay(1000);
}

void loop(){

 //read red
digitalWrite(S2_PIN, LOW);
digitalWrite(S3_PIN, LOW);
Frequency = pulseIn(OUT_PIN, LOW);
Serial.println("R:");
Serial.print(Frequency);
Serial.print(" ");
delay(1000);
//read green
digitalWrite(S2_PIN, HIGH);
digitalWrite(S3_PIN, HIGH);
Frequency = pulseIn(OUT_PIN,LOW);
Serial.println("G:");
Serial.print(Frequency);
Serial.print(" ");
delay(1000);
//read blue
digitalWrite(S2_PIN, LOW);
digitalWrite(S3_PIN, HIGH);
Frequency = pulseIn(OUT_PIN, LOW);
Serial.println("B:");
Serial.print(Frequency);
Serial.print(" ");
delay(1000);


if (("R:") <  ("G:") && ("B:")) {
  Serial.println("Detected: Red");
 
  delay(1000);

} else {
  Keyboard.releaseAll(); }

delay(500);

if (("G:") <  ("R:") && ("B:")) {
  Serial.println("Detected: Green");
 
  delay(1000);
 
} else {
  Keyboard.releaseAll(); }

delay(500);

  if (("B:") < ("R:") || ("G:")){ 
  Serial.println("Detected: Blue"); 
 
  delay(1000);
  
} else {
   }

delay(500);
}


