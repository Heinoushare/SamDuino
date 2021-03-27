// BeanDuino

// Setup Button hack
int buttonPin=12;
int buttonValue;


// Water level stuff
int resVal; // Sensor Value
int resPin = A5; // Sensor Pin

int dt = 100; // Delay Time

void readWaterLevel() {
  resVal = analogRead(resPin); //Set the sensor value

  if (resVal <= 100) { 
    Serial.println("Water level: Empty");
  }
  // If water level is empty
  
  else if (resVal > 100 && resVal <= 300) {
    Serial.println("Water level: Low");
  }
  // Elif water level low

  else if (resVal > 300 && resVal <= 350) {
    Serial.println("Water level: Medium");
  }
  // Elif water level medium

  else if (resVal > 330) {
    Serial.println("Water level: High");
  }
  // Elif water level high
}
// This function will read the water level

// LED setup stuff
int ledPin = 13;

// Execute Order Photoresistor stuff
int lightLevel;
int lightPin = A0;
int sunLevel; // You left off here. Make sure to get this set to the photoresistor amount and use this to check if the sun is around. You may want to subtract a bit as a fudge factor; sun levels can change quickly and I don't want to be calibrating this thing every two seconds.

// This function will read the light level

void setup() {
  // put your setup code here, to run once:
  
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  // I know those last two lines make zero sense. It's a button hack. More info here: https://www.youtube.com/watch?v=ChHNI8yt69g&list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP&index=34
  
  pinMode(resPin, INPUT); // PINMODE!!! I almost forgot about this.
  pinMode(lightPin, INPUT); // Pinmode for Photoresistor
  pinMode(ledPin, OUTPUT); // Pinmode for LED
  Serial.begin(9600); // Start the serial monitor (good ol' 9600)
  digitalWrite(ledPin, LOW);

  delay(dt);
  Serial.println("Please calibrate photresistor");
  delay(dt);
  buttonValue = digitalRead(buttonPin);
  while (buttonValue >= 0) {
    
    buttonValue = digitalRead(buttonPin);
    Serial.println(buttonValue);
    if (buttonValue < 1) {
      Serial.println("Button value equals 0.");
      break;
    }
    delay(dt);
  }

  sunLevel = analogRead(lightPin);
  if (sunLevel <= 50) {
      
  }

  else {
    sunLevel = sunLevel - 50;
  }
  Serial.print("Photoresistor calibrated to: ");
  Serial.println(sunLevel);

  digitalWrite(ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lightLevel = analogRead(lightPin);
  digitalWrite(ledPin, LOW);
  if (lightLevel < sunLevel) {
    
    delay(dt);
    Serial.println("Please calibrate photresistor");
    delay(dt);
    buttonValue = digitalRead(buttonPin);
    while (buttonValue >= 0) {
      
      buttonValue = digitalRead(buttonPin);
      Serial.println(buttonValue);
      if (buttonValue < 1) {
        Serial.println("Button value equals 0.");
        break;
      }
      delay(dt);
    }
  
    sunLevel = analogRead(lightPin);
    if (sunLevel <= 50) {
      
    }

    else {
      sunLevel = sunLevel - 50;
    }
    Serial.print("Photoresistor calibrated to: ");
    Serial.println(sunLevel);
  
    digitalWrite(ledPin, HIGH);
  
  }
  
}
