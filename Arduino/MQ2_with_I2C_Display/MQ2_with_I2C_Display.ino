#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
double value;
int smokePin = A0;
int led = 9;
int buzz = 8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(smokePin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(smokePin);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Smoke: ");
  lcd.println(value);
  delay (1000);
  if(value >200){
    digitalWrite(led, HIGH);
    digitalWrite(buzz, HIGH);
    delay(800);
    digitalWrite(led, LOW);
    digitalWrite(buzz, LOW);
  }else{
    digitalWrite(led, LOW);
    digitalWrite(buzz, LOW);
  }
}
