//#include <IRremote.h>
//
//int IRpin = 3;
//
//void setup() {
//  // put your setup code here, to run once:
//
//  IrSender.begin(IRpin);
////  IrSender.sendNEC(0x0, 0x18, 3);
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  // Wait for user input
////  while (Serial.available() == 0) { }
////
////  String cmd = Serial.readString();
////
////  if (cmd.equalsIgnoreCase("sUP") {
////    IrSender.sendNEC(0xE718FF00, 32);
////  }
//
//  IrSender.sendApple(0x54, 0xA, 3);
//  delay(40);
//}

int Xpin = A0;
int Ypin = A1;
int Spin = 12;
int Xval;
int Yval;
int Sval;

String oldMsg = "0,0,1;";

void setup() {
  Serial.begin(9600);

  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(Spin, INPUT);

  digitalWrite(Spin, HIGH);

  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH);
}

void loop() {

  Xval = analogRead(Xpin);
  Yval = analogRead(Ypin);
  Sval = digitalRead(Spin);

  delay(50);

  if (abs(511 - Xval) < 450) {
    Xval = 511;
  }

  if (abs(511 - Yval) < 450) {
    Yval = 511;
  }

  String sailVal = String(round((511 - Xval) / 1023. * 2.));
  String rudderVal = String(round((511 - Yval) / 1023. * 2.));
  String btnVal = String(Sval);
  String msg = sailVal + "," + rudderVal + "," + btnVal + ";";
  
//  Serial.println("Sail: " + sailVal);
//  Serial.println("Rudder: " + rudderVal);
//  Serial.println("Switch: " + btnVal);
//  Serial.println();

  if (oldMsg.equals(msg) == false) {
    Serial.println(sailVal + "," + rudderVal + "," + btnVal);
    oldMsg = msg;
  }
}
