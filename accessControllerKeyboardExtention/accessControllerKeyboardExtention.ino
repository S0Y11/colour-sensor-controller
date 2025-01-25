
#include <Keyboard.h>
#include <NewPing.h>
#include <TCS3200.h>

#define S0_PIN 4
#define S1_PIN 5
#define S2_PIN 6
#define S3_PIN 7
#define OUT_PIN 8


#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 7
const int distanceThreshold = 7;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

int Frequency = 0;

void setup() {

  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);

Keyboard.begin();

digitalWrite(S0_PIN, HIGH);
digitalWrite(S1_PIN, HIGH);

Serial.begin(9600);

delay(1000);
}

void loop(){

  delay(50);
  Serial.print("ping");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");

  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delay(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034/2;


 //read red
digitalWrite(S2_PIN, LOW);
digitalWrite(S3_PIN, LOW);
Frequency = pulseIn(OUT_PIN, LOW);
Serial.print("R:");
Serial.print(Frequency);
Serial.print(" ");
delay(100);
//read green
digitalWrite(S2_PIN, HIGH);
digitalWrite(S3_PIN, HIGH);
Frequency = pulseIn(OUT_PIN,LOW);
Serial.print("G:");
Serial.print(Frequency);
Serial.print(" ");
delay(100);
//read blue
digitalWrite(S2_PIN, LOW);
digitalWrite(S3_PIN, HIGH);
Frequency = pulseIn(OUT_PIN, LOW);
Serial.print("B:");
Serial.print(Frequency);
Serial.print(" ");
delay(100);

if (("R:") <  ("G:") || ("B:")) {
  Serial.println("Detected: Red");
  Keyboard.press('A');
  delay(100);
  Keyboard.release('A');
  delay(1000);
} else {
  Keyboard.releaseAll(); }

delay(500);

if (("G:") <  ("R:") || ("B:")) {
  Serial.println("Detected: Green");
  Keyboard.press('W');
  delay(100);
  Keyboard.release('W');
    delay(1000);
} else {
  Keyboard.releaseAll(); }

delay(500);

  if (("B:") < ("R:") || ("G:")){ 
  Serial.println("Detected: Blue"); 
  Keyboard.press('D');
  delay(100);
  Keyboard.release('D');
   delay(1000);
} else {
  Keyboard.releaseAll(); }

delay(500);

if (distance <= distanceThreshold) {
  Keyboard.press('E');
  Keyboard.release('E');
  delay(500);
} else {
  Keyboard.releaseAll();
}
delay(500);
}
 
