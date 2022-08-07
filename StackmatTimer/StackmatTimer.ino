// Stackmat Timer

// Libraries
#include <LiquidCrystal.h>

// Ultrasonic Variables
int trigPin = 5;
int echoPin = 4;
int pTT;
float pTD;
float dTT;

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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  
  Serial.begin(2000000);

  lcd.begin(16,2);

}

void loop() {
  // put your main code here, to run repeatedly:

  dTT = 30;

  while (dTT > 5) {
//    dTT = getDist(trigPin, echoPin);

    Serial.println(dTT);

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

  digitalWrite(rPin, HIGH);
  delay(100);

  while (dTT < 5) {
    Serial.println(dTT);
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

  timer = millis();
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, HIGH);
  delay(100);

  while (dTT > 5) {
    Serial.println(dTT);
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

  lcd.clear();
  lcd.print((double) (millis() - timer) / 1000.);

  digitalWrite(gPin, LOW);

  delay(200);

  while (true) {
    // Waiting for user to reset
  }



}
