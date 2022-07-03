#include <Servo.h>

Servo myservo;

const int ledPin = 7;
const int trigPin = 10;
const int echoPin = 11;
const int buzzPin = 2;

// Motors pins
const int m1a = 3;
const int m1b = 4;
const int m2a = 5;
const int m2b = 6;


int pos = 0;
int unsigned distance;
int duration;
boolean goesForward = false;

void setup() {
  myservo.attach(9);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motors
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);

  Serial.begin (9600);

  myservo.write(50);
  delay(2000);
  distance = ultrasonicDistance();
  delay(100);
  distance = ultrasonicDistance();
  delay(100);
  distance = ultrasonicDistance();
  delay(100);
  distance = ultrasonicDistance();
  delay(100);
}

void loop() {

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  
  
  forwardMotors();
  distance = ultrasonicDistance();

  if (distance <= 20) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzPin, HIGH);
    stopMotors();
    delay(300);
    backwardMotors();
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzPin, LOW);
    delay(300);
    stopMotors();
    delay(300);
    distanceRight = servoRight();
    delay(300);
    distanceLeft = servoLeft();
    delay(300);

    if (distanceRight >= 50) {
      Serial.print("Right: ");
      Serial.println(distanceRight);
      rightMotors();
      stopMotors();
      forwardMotors();
    } else if (distanceLeft >=50){
      Serial.print("Left: ");
      Serial.println(distanceLeft);
      leftMotors();
      stopMotors();
      forwardMotors();
    }else{
      forwardMotors();
    }
  } else {
    forwardMotors();
  }
  distance = ultrasonicDistance();
}

int ultrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

int servoRight() {
  myservo.write(0);
  delay(500);
  int distance = ultrasonicDistance();
  delay(100);
  myservo.write(50);
  return distance;
}

int servoLeft() {
  myservo.write(100);
  delay(500);
  int distance = ultrasonicDistance();
  delay(100);
  myservo.write(50);
  return distance;
}



void forwardMotors() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

void backwardMotors() {
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}

void rightMotors() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);

  delay (500);
}

void leftMotors() {
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);

  delay (500);
}

void stopMotors() {
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}
