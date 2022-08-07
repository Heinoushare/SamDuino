// Stackmat Timer

// Libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

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
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Scramble moves
String rMoves[] = {"R", "R\'", "R2"};
String lMoves[] = {"L", "L\'", "L2"};
String uMoves[] = {"U", "U\'", "U2"};
String bMoves[] = {"B", "B\'", "B2"};
String fMoves[] = {"F", "F\'", "F2"};
String dMoves[] = {"D", "D\'", "D2"};

void setup() {
  // put your setup code here, to run once:

  // Ultrasonic Sensor Setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  // LED Setup
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);

  // LCD Setup
  lcd.init();     
  lcd.backlight();
  lcd.setCursor(0,0);
                          
  // Serial Monitor
  Serial.begin(2000000);

  // Generate Random Seed
  randomSeed(analogRead(A0));

}

void loop() {
  // put your main code here, to run repeatedly:

  // Waiting for user to place cube
  while (dTT > 4) {
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


  // Generate and show Scramble to user
  String scramble = "";
  lcd.clear();
  bool secondLine = false;

  int exclude = 6;

  for (int i = 0; i < 20; i++) {

    int groupNum = exclude;
    do
    {
      groupNum = random(0, 6);
    } while (groupNum == exclude);

    String group[3];

    String cMove;

    if (groupNum == 0) {
      cMove = rMoves[random(0, 3)];
    }
    else if (groupNum == 1) {
      cMove = lMoves[random(0, 3)];
    }
    else if (groupNum == 2) {
      cMove = uMoves[random(0, 3)];
    }
    else if (groupNum == 3) {
      cMove = bMoves[random(0, 3)];
    }
    else if (groupNum == 4) {
      cMove = fMoves[random(0, 3)];
    }
    else if (groupNum == 5) {
      cMove = dMoves[random(0, 3)];
    }

    exclude = groupNum;
    
    scramble += cMove + " ";

    if (scramble.length() < 16) {
      lcd.print(cMove);
    }
    else {
      if (secondLine == false) {
        lcd.setCursor(0, 1);
        secondLine = true;
      }
      lcd.print(cMove);
    }
  }
  Serial.println(scramble);

  // Waiting for user to remove cube
  while (dTT < 4) {
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

  // Waiting for user to place cube
  while (dTT > 4) {
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
  lcd.print("Inspect! ");

  // Waiting for user to remove cube
  while (dTT < 4) {
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

  // Waiting for user to place cube

  const float countdownStart = 15;
  unsigned long startTime = millis();
  
  while (dTT > 4) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pTT = pulseIn(echoPin, HIGH);
    delay(25);
    pTD = (pTT * 765. * 5280. * 12.) / (3600. * 1000000.);
    dTT = pTD / 2.;

    lcd.clear();
    lcd.print("Inspect! ");
    float countdown = countdownStart - (float) ((millis() - startTime) / 1000.);
    lcd.print(countdown);

    if (countdown <= 0) {
      lcd.setCursor(0, 1);
      lcd.print("Time's up!");
    }
    
  }

  // Turn on red LED
  digitalWrite(rPin, HIGH);
  delay(100);


  // Waiting for user to remove cube
  while (dTT < 4) {
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
  while (dTT > 4) {
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
  float endTime = (float) (millis() - timer) / 1000.;
  lcd.print(endTime);
  Serial.println(endTime);

  digitalWrite(gPin, LOW);

  while (true) {
    // Waiting for user to reset
  }



}
