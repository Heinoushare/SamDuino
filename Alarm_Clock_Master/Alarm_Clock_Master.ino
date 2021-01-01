#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object




String askHour="What hour of the day is it?";
String askMinute="What minute of the hour is it?";
String askAlarmDay="Would you like me to sound your alarm today, tomorrow, or never?";
String askAlarmHour="What hour of the day would you like me to sound your alarm?";
String askAlarmMinute="What minute of the hour would you like me to sound your alarm?";
int alarmPin=12;
int buttonPin=53;
int displayState=1;
int buttonNew;
int buttonOld=1;
int hour;
int minute;
String alarmDay;
int alarmHour;
int alarmMinute;
long j;
int f;
int y;
int dt2;
int dt3;
int dt4;
int hd;
int md;
unsigned long millisTime;

String p1;
String p2;
String p3;
int p4;

char k[4]="00\0";
String ks = "";
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void todaySubroutine() {
  millisTime=millis()+60000;
  while (hour<alarmHour) {
    hd=hour;
    md=minute;
    hd=hd*100;
    hd=hd+md;
    displayOnOff();
    if (millisTime<=millis()) {
      minute++;
      millisTime=millis()+60000;
    }

    

    if (minute>=60) {
      minute=0;
      hour++;
    }


  }
    millisTime=millis()+60000;
    while (hour<=alarmHour && minute<alarmMinute) {
    hd=hour;
    md=minute;
    hd=hd*100;
    hd=hd+md;
    displayOnOff();
    if (millisTime<=millis()) {
        minute++;
        millisTime=millis()+60000;
    }

    

    }
    if (minute>=60) {
      minute=0;
      hour++;
    }
    if (hour>=24) {
      hour=0;
      minute=0;
    }

    

  

    soundAlarm();

    millisTime=millis()+60000;
    while (hour<24) {
      hd=hour;
      md=minute;
      hd=hd*100;
      hd=hd+md;
      displayOnOff();
      if (millisTime<=millis()) {
        minute++;
        millisTime=millis()+60000;
      }


      if (minute>=60) {
        hour++;
        minute=0;
      }

    hour=0;
    minute=0;
}
}


void neverSubroutine() {
  millisTime=millis()+60000;
  for (y=0;y<=1;) {
    if (millisTime<=millis()) {
      minute++;
      millisTime=millis()+60000;
    }
    if (minute>=60) {
      minute=0;
      hour++;
    }
    if (hour>=24) {
      hour=0;
      minute=0;
    }
    hd=hour;
    md=minute;
    hd=hd*100;
    hd=hd+md;
    
    displayOnOff();





  }
}



void tomorrowSubroutine() {
  millisTime=millis()+60000;
  while (hour<24) {
    hd=hour;
    md=minute;
    hd=hd*100;
    hd=hd+md;
    displayOnOff();
    if (millisTime<=millis()) {
        minute++;
        millisTime=millis()+60000;
    }

    

    
    if (minute>=60) {
      minute=00;
      hour++;
    }

  }
  hour=0;
  minute=0;

  millisTime=millis()+60000;
  while (hour<alarmHour) {
    hd=hour;
    md=minute;
    hd=hd*100;
    hd=hd+md;
    displayOnOff();
    if (millisTime<=millis()) {
        minute++;
        millisTime=millis()+60000;
      }
    if (minute>=60) {
      minute=0;
      hour++;
    }
}
    millisTime=millis()+60000;
    while (hour<=alarmHour && minute<alarmMinute) {
      if (millisTime<=millis()) {
        minute++;
        millisTime=millis()+60000;
      }
      
      if (minute>=60) {
          minute=0;
          hour++;
        }
        if (hour>=24) {
          hour=0;
          minute=0;
        }
      hd=hour;
      md=minute;
      hd=hd*100;
      hd=hd+md;
      displayOnOff();
      }
      

  
    soundAlarm();
}


void soundAlarm() {
  for (j=0;j<=120;j=j+1) {
      sevseg.refreshDisplay();
      digitalWrite(alarmPin,HIGH);
      sevseg.refreshDisplay();
      dt2=random(10,500);
      sevseg.refreshDisplay();
      dt3=dt3+dt2;
      sevseg.refreshDisplay();
      delay(dt2);
      sevseg.refreshDisplay();
      digitalWrite(alarmPin,LOW);
      sevseg.refreshDisplay();
      dt2=random(10,500);
      sevseg.refreshDisplay();
      dt3=dt3+dt2;
      sevseg.refreshDisplay();
      delay(dt2);
    }
}


