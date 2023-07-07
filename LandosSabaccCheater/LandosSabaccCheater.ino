// Lando's Sabacc Cheater

// Servo Stuff
#include <Servo.h> // Include Servo Library
int servoPin = 2; // Servo is connected to pin 9
int servoPos = 0; // Servo starts at 0 degrees
int servoStartPos = 0; // Servo starting position (0)
Servo myServo; // Creating a virtual Servo object myServo

// Button Stuff
int btnPin = 12; // Button is connected to pin 2
int btnGnd = 10; // The GND pin for the btn
int btnVal; // Button value(on or off) has no default value

// Misc.
int cardOut = 0; // Is the card out? (1 = yes, 0 = no)
int dt = 100; // How many milliseconds to delay for

void setup() {
  // put your setup code here, to run once:
  pinMode(btnGnd, OUTPUT); // btnGnd is an OUTPUT
  digitalWrite(btnGnd, LOW); // Set btnGnd to act like a GND
  pinMode(btnPin, INPUT); // Set button pin to an input pin
  digitalWrite(btnPin, HIGH); // This sends command to an input. More info on this hack: https://www.youtube.com/watch?v=ChHNI8yt69g&t=495s
  Serial.begin(9600); // Start the Serial monitor to easily read variables from the Arduino (9600 baudrate)
  myServo.attach(servoPin); // Attach my virtual myServo object to the servoPin
  myServo.write(servoStartPos); // Move myServo to servoStartPos degrees
}

void loop() {
  // put your main code here, to run repeatedly:
  btnVal = digitalRead(btnPin); // btnVal = On or Off
  if (btnVal == 0) {
    // If button is being pressed:
    if (cardOut == 0) {
      // If the card has not been pushed out yet
      servoPos = 180; // servoPos = 180
      myServo.write(servoPos); // Move myServo to servoPos degrees
      cardOut = 1; // Set the card to out
    }
    else if (cardOut == 1) {
      // Else if(elif) the card has already been pushed out
      servoPos = 0; // servoPos = 0
      myServo.write(servoPos); // Move myServo to servoPos degrees
      cardOut = 0; // Set the card to retracted
    }
    while (btnVal == 0) {
      // While Button is being pressed
      btnVal = digitalRead(btnPin); // Check if the button is being pressed by setting btnVal to on or off
    }
  }
  delay(dt); // Delay for dt to avoid the button bouncing
}
