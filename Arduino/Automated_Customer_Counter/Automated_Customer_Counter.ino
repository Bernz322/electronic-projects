/* Copyright (c) 2022 Jeffrey G. Bernadas. All rights reserved.*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledRed = 6; 
const int ledGreen = 7; 
const int buzzer = 4; 
const int trig = 2; 
const int echo = 3; 
const int relay = 8; 

int duration;
int distance;
int peopleCount = 0;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; // this is in cm

}

void loop() {
  delay(2000);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: "); // For debugging purposes
  Serial.println(distance); //  For debugging purposes

  if (distance <= 16 && distance >= 0) {
    digitalWrite(buzzer, HIGH);
    peopleCount += 1;
    delay(500);
    digitalWrite(buzzer, LOW);
  } else if (distance >= 16.5 && distance <= 33) {
    digitalWrite(buzzer, HIGH);
    peopleCount -= 1;
    delay(500);
    digitalWrite(buzzer, LOW);
  }

  Serial.print("People Inside: ");  // For debugging purposes
  Serial.println(peopleCount);  // For debugging purposes
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Count: ");
  lcd.print(peopleCount);

  
  if (peopleCount <= 5 && peopleCount >= 0) {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(relay, 0);
  // If the number of customer entered the premises is more than 5, warn.
  } else if (peopleCount > 5) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(relay, 1);
    digitalWrite(buzzer, HIGH);
  }
}
