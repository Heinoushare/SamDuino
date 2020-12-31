int potPin=A0;
int buzzPin=4;
int potVal;
float buzzVal;
float voltVal;
void setup() {
  // put your setup code here, to run once:
pinMode(potPin,INPUT);
pinMode(buzzPin,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
potVal=analogRead(potPin);
buzzVal=(255./1023.)*potVal;
voltVal=(200./1023.)*potVal;
analogWrite(buzzPin,buzzVal);
Serial.println(voltVal);
}
