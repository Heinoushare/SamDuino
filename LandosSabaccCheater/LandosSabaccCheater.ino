// Lando's Sabacc Cheater

// Servo Stuff
#include <Servo.h>
int servoPin = 9;
int servoPos = 0;
int servoStartPos = 0;
Servo myServo;

// Button Stuff
int btnPin = 2;
int btnVal;

// Misc.
int cardOut = 0;
int dt = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(btnPin, INPUT);
  digitalWrite(btnPin, HIGH);
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(servoStartPos);
}

void loop() {
  // put your main code here, to run repeatedly:
  btnVal = digitalRead(btnPin);
  if (btnVal==0) {
    if (cardOut==0) {
      servoPos = 180;
      myServo.write(servoPos);
      cardOut = 1;
    }
    else if (cardOut==1) {
      servoPos = 0;
      myServo.write(servoPos);
      cardOut = 0;
    }
    while (btnVal==0) {
      btnVal = digitalRead(btnPin);
    }
  }
}
