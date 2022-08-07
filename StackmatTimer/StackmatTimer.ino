// Stackmat Timer

// Ultrasonic Variables
int trigPin = 12;
int echoPin = 11;
int pTT;
float pTD;
float dTT;

// LED Variables
int rPin = 3;
int gPin = 2;

// Timer Variables
unsigned long timer;

float getDist(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delay(25);
  return ((pulseIn(echoPin, HIGH) * 765. * 5280. * 12.) / (3600. * 1000000.)) / 2.;
  
}

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  dTT = 30;

  while (dTT > 4) {
//    dTT = getDist(trigPin, echoPin);

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

  digitalWrite(rPin, HIGH);
  delay(100);

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

  timer = millis();
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, HIGH);
  delay(100);

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

  Serial.println((double) (millis() - timer) / 1000.);
  // Placeholder for sevseg displays

  digitalWrite(gPin, LOW);

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



}