void displayOnOff() {
  if (displayState==1) {
      sevseg.setNumber(hd,2);
      sevseg.refreshDisplay();
    }
    if (displayState==-1) {
      shutdownDisplay();
    }

    buttonNew=digitalRead(buttonPin);

    if (buttonNew==1) {

      displayState=displayState*-1;


    while (buttonNew==1) {
      buttonNew=digitalRead(buttonPin);
      sevseg.refreshDisplay();
    }
    }
}
void shutdownDisplay() {
  digitalWrite(22, LOW);
  digitalWrite(23, LOW);
  digitalWrite(24, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
}

void setup() {
  // put your setup code here, to run once:
pinMode(alarmPin,OUTPUT);
pinMode(buttonPin,INPUT);
Serial.begin(9600);

byte numDigits = 4;  
byte digitPins[] = {22, 23, 24, 25};
byte segmentPins[] = {26, 27, 28, 29, 30, 31, 32, 33};
bool resistorsOnSegments = 0; 
// variable above indicates that 4 resistors were placed on the digit pins.
// set variable to 1 if you want to use 8 resistors on the segment pins.
sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
sevseg.setBrightness(90);

delay(500);
Serial.println(askHour);
for (j=0;j<2;) {
    char key = keypad.getKey();
  
  
  if (key){
    ks += key;
    j++;
  }
  if (j==1) {
    p1=key;
    k[1]=key;
  }
  if (j==2) {
    k[2] = key;
    p2=key;
    p3=p1.concat(p2);
    hour=ks.toInt();
    Serial.println(hour);
    ks="";
  }
}
sevseg.setNumber(hour);
for (j=0;j<1000;j=j+1) {
delay(1);
sevseg.refreshDisplay();
}
Serial.println(askMinute);
for (j=0;j<2;) {
    char key = keypad.getKey();
  
  
  if (key){
    ks += key;
    j++;
  }
  if (j==1) {
    p1=key;
    k[1]=key;
  }
  if (j==2) {
    k[2] = key;
    p2=key;
    p3=p1.concat(p2);
    minute=ks.toInt();
    Serial.println(minute);
    ks="";
  }
}
sevseg.setNumber(minute);
for (j=0;j<1000;j=j+1) {
delay(1);
sevseg.refreshDisplay();
}
Serial.println(askAlarmDay);
for (j=0;j<1;) {
    char key = keypad.getKey();
  
  
  if (key){
    ks += key;
    j++;
  }
  if (j==1) {
    p1=key;
    k[1]=key;
    ks="";
  }
}
if (p1=="A") {
  alarmDay="Today";
  Serial.println(alarmDay);
  sevseg.setNumber(1111);
  for (j=0;j<1000;j=j+1) {
    delay(1);
    sevseg.refreshDisplay();
  }
}
if (p1=="B") {
  alarmDay="Tomorrow";
  Serial.println(alarmDay);
  sevseg.setNumber(2222);
  for (j=0;j<1000;j=j+1) {
    delay(1);
    sevseg.refreshDisplay();
  }
}

if (p1=="C") {
  alarmDay="Never";
  Serial.println(alarmDay);
  sevseg.setNumber(3333);
  for (j=0;j<1000;j=j+1) {
    delay(1);
    sevseg.refreshDisplay();
  }
}
if (alarmDay.equalsIgnoreCase("Today") || alarmDay.equalsIgnoreCase("Tomorrow")) {
Serial.println(askAlarmHour);
for (j=0;j<2;) {
    char key = keypad.getKey();
  
  
  if (key){
    ks += key;
    j++;
  }
  if (j==1) {
    p1=key;
    k[1]=key;
  }
  if (j==2) {
    k[2] = key;
    p2=key;
    p3=p1.concat(p2);
    alarmHour=ks.toInt();
    Serial.println(alarmHour);
    ks="";
  }
}
sevseg.setNumber(alarmHour);
for (j=0;j<1000;j=j+1) {
  delay(1);
  sevseg.refreshDisplay();
}
Serial.println(askAlarmMinute);
for (j=0;j<2;) {
    char key = keypad.getKey();
  
  
  if (key){
    ks += key;
    j++;
  }
  if (j==1) {
    p1=key;
    k[1]=key;
  }
  if (j==2) {
    k[2] = key;
    p2=key;
    p3=p1.concat(p2);
    alarmMinute=ks.toInt();
    Serial.println(alarmMinute);
    ks="";
  }
}
sevseg.setNumber(alarmMinute);
for (j=0;j<1000;j=j+1) {
  delay(1);
  sevseg.refreshDisplay();
  }
}

}

void loop() {
  // put your main code here, to run repeatedly:
if (alarmDay.equalsIgnoreCase("Today")) {
  todaySubroutine();
}

if (alarmDay.equalsIgnoreCase("tomorrow")) {
  tomorrowSubroutine();

}

if (alarmDay.equalsIgnoreCase("Never")) {
  neverSubroutine();
}
}
