int redPin=8;
int greenPin=9;
int bluePin=10;
String myColor;
String greeting="Rob: My name is Rob, what is yours?";
String greeting2="Rob: Hello ";
String msg="Rob: What colour do you want?";
int dt=150;
String myName;
String sorry="Sorry! I can't make that color (yet). Maybe you should ask Sam to let me make it.";
int verify;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

  delay(dt);
  Serial.println();
  delay(dt);
  Serial.println(greeting);
while (Serial.available()==0) {
  
}

myName=Serial.readString();
Serial.println();
Serial.print(myName);
Serial.print(": ");
Serial.println(myName);
Serial.println();
Serial.print(greeting2);
Serial.print(myName);
Serial.println(".");
}

void loop() {
  // put your main code here, to run repeatedly:
verify=0;
delay(dt);
Serial.println();
delay(dt);
Serial.println(msg);
while (Serial.available()==0); {
  
}
myColor=Serial.readString();


if (myColor.equalsIgnoreCase("red")) { 
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Red Sus.");
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
}

if (myColor.equalsIgnoreCase("green")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Lean in Green!");
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,HIGH);
  digitalWrite(bluePin,LOW);
}

if (myColor.equalsIgnoreCase("blue")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Cool in Blue!");
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,HIGH);
}


if (myColor.equalsIgnoreCase("white")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Bright in White!");
  analogWrite(redPin,255);
  analogWrite(greenPin,255);
  analogWrite(bluePin,255);

}

if (myColor.equalsIgnoreCase("aqua")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Water is Great!");
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,100);

}


if (myColor.equalsIgnoreCase("cyan")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Cyan like a Diamond!");
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,255);

}

if (myColor.equalsIgnoreCase("magenta")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Cool!");
  analogWrite(redPin,255);
  analogWrite(greenPin,0);
  analogWrite(bluePin,150);

}


if (myColor.equalsIgnoreCase("purple") || myColor.equalsIgnoreCase("violet")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  if (myColor.equalsIgnoreCase("purple")) {
    Serial.println("Rob: I still think it's Violet.");
  }
  else {
    Serial.println("Rob: Good, you said Violet");
  }
  analogWrite(redPin,200);
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);

}

if (myColor.equalsIgnoreCase("yellow")) {
  verify=1;
  Serial.println();
  Serial.print(myName);
  Serial.print(": ");
  Serial.println(myColor);
  Serial.println();
  Serial.println("Rob: Mellow in Yellow.");
  analogWrite(redPin,255);
  analogWrite(greenPin,175);
  analogWrite(bluePin,0);

}

if (myColor.equalsIgnoreCase("none")) {
  //Turn off all pins
  verify=1;
  Serial.println();
  Serial.println("Rob: Okay then. I'll keep all the light for myself >:(");
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
}

if (verify==0) {
  Serial.println();
  Serial.println(sorry);
}
delay(dt);
}
