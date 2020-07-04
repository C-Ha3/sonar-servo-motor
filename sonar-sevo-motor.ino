#include <Arduino.h>
#include <Servo.h>

Servo *servo = new Servo();

const bool isOpen = true;
const bool isClosed = false;
const int CLOSED_POSITION = 512;
const int OPEN_POSITION = 0;

const int servoPin = 5;
const int trigPin = 9;
const int echoPin = 10;

int scenario;

long duration;
int distance;

bool doorState = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo->attach(servoPin);

  Serial.begin(9600);
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3.5);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  Serial.print("Distance : ");
  Serial.println(distance);
  
if (distance < 20){

  if (doorState == isOpen){
    scenario = 1;
  }
  
  if (doorState == isClosed)
  {
    scenario = 2;
  }

  switch (scenario)
  {
  case 1:
    Serial.println("Motion detected, closing door!");
    servo->write(CLOSED_POSITION);
    
    doorState = isClosed;

    delay(1000);
    break;

  case 2:
    Serial.println("Motion detected, opening door!");
    servo->write(OPEN_POSITION);

    doorState = isOpen;

    delay(1000);
    break;
  
  default:
   Serial.println("The door is neither closed nor open...");
   break;
  }
  
}
}
