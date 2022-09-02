// Stackmat Timer V2

// Libraries
#include <CapacitiveSensor.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Touchpad setup
CapacitiveSensor rPad = CapacitiveSensor(4, 8);
CapacitiveSensor lPad = CapacitiveSensor(4, 6);

// Hands on sensor thresholds
long tLVal = 500;
long tRVal = 500;

// Variable to store sensore values
long rVal = 0;
long lVal = 0;

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

void setup()
{

  // LCD Setup
  lcd.init();     
  lcd.backlight();
  lcd.setCursor(0,0);

  // Generate Random Seed
  randomSeed(analogRead(A0));

}

void loop()
{
  
  // Waiting for user to place hands
  while (rVal < tRVal || lVal < tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }

  // Generate and show Scramble to user
  String scramble = "";
  lcd.clear();
  bool secondLine = false;

  // Which move type to exclude in the selection of the move
  int exclude = 6;

  // 20 cycles for 20 scramble steps
  for (int i = 0; i < 20; i++) {

    // Select the move type
    int groupNum = exclude;
    do
    {
      groupNum = random(0, 6);
    } while (groupNum == exclude);

    // Randomly select a move from the randomly selected move set
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

    // Update variable to exclude the move type next cycle
    exclude = groupNum;

    // Concatenate scramble string and next scramble step
    scramble += cMove + " ";

    // Print scramble
    if (scramble.length() < 16) {
      lcd.print(cMove);
    }
    else {
      // If the scramble has become more than 16 chars, print on second line (LCD is 16x2)
      if (secondLine == false) {
        lcd.setCursor(0, 1);
        secondLine = true;
      }
      lcd.print(cMove);
    }
  }

  // Waiting for user to remove hands
  while (rVal > tRVal || lVal > tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }

  // Waiting for user to place hands
  while (rVal < tRVal || lVal < tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }

  lcd.clear();
  lcd.print("Inspect! ");

  // Waiting for user to remove hands
  while (rVal > tRVal || lVal > tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }

  // Waiting for user to place hands and start inspection timer

  const float countdownStart = 15;
  unsigned long startTime = millis();

  bool plusTwo = false;
  bool dnf = false;
  
  while (rVal < tRVal || lVal < tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);

    lcd.clear();
    lcd.print("Inspect! ");
    float countdown = countdownStart - (float) ((millis() - startTime) / 1000.);
    lcd.print(countdown);

    if (countdown <= 0) {
      lcd.setCursor(0, 1);
      lcd.print("Time's up!");
      plusTwo = true;
        if (countdown < -2) {
          dnf = true;
          plusTwo = false;
        }
    }

  }

  

  lcd.clear();
  lcd.print("Go when ready");

  // Waiting for user to remove hands
  while (rVal > tRVal || lVal > tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }

  // Starting timer
  timer = millis();
  delay(100);

  // Waiting for user to place hands
  while (rVal < tRVal || lVal < tLVal) {
    lcd.clear();
    String curTime = String((double) (millis() - timer) / 1000., 3);
    lcd.print(curTime);

    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }

  // Writing final time
  lcd.clear();
  String endTime = String((double) (millis() - timer) / 1000., 3);;
  lcd.print(endTime);
  

  // Write if the user received any penalties from going over inspection time (WCA regs)
  if (dnf == true) {
    lcd.print(" (DNF)");
  }
  else if (plusTwo == true) {
    lcd.print(" (+2)");
  }

  // Waiting for user to remove hands
  while (rVal > tRVal || lVal > tLVal) {
    rVal = rPad.capacitiveSensor(30);
    lVal = lPad.capacitiveSensor(30);
  }
  
}
