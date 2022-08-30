#include <CapacitiveSensor.h>

CapacitiveSensor rPad = CapacitiveSensor(4, 8);
CapacitiveSensor lPad = CapacitiveSensor(4, 6);

long rVal = 0;
long lVal = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  rVal = rPad.capacitiveSensor(30);
  lVal = lPad.capacitiveSensor(30);

  Serial.print("rVal: ");
  Serial.println(rVal);
  Serial.print("lVal: ");
  Serial.println(lVal);

}
