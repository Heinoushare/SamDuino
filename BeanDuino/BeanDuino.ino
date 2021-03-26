//Garduino (not original name)
int resVal; //Sensor Value
int resPin = A5; //Sensor Pin

int dt = 500; //Delay Time

void setup() {
  // put your setup code here, to run once:
  pinMode(resPin, INPUT); //PINMODE!!! I almost forgot about this.
  Serial.begin(9600); //Start the serial monitor (good ol' 9600)
}

void loop() {
  // put your main code here, to run repeatedly:

  resVal = analogRead(resPin); //Set the sensor value

  if (resVal <= 100) { 
    Serial.println("Water level: Empty");
  }
  //If water level is empty
  
  else if (resVal > 100 && resVal <= 300) {
    Serial.println("Water level: Low");
  }
  //Elif water level low

  else if (resVal > 300 && resVal <= 350) {
    Serial.println("Water level: Medium");
  }
  //Elif water level medium

  else if (resVal > 330) {
    Serial.println("Water level: High");
  }
  //Elif water level high
  
}