#include <Servo.h>

Servo myservo;

const int ledPin = 5;
const int trigPin = 2;
const int echoPin = 3;
const int buzzPin = 5;

int unsigned distance;
int duration;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin (9600);
  myservo.write(50);
  delay(2000);
  myservo.write(100);
  delay(2000);
  myservo.write(0);
  delay(2000);
}

void loop() {
  lookLeft();
  lookRight();
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

void lookLeft() {
  for (int x = 0; x <= 100; x++) {
    myservo.write(x);
    distance = ultrasonicDistance();
    delay(50);
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance <= 25) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzPin, HIGH);
      Serial.print("Distance: ");
      Serial.println(distance);
      delay (25);
    } else {
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzPin, LOW);
      delay (25);
    }
  }
}

void lookRight() {
  for (int x = 100; x >= 0; x--) {
    myservo.write(x);
    distance = ultrasonicDistance();
    delay(50);
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance <= 25) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzPin, HIGH);
      Serial.print("Distance: ");
      Serial.println(distance);
      delay (25);
    } else {
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzPin, LOW);
      delay (25);
    }
  }
}
