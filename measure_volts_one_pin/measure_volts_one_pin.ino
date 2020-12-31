int readPin=A2;
float V2=0;
int readVal;
int delayTime=500;
int redPin=8;

void setup() {
  // put your setup code here, to run once:
pinMode(readPin,INPUT);
pinMode(redPin,OUTPUT);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
readVal=analogRead(readPin);
V2=(5./1023.)*readVal;
Serial.println(V2);
if (V2>4.0){
  digitalWrite(redPin,HIGH);
}
if (V2<4.0){
  digitalWrite(redPin,LOW);
}
delay(delayTime);
}
