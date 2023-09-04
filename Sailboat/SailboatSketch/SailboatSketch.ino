#include <Servo.h>
//#include "ArduinoLowPower.h"

int rudderPin = 3;
int rudderAngle = 80;
int rudderChange = 0;
Servo rudder;

const int servoChange = 1;


int sailPin = 5;
int sailAngle = 90;
int sailChange = 1;
Servo sail;

int joyBtn = 1;
int rescueDT = 250;

int cmdDT = 25;

int lPin = 13;

int xbeeRST = 2;

int xbeeRSSI = 4;

bool awake = false;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(rudderPin, OUTPUT);
  rudder.attach(rudderPin);
  rudder.write(rudderAngle);

  pinMode(sailPin, OUTPUT);
  sail.attach(sailPin);
  sail.write(sailAngle);

  pinMode(lPin, OUTPUT);
  digitalWrite(lPin, HIGH);

  pinMode(xbeeRST, OUTPUT);
  digitalWrite(xbeeRST, HIGH);

  // Set pin as INPUT_PULLUP to avoid spurious wakeup
//  pinMode(xbeeRSSI, INPUT_PULLUP);
  // Attach a wakeup interrupt on pin 8, calling wakeup() when the device is woken up
//  LowPower.attachInterruptWakeup(xbeeRSSI, wakeup, CHANGE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (awake == false) {
//    LowPower.sleep();
  }
  
  if (Serial.available()) {

    char val = Serial.read();
    switch(val)
    {
      case '-':
        joyBtn = 1;
        sail.write(sailAngle);
        rudderChange = 0;
        break;
      
      case 'e':
        joyBtn = 0;
        break;
  
      case 'E':
        joyBtn = 1;
        break;
        
      case 'S':
        sail.write(sailAngle + sailChange * 8);
        break;
  
      case 's':
        sail.write(sailAngle - sailChange * 8);
        break;
  
      case 'R':
        rudderChange = -1;
        break;
  
      case 'r':
        rudderChange = 1;
        break;
  
    }
  
    xbeeRefresh();
    
  }

  awake = false;

//  if (sailChange != 0 && rudderChange != 0) {
//    sailChange = 0;
//  }

//  if (sailChange != 0) {
//    // Sail stuff
////    sailAngle += sailChange * servoChange;
//     sail.write(sailAngle + sailChange * 8);
//
//    if (sailAngle > 160) {
//      sailAngle = 160;
//    }
//    else if (sailAngle < 5) {
//      sailAngle = 5;
//    }
//    awake = true;
//    delay(cmdDT);
//  }
//  else {
//    sail.write(sailAngle);
//  }

  if (rudderChange != 0) {
    // Rudder stuff
    rudderAngle -= rudderChange * servoChange;

    if (rudderAngle > 160) {
      sailAngle = 160;
    }
    else if (rudderAngle < 5) {
      rudderAngle = 5;
    }
    awake = true;
    delay(cmdDT);
  }

  if (joyBtn == 0) {
    rudder.write(35);
    delay(rescueDT);
    rudder.write(125);
    delay(rescueDT);

    awake = true;
  }

  rudder.write(rudderAngle);

//  sail.write(sailAngle);
  
}

void xbeeRefresh() {
  delay(10);
  digitalWrite(xbeeRST, LOW);
  delay(10);
  digitalWrite(xbeeRST, HIGH);
}

void wakeup() {
  
}
