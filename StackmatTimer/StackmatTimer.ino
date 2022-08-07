// Stackmat Timer

// Libraries
#include <LiquidCrystal.h>

// Ultrasonic Variables
int trigPin = 5;
int echoPin = 4;
int pTT;
float pTD;
float dTT = 30; // 30 is a placeholder value

// LED Variables
int rPin = 3;
int gPin = 13;

// Timer Variables
unsigned long timer;

// LCD Variables
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:

  // Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  // LED Setup
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);

  // LCD Setup
  lcd.begin(16,2);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Waiting for user to place hand
  while (dTT > 5) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pTT = pulseIn(echoPin, HIGH);
    delay(25);
    pTD = (pTT * 765. * 5280. * 12.) / (3600. * 1000000.);
    dTT = pTD / 2.;
  }

  // Turn on red LED
  digitalWrite(rPin, HIGH);
  delay(100);


  // Waiting for user to remove hand
  while (dTT < 5) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pTT = pulseIn(echoPin, HIGH);
    delay(25);
    pTD = (pTT * 765. * 5280. * 12.) / (3600. * 1000000.);
    dTT = pTD / 2.;
  }

  // Starting timer
  timer = millis();
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, HIGH);
  delay(100);


  // Waiting for user to place hand
  while (dTT > 5) {
    lcd.clear();
    lcd.print((double) (millis() - timer) / 1000.);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pTT = pulseIn(echoPin, HIGH);
    delay(25);
    pTD = (pTT * 765. * 5280. * 12.) / (3600. * 1000000.);
    dTT = pTD / 2.;
  }

  // Writing final time
  lcd.clear();
  lcd.print((double) (millis() - timer) / 1000.);

  digitalWrite(gPin, LOW);

  while (true) {
    // Waiting for user to reset
  }



}
