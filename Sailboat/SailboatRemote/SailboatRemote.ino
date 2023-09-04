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
int oldXval = 0;
int oldYval = 0;
int oldSval = 1;

char Xpos = '-';
char Ypos = '-';

char oldXPos = '-';
char oldYPos = '-';

bool Xchange = false;
bool Ychange = false;
bool Schange = false;

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

  if (abs(511 - Yval) < 450) {
    Ypos = '-';
  }
  else if (Yval > 511) {
    Ypos = 'u';
  }
  else if (Yval < 511) {
    Ypos = 'd';
  }

  if (abs(511 - Xval) < 450) {
    Xpos = '-';
  }
  else if (Xval > 511) {
    Xpos = 'u';
  }
  else if (Xval < 511) {
    Xpos = 'd';
  }

  delay(50);

  if (oldSval != Sval) {
    
    if (Sval == 0) {
      Serial.write('e');
      oldSval = Sval;
      return;
    }
    else if (Sval == 1) {
      Serial.write('E');
      oldSval = Sval;
      return;
    }
    
  }

  if (Ypos == oldYPos) {
    
  }
  else if (abs(511 - Yval) < 450) {
    Yval = 511;
    Ychange = true;
  }
  else if (Yval > 511) {
    oldYval = Yval;
    oldYPos = Ypos;
    Serial.write('R');
    Ychange = true;
    return;
  }
  else if (Yval < 511) {
    oldYval = Yval;
    oldYPos = Ypos;
    Serial.write('r');
    Ychange = true;
    return;
  }

  if (Xpos == oldXPos) {
    
  }
  else if (abs(511 - Xval) < 450) {
    Xval = 511;
  }
  else if (Xval > 511) {
    oldXval = Xval;
    oldXPos = Xpos;
    Serial.write('S');
    return;
  }
  else if (Xval < 511) {
    oldXval = Xval;
    oldXPos = Xpos;
    Serial.write('s');
    return;
  }

  if (Sval == 1 && abs(511 - Xval) < 450 && abs(511 - Yval) < 450 && (oldXPos != '-' || oldYPos != '-' || oldSval != 1)) {
    Serial.write('-');
  }
  oldXval = Xval;
  oldYval = Yval;
  oldSval = Sval;

  oldYPos = Ypos;
  oldXPos = Xpos;

//  String sailVal = String(round((511 - Xval) / 1023. * 2.));
//  String rudderVal = String(round((511 - Yval) / 1023. * 2.));
//  String btnVal = String(Sval);
//  String msg = sailVal + "," + rudderVal + "," + btnVal + ";";
  
//  Serial.println("Sail: " + sailVal);
//  Serial.println("Rudder: " + rudderVal);
//  Serial.println("Switch: " + btnVal);
//  Serial.println();

//  if (oldMsg.equals(msg) == false) {
//    Serial.println(sailVal + "," + rudderVal + "," + btnVal);
//    oldMsg = msg;
//  }
}
