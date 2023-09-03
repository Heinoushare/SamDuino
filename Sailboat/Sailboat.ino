#include <Servo.h>
//#include "ArduinoLowPower.h"

int rudderPin = 3;
int rudderAngle = 80;
int rudderChange = 0;
Servo rudder;

const int servoChange = 1;


int sailPin = 5;
int sailAngle = 90;
int sailChange = 0;
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

  pinMode(sailPin, OUTPUT);
  sail.attach(sailPin);

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
  
    String msg = Serial.readString();
    Serial.print(msg);

    delay(10);

    digitalWrite(xbeeRST, LOW);
    delay(10);
    digitalWrite(xbeeRST, HIGH);

    
    
    char *cmd = strtok(msg.c_str(), ";");
    char *lastCmd;

    while (cmd != NULL) {
      lastCmd = cmd;
      cmd = strtok(NULL, ";");
    }


    lastCmd = strtok(lastCmd, ",");
    sailChange = atoi(lastCmd);

    for (int i = 0; i < 2; i++) {
      lastCmd = strtok(NULL, ",");
      if (i == 0) {
        rudderChange = atoi(lastCmd);
      }
      else if (i == 1) {
        joyBtn = atoi(lastCmd);
      }
    }

  }

  awake = false;

  if (sailChange != 0 && rudderChange != 0) {
    sailChange = 0;
  }

//  if (sailChange != 0) {
//    // Sail stuff
////    sailAngle += sailChange * servoChange;
     sail.write(sailAngle + sailChange * 8);
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

void wakeup() {
  
}
