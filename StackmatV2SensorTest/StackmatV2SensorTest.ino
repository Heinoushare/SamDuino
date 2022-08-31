#include <CapacitiveSensor.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

CapacitiveSensor rPad = CapacitiveSensor(4, 8);
CapacitiveSensor lPad = CapacitiveSensor(4, 6);

LiquidCrystal_I2C lcd(0x27, 16, 2);


long rVal = 0;
long lVal = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  // LCD Setup
  lcd.init();     
  lcd.backlight();
  lcd.setCursor(0,0);

}

void loop() {
  // put your main code here, to run repeatedly:

  rVal = rPad.capacitiveSensor(30);
  lVal = lPad.capacitiveSensor(30);

  Serial.print("rVal: ");
  Serial.println(rVal);
  Serial.print("lVal: ");
  Serial.println(lVal);

  lcd.clear();

  lcd.print("rVal: ");
  lcd.print(rVal);
  lcd.setCursor(0, 1);
  lcd.print("lVal: ");
  lcd.print(lVal);

  delay(100);

}
