// BeanDuino

unsigned long millisTime;
int displayTime = 3000;
int lightFirstDigit;
int lightFirstDigitClone;
int lightSecondDigit;
int lightThirdDigit;

#include "SevSeg.h"
SevSeg sevseg; 

void shutdownDisplay() {
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}


// Water level stuff
int resVal; // Sensor Value
int resPin = A5; // Sensor Pin

int dt = 500; // Delay Time

void readWaterLevel() {
  resVal = analogRead(resPin); //Set the sensor value

  if (resVal <= 100) { 
    Serial.println("Water level: Empty");
  }
  // If water level is empty
  
  else if (resVal > 100 && resVal <= 300) {
    Serial.println("Water level: Low");
  }
  // Elif water level low

  else if (resVal > 300 && resVal <= 350) {
    Serial.println("Water level: Medium");
  }
  // Elif water level medium

  else if (resVal > 330) {
    Serial.println("Water level: High");
  }
  // Elif water level high
}
// This function will read the water level

// LED setup stuff
int ledPin = 13;

// Execute Order Photoresistor stuff
int lightLevel;
int lightPin = A0;

void readLightLevel() {
  lightLevel = analogRead(lightPin);
  Serial.println(lightLevel);
  if (lightLevel < 530) {
    
    while (lightLevel < 530) {
      lightLevel = analogRead(lightPin);
      Serial.println(lightLevel);
      Serial.println("Where is the sun!?");
      digitalWrite(ledPin, LOW);
      delay(dt);
      lightLevel = lightLevel * 0.01;
      Serial.println(lightLevel);
      sevseg.setNumber(lightLevel);
      sevseg.refreshDisplay();
      lightLevel = analogRead(lightPin);
    }
    digitalWrite(ledPin, HIGH);
  }
}
// This function will read the light level

void setup() {
  // put your setup code here, to run once:

  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

    
  pinMode(resPin, INPUT); // PINMODE!!! I almost forgot about this.
  pinMode(lightPin, INPUT); // Pinmode for Photoresistor
  pinMode(ledPin, OUTPUT); // Pinmode for LED
  Serial.begin(9600); // Start the serial monitor (good ol' 9600)
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  millisTime = millis() + displayTime;
  while (millisTime > millis()) {
    lightLevel = analogRead(lightPin);
    lightFirstDigit = lightLevel * 0.01;
    lightFirstDigitClone = lightFirstDigit * 10;
    //Serial.println(lightFirstDigit);
    sevseg.setNumber(lightFirstDigit, 0);
    sevseg.refreshDisplay();

    //Serial.println("1");
      
    lightLevel = analogRead(lightPin);
    Serial.println(lightFirstDigitClone);
    if (lightLevel < 530) {
      
      digitalWrite(ledPin, LOW);
     }
  
     else {
      digitalWrite(ledPin, HIGH);
     }
  }  

  millisTime = millis() + displayTime;
  while (millisTime > millis()) {
    
    lightFirstDigit = lightFirstDigit * 100;
    lightSecondDigit = lightLevel - lightFirstDigit;
    
    lightSecondDigit = lightSecondDigit * 0.1;
    //lightFirstDigitClone = lightFirstDigitClone * 10;
    lightSecondDigit = lightSecondDigit - lightFirstDigitClone;
    
    //Serial.println(lightSecondDigit);
    Serial.println(lightFirstDigitClone);
    sevseg.setNumber(lightSecondDigit);
    sevseg.refreshDisplay();

    //Serial.println("2");
    
      
    lightLevel = analogRead(lightPin);
    //Serial.println(lightLevel);
    if (lightLevel < 530) {
      
      digitalWrite(ledPin, LOW);
     }
  
     else {
      digitalWrite(ledPin, HIGH);
     }
  }  

  millisTime = millis() + displayTime;
  while (millisTime > millis()) {
    lightSecondDigit = lightSecondDigit * 10;
    lightThirdDigit = lightFirstDigit + lightSecondDigit;
    //Serial.println(lightThirdDigit);
    sevseg.setNumber(lightThirdDigit, 0);
    sevseg.refreshDisplay();

    //Serial.println("3");
      
    lightLevel = analogRead(lightPin);
    //Serial.println(lightLevel);
    if (lightLevel < 530) {
      
      digitalWrite(ledPin, LOW);
     }
  
     else {
      digitalWrite(ledPin, HIGH);
     }
  }  

  millisTime = millis() + 2000;
  while (millisTime > millis()) {
    shutdownDisplay();

    //Serial.println("4");
      
    lightLevel = analogRead(lightPin);
    Serial.println(lightLevel);
    if (lightLevel < 530) {
      
      digitalWrite(ledPin, LOW);
     }
  
     else {
      digitalWrite(ledPin, HIGH);
     }
  }  
}
