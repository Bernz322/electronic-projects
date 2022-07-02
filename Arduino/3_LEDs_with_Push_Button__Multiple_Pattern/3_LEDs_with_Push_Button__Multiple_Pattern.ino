/* Copyright (c) 2022 Jeffrey G. Bernadas. All rights reserved.*/

const int pinButton = 8;
const int redLED = 10;
const int yellowLED = 11;
const int greenLED = 12;
const int buzzerPin = 13;

int ledPin [] = {greenLED, yellowLED, redLED};

int buttonCounter = 0;  // Used to determine if button is pressed
int buttonStatus = 0; // Used to determine what pattern to display

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pinButton, INPUT);

  Serial.begin(9600);
}

void Pattern1() {

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin [i], HIGH);
    delay (1000);
  }
  for (int i = 2; i >= 0; i--) {
    digitalWrite(ledPin [i], LOW);
    delay (1000);
  }

}

void Pattern2() {
    for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin [i], HIGH);
    delay (500);
  }
  for (int i = 2; i >= 0; i--) {
    digitalWrite(ledPin [i], LOW);
    delay (500);
  }
}

void Pattern3() {
    for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin [i], HIGH);
    delay (100);
  }
  for (int i = 2; i >= 0; i--) {
    digitalWrite(ledPin [i], LOW);
    delay (100);
  }
}

void Pattern4() {
    for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin [i], HIGH);
    delay (50);
  }
  for (int i = 2; i >= 0; i--) {
    digitalWrite(ledPin [i], LOW);
    delay (50);
  }
}

void Pattern5() {
    for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin [i], HIGH);
    delay (10);
  }
  for (int i = 2; i >= 0; i--) {
    digitalWrite(ledPin [i], LOW);
    delay (10);
  }
}

void onAll() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin [i], HIGH);
  }
}

void offAll() {
  for (int i = 2; i >= 0; i--) {
    digitalWrite(ledPin [i], LOW);
  }
}

void loop() {

  buttonStatus = digitalRead(pinButton);
  if (buttonStatus == HIGH) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    buttonCounter = buttonCounter + 1;
    Serial.println(buttonCounter);  // Debug purposes
  } else {
    offAll();
  }

  if (buttonCounter == 1) {
    Pattern1();
  } else if (buttonCounter == 2) {
    Pattern2();
  } else if (buttonCounter == 3) {
    Pattern3();
  } else if (buttonCounter == 4) {
    Pattern4();
  } else if (buttonCounter == 5) {
    Pattern5();
  } else if (buttonCounter > 5) {
    offAll();
    buttonCounter = 0;
  }
}
